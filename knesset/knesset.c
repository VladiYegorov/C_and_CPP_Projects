#include "knesset.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

static void sortKnesset (Knesset knesset);
static double findGap(Knesset knesset,int place, double politicalPlatform,double economicalPlatform);
static bool knessetRecCoalition(Knesset knesset, double gap,int coalition[],int minMandate,int current);
static int isLeagal(Knesset knesset,double gap,int coalition[],int current);

#define IMPOSSIBLE_BEST_RESULT 100
struct knesset_t {
	Party* parties;
	int knessetID;
	int maxPartiesNum;
	int currentPartiesNum;

};

Knesset knessetCreate(int knessetID, int maxPartiesNum){
	if (knessetID<=0||maxPartiesNum<=0){
		return NULL;
	}
	Knesset knesset = malloc(sizeof(*knesset));
	if (knesset == NULL) {
		return NULL;
	}
	knesset->parties = malloc(maxPartiesNum * sizeof(Party));
	if (knesset->parties == NULL) {
		free(knesset);
		return NULL;
	}
	for (int i=0;i<maxPartiesNum;i++){
		knesset->parties[i]=NULL;
	}
	knesset->maxPartiesNum= maxPartiesNum;
	knesset->knessetID = knessetID;
	knesset->currentPartiesNum=-1;
	return knesset;
}

Knesset knessetCopy(Knesset copied){
	if (copied==NULL){
		return NULL;
	}
	Knesset copy = knessetCreate(copied->knessetID,copied->maxPartiesNum);
	if (copy == NULL) {
		return NULL;
	}
	for (int i=0;i<=copied->currentPartiesNum;i++){
		KnessetResult result=knessetAddParty(copy,copied->parties[i]);
		if (result==KNESSET_OUT_OF_MEMORY){
			for (int k=i;k>-1;k--){
				partyDestroy(copy->parties[i]);
			}
			knessetDestroy(copy);
			return NULL;
		}}
	copy->currentPartiesNum= copied->currentPartiesNum;
	return copy;
}

KnessetResult knessetAddParty(Knesset knesset, Party party){
	if (knesset==NULL || party==NULL){
		return KNESSET_ILLEGAL_ARGUMENT;
	}
	int i=0;
	while (i<=knesset->currentPartiesNum){
		if (knesset->parties[i]!=NULL){
			if (partyGetID(knesset->parties[i])==partyGetID(party)){
				return KNESSET_ALREADY_INSIDE;
			}}
		i++;
	}
	if (knesset->currentPartiesNum>= knesset->maxPartiesNum-1){
		return KNESSET_NO_PLACE_FOR_PARTY;
	}
	knesset->currentPartiesNum++;
	knesset->parties[knesset->currentPartiesNum]=partyCopy(party);
		if(knesset->parties[knesset->currentPartiesNum]==NULL){
			return KNESSET_OUT_OF_MEMORY;
		}
	return KNESSET_SUCCESS;
}

KnessetResult knessetRemoveParty(Knesset knesset, int partyID){
	if (knesset==NULL){
		return KNESSET_ILLEGAL_ARGUMENT;
	}
	for (int i=0;i<knesset->maxPartiesNum;i++){
		if (knesset->parties[i]!=NULL&&
				partyGetID(knesset->parties[i])==partyID){
			partyDestroy(knesset->parties[i]);
			int getCurrentParty=knesset->currentPartiesNum;
			if (getCurrentParty>0&&getCurrentParty<=knesset->maxPartiesNum-1){
				knesset->parties[i]=knesset->parties[getCurrentParty];
			}
			knesset->parties[knesset->currentPartiesNum]=NULL;
			knesset->currentPartiesNum--;
			return KNESSET_SUCCESS;
		}
	}
	return KNESSET_NO_PARTY;
}

int knessetGetPartiesNum(Knesset knesset){
	assert (knesset!=NULL);
	return knesset->currentPartiesNum+1;
}

int knessetGetPartyBySize(Knesset knesset, int place){
	if (knesset==NULL||knesset->currentPartiesNum<place||place<0){
		return -1;
	}
	sortKnesset(knesset);
	return partyGetID(knesset->parties[place]);
}

static void sortKnesset(Knesset knesset){
    for(int j=0;j<knesset->currentPartiesNum;j++){
        for(int i=0;i<knesset->currentPartiesNum;i++){
            int currentPartyID=partyGetID(knesset->parties[i]);
            int nextPartyID=partyGetID(knesset->parties[i+1]);
            int currentPartyMandate=partyGetMandatesNum(knesset->parties[i]);
            int nextPartyMandate=partyGetMandatesNum(knesset->parties[i+1]);
            if(currentPartyMandate>=nextPartyMandate){
                if(currentPartyMandate==nextPartyMandate
                   &&currentPartyID>nextPartyID){
                    Party tmp1 = knesset->parties[i];
                    knesset->parties[i] = (knesset->parties[i+1]);
                    knesset->parties[i+1] = tmp1;
                    tmp1=NULL;
                    }
                if(currentPartyMandate>nextPartyMandate){
                    Party tmp2=knesset->parties[i];
                    knesset->parties[i]= (knesset->parties[i+1]);
                    knesset->parties[i+1]=tmp2;
                    tmp2=NULL;
                }}}}
}

KnessetResult knessetSetThreshold(Knesset knesset, int threshold){
	if (knesset==NULL||threshold<0){
		return KNESSET_ILLEGAL_ARGUMENT;
	}
	for (int i=knesset->currentPartiesNum;i>=0;i--){
		int getMadateNum=partyGetMandatesNum(knesset->parties[i]);
		if(knesset->parties[i]!=NULL&&getMadateNum<threshold){
			int getID=partyGetID(knesset->parties[i]);
			knessetRemoveParty(knesset,getID);
		}}
	return KNESSET_SUCCESS;
}

int knessetRecommendVote(Knesset knesset, double politicalPlatform,
		double economicalPlatform){
	if (knesset==NULL||knesset->currentPartiesNum<0||politicalPlatform<0
			||politicalPlatform>10||economicalPlatform<0
			||economicalPlatform>10){
		return -1;
	}
	double bestResult=IMPOSSIBLE_BEST_RESULT;
	int bestMatchID;
	for (int i=0;i<=knesset->currentPartiesNum;i++){
		assert (knesset->parties[i]!=NULL);
        double result=findGap(knesset,i,politicalPlatform,economicalPlatform);
		if (result<bestResult){
			bestResult=result;
			bestMatchID=partyGetID(knesset->parties[i]);
		}}
	return bestMatchID;
}

static double findGap(Knesset knesset,int place,double politicalPlatform, double economicalPlatform){
	double politicalView=partyGetPoliticalPlatform(knesset->parties[place]);
	double economicalView=partyGetEconomicalPlatform(knesset->parties[place]);
	double result= fabs(politicalView-politicalPlatform)+fabs
        (economicalView-economicalPlatform);
	return result;
}

int knessetGetMembersNum(Knesset knesset){
	assert(knesset!=NULL);
	int memberNum=0;
	for(int i=0;i<=knesset->currentPartiesNum;i++){
		if(knesset->parties[i]!=NULL){
			memberNum+=partyGetMandatesNum(knesset->parties[i]);
		}}
	return memberNum;
}

KnessetResult knessetAssembleCoalition(Knesset knesset, double gap,
		bool* coalitionExists){
	if(knesset==NULL||gap<0||coalitionExists==NULL){
		return KNESSET_ILLEGAL_ARGUMENT;
	}
	int minMandate=knessetGetMembersNum(knesset)/2;
	int *coalition = malloc((knesset->currentPartiesNum+1) * sizeof(int));
	if (coalition==NULL){
	return KNESSET_OUT_OF_MEMORY;
	}

	for (int i=0;i<knesset->currentPartiesNum;i++){
		coalition[i]=0;
	}


	*coalitionExists= knessetRecCoalition(knesset,gap,coalition,minMandate,0);
	free(coalition);
	return KNESSET_SUCCESS;

}

static bool knessetRecCoalition(Knesset knesset, double gap,int coalition[],
		int minMandate,int current){
    if (knesset->currentPartiesNum+1==current){
    	int coalitionSize=0;
    	for (int i=0;i<=knesset->currentPartiesNum;i++){
    		if(coalition[i]==1){
    		coalitionSize+=partyGetMandatesNum(knesset->parties[i]);
    		}}
        if (coalitionSize>minMandate){
            return true;
        } else {
            return false;
        }}
    coalition[current]=0;
    bool coalitionWithoutCurrent = knessetRecCoalition(knesset,gap,coalition,
    												minMandate,current+1);
    bool coalitionWithCurrent=false;
    if (isLeagal(knesset,gap,coalition,current)==1){
    	coalition[current]=1;
    	coalitionWithCurrent = knessetRecCoalition(knesset,gap,coalition,
    												minMandate,current+1);
    }
    if (coalitionWithCurrent==true||coalitionWithoutCurrent==true){
    	return true;
    }
    return false;
}

static int isLeagal(Knesset knesset,double gap,int coalition[],int current){
    assert(knesset->parties[current]!=NULL);
	for (int i=0;i<knesset->currentPartiesNum;i++){
		if(coalition[i]==1){
			double politicalView=partyGetPoliticalPlatform
					(knesset->parties[i]);
			double economicalView=partyGetEconomicalPlatform
					(knesset->parties[i]);
			double maxGap=findGap(knesset,current,politicalView,
													economicalView);
            if(maxGap>gap){
                return 0;
            }}}
	return 1;
}

void knessetDestroy(Knesset knesset){
	if (knesset==NULL){
		return;
	}
	for (int i=knesset->currentPartiesNum;i>=0;i--){
		if(knesset->parties[i]!=NULL) {
			partyDestroy(knesset->parties[i]);
		}}
	free(knesset->parties);
	free(knesset);
}

















