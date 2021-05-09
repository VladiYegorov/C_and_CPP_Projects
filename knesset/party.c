#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "party.h"

static PartyResult inputRemains(Party copy, Party copied,int from)
{
	int j=from;
	for(int i=2*from; j < partyGetMembersNum(copied);i++,j++) {
			char *temp=malloc(sizeof(strlen(copied->members[j])+1));
			if(temp==NULL) {
				return PARTY_ILLEGAL_ARGUMENT;
			}
			strcpy(temp,copied->members[j]);
			copy->members[i] = temp;
			temp = NULL;
	}
	return PARTY_SUCCESS;
}

static PartyResult moveSetMembersToRight(Party party, int start, int end)
{
	for(int i=start,j=end; i<(j+1) ; j--)
	{
	    char *temp = malloc(sizeof(strlen(party->members[j])+1));
	    if(temp==NULL) {
            return PARTY_ILLEGAL_ARGUMENT;
	    }
		strcpy(temp,party->members[j]);
		free(party->members[j+1]);
		party->members[j+1] = temp;
		free(party->members[j]);
		party->members[j] = NULL;
		temp = NULL;
	}
	return PARTY_SUCCESS;
}

static bool InLegalRange(double num)
{
	return (num>=0 && num<=10);
}

static PartyResult copyMembersBySize(Party from,char **to,int size)
{
	for(int i=0;i<size;i++)
	{
	    char *temp = malloc(strlen(from->members[i])+1);
	    if(temp==NULL) {
	    	return PARTY_OUT_OF_MEMORY;
	    }
        strcpy(temp,from->members[i]);
        to[i] = temp;
        temp = NULL;
	}
	return PARTY_SUCCESS;
}

Party partyCreate(int partyID, int maxMembersNum, double politicalPlatform,
					double economicalPlatform)
{
	Party result = malloc(sizeof(*result));
	if((result==NULL) || (partyID<=0) || (maxMembersNum<=0) ||
		(!InLegalRange(politicalPlatform))||(!InLegalRange(economicalPlatform))) {
		return NULL;
	}
	result->partyID = partyID;
	char **members = calloc(maxMembersNum,sizeof(*members));
	if(members==NULL) {
		free(result);
		return NULL;
	}
	result->members = members;
	result->maxMembersNum = maxMembersNum;
	result->mandatesNum = 0;
	result->politicalPlatform = politicalPlatform;
	result->economicalPlatform = economicalPlatform;
	return result;
}

Party partyCopy(Party copied)
{
	if(copied == NULL) {
		return NULL;
	}
	Party copy;
	copy = partyCreate(copied->partyID,copied->maxMembersNum,
			copied->politicalPlatform,copied->economicalPlatform);
	if(copy==NULL) {
			return NULL;
	}
	int mandatesNum = copied->mandatesNum;
	copy->mandatesNum = mandatesNum;
	char **copyMembers = calloc(copied->maxMembersNum,sizeof(*copyMembers));
	if(copyMembers == NULL) {
		partyDestroy(copy);
		return NULL;
	}
	copyMembersBySize(copied,copyMembers,partyGetMembersNum(copied));
	for(int i=0; i<partyGetMembersNum(copied) ;i++) {
        copy->members[i] = copyMembers[i];
        copyMembers[i] = NULL;
	}
	free(copyMembers);
	return copy;
}

int partyGetMembersNum(Party party)
{
	assert(party!=NULL);
	int i=0;
	while( (party->maxMembersNum) > i && (party->members[i])) {
		i++;
	}
	return i;
}

PartyResult partyAddMember(Party party, char* member)
{
	if(party==NULL || member==NULL) {
		return PARTY_ILLEGAL_ARGUMENT;
	}
	if(partyGetMemberPlace(party,member) != -1) {
		return PARTY_ALREADY_MEMBER;
	}
	int membersNum = partyGetMembersNum(party);
	if(membersNum==(party->maxMembersNum)) {
		return PARTY_NO_PLACE_FOR_MEMBER;
	}
    char *temp = malloc(sizeof(strlen(member)+1));
    if(temp==NULL) {
        return PARTY_ILLEGAL_ARGUMENT;
    }
	strcpy(temp,member);
	temp[strlen(member)] = '\0';
	party->members[membersNum] = NULL;
	party->members[membersNum] = temp;
	temp = NULL;
	return PARTY_SUCCESS;
}

PartyResult partyRemoveMember(Party party, char* member)
{
	if(party==NULL || member==NULL) {
		return PARTY_ILLEGAL_ARGUMENT;
	}
	int index = partyGetMemberPlace(party,member);
	if(index==-1) {
		return PARTY_NO_MEMBER;
	}
    int membersNum=partyGetMembersNum(party);
    free(party->members[index]);
    party->members[index] = NULL;
	for(int i=index+1; i<membersNum ; i++) {
        char *temp = malloc(sizeof(strlen(party->members[i])+1));
        if(temp==NULL) {
            return PARTY_ILLEGAL_ARGUMENT;
        }
        strcpy(temp,party->members[i]);
        temp[strlen(party->members[i])] = '\0';
        party->members[i-1] = temp;
        free(party->members[i]);
        temp = NULL;
        party->members[i] = NULL;
        }
	return PARTY_SUCCESS;
}

int partyGetMemberPlace(Party party, char* member)
{
	if(party==NULL|| member==NULL) {
		return -1;
	}
	for(int i=0; i<partyGetMembersNum(party) ; i++) {
		if(strcmp(party->members[i],member)==0) {
			return i;
		}}
	return -1;
}

PartyResult partySetChairman(Party party, char* member)
{
	if(party==NULL || member==NULL) {
		return PARTY_ILLEGAL_ARGUMENT;
	}
	int membersNum=partyGetMembersNum(party);
	if(partyGetMemberPlace(party,member)==-1) {
		if(membersNum == (party->maxMembersNum)) {
			free(party->members[party->maxMembersNum-1]);
			party->members[party->maxMembersNum-1] = NULL;
			membersNum--;
		}
		moveSetMembersToRight(party,0,membersNum-1);
		char *temp =  malloc(sizeof((strlen(member)+1)));
		if(temp==NULL) {
			return PARTY_OUT_OF_MEMORY;
		}
		strcpy(temp,member);
		temp[strlen(member)] = '\0';
		free(party->members[0]);
		party->members[0] = NULL;
		party->members[0] = temp;
		temp = NULL;
		return PARTY_SUCCESS;
	}
	int index=partyGetMemberPlace(party,member);
	free(party->members[index]);
	party->members[index] = NULL;
	moveSetMembersToRight(party,0,index-1);
	char *temp =  malloc(sizeof((strlen(member)+1)));
	if(temp==NULL) {
				return PARTY_OUT_OF_MEMORY;
	}
    strcpy(temp,member);
    temp[strlen(member)] = '\0';
    free(party->members[0]);
    party->members[0] = NULL;
    party->members[0] = temp;
    temp = NULL;
	return PARTY_SUCCESS;
}

char* partyGetMemberByPlace(Party party, int place)
{
	if(party == NULL) {
		return NULL;
	}
	if(place >= party->maxMembersNum || party->members[place] == NULL) {
		return NULL;
	}
	char *member = malloc(sizeof(strlen(party->members[place])+1));
	if(member == NULL) {
		return NULL;
	}
	strcpy(member,party->members[place]);
	return member;
}

PartyResult partySetMandatesNum(Party party, int mandatesNum)
{
	if(party == NULL) {
		return PARTY_ILLEGAL_ARGUMENT;
	}
	if(mandatesNum<0 || mandatesNum>(party->maxMembersNum)) {
		return PARTY_ILLEGAL_ARGUMENT;
	}
	party->mandatesNum = mandatesNum;
	return PARTY_SUCCESS;
}

char** partyGetCaucus(Party party)
{
	if(party == NULL) {
		return NULL;
	}
	if(party->mandatesNum == 0 ||
			(party->mandatesNum) > partyGetMembersNum(party)) {
		return NULL;
	}
	char **caucus = calloc((party->mandatesNum),sizeof(*caucus));
	if(caucus == NULL) {
		return NULL;
	}
	copyMembersBySize(party,caucus,party->mandatesNum);
	return caucus;
}

int partyGetID(Party party)
{
	assert(party!=NULL);
	return (party->partyID);
}

int partyGetMandatesNum(Party party)
{
	assert(party!=NULL);
	return (party->mandatesNum);
}

Party partyUnion(Party party1, Party party2)
{
	if(party1==NULL) {
		partyDestroy(party2);
		return NULL;
	}
	if(party2==NULL) {
		partyDestroy(party1);
		return NULL;
	}
	double newPolitical, newEconomical;
	newPolitical=(party1->politicalPlatform)*((float)(party1->mandatesNum+1)
			/((float)party1->mandatesNum+(float)party2->mandatesNum+2))+
			(party2->politicalPlatform)*((float)(party2->mandatesNum+1)
				/((float)party1->mandatesNum+(float)party2->mandatesNum+2));
	newEconomical=(party1->economicalPlatform)*((float)(party1->mandatesNum+1)
			/((float)party1->mandatesNum+(float)party2->mandatesNum+2))+
			(party2->economicalPlatform)*((float)(party2->mandatesNum+1)
				/((float)party1->mandatesNum+(float)party2->mandatesNum+2));
	Party result = partyCreate(party1->partyID+party2->partyID,
			party1->maxMembersNum+party2->maxMembersNum,
			newPolitical,newEconomical);
	if(result==NULL) {
		partyDestroy(party1);
		partyDestroy(party2);
		return NULL;
	}
	result->mandatesNum = (party1->mandatesNum) + (party2->mandatesNum);
	Party first = party1;
	Party second = party2;
	int minMembersNum = partyGetMembersNum(party1);
	if(partyGetMembersNum(party1) > partyGetMembersNum(party2)) {
		minMembersNum = partyGetMembersNum(party2);
	}
	if(party1->mandatesNum < party2->mandatesNum) {
		first = party2;
		second = party1;
	}
	for(int i=0;i<minMembersNum;i++) {
	    char *temp1=malloc(sizeof(strlen(first->members[i])+1));
	    if(temp1==NULL) {
	    	partyDestroy(party1);
	    	partyDestroy(party2);
	    	return NULL;
	    }
	    char *temp2=malloc(sizeof(strlen(second->members[i])+1));
	    if(temp2==NULL) {
	    	free(temp1);
	    	partyDestroy(party1);
	    	partyDestroy(party2);
	    	return NULL;
		}
	    strcpy(temp1,first->members[i]);
	    strcpy(temp2,second->members[i]);
	    result->members[i*2] = NULL;
	    result->members[i*2+1] = NULL;
		result->members[i*2] = temp1;
		result->members[i*2+1] = temp2;
		temp1 = NULL;
		temp2 = NULL;
	}
	inputRemains(result,first,minMembersNum);
	inputRemains(result,second,minMembersNum);
	partyDestroy(party1);
	partyDestroy(party2);
	return result;
}

double partyGetPoliticalPlatform(Party party)
{
	assert(party!=NULL);
	return (party->politicalPlatform);
}

double partyGetEconomicalPlatform(Party party)
{
	assert(party!=NULL);
	return (party->economicalPlatform);
}

void partyDestroy(Party party)
{
	if(party==NULL) {
		return;
	}
	for(int i=0; i< (party->maxMembersNum) ;i++) {
		if(party->members[i] != NULL){
			free(party->members[i]);
			party->members[i] = NULL;
		}}
	free(party->members);
	party->members = NULL;
	free(party);
}
