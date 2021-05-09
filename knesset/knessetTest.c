
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testsMacros.h"
#include "knesset.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool KnessetCreateTest() {
	bool result = true;
	Knesset knesset1 = knessetCreate(7, 0);
	TEST_EQUALS(result, knesset1, NULL);
	Knesset knesset2 = knessetCreate(0, 2);
	TEST_EQUALS(result, knesset2, NULL);
	Knesset knesset3= knessetCreate(1, 5);
	TEST_DIFFERENT(result, knesset3, NULL);
	knessetDestroy(knesset1);
	knessetDestroy(knesset2);
	knessetDestroy(knesset3);
	return result;
}

static bool KnessetCopyTest() {
	bool result = true;
	Knesset knesset = knessetCreate(1, 5);
	TEST_DIFFERENT(result, knesset, NULL);
	Knesset copied=knessetCopy(knesset);
	TEST_DIFFERENT(result, knesset, NULL);
    knessetDestroy(copied);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 0);
    Party party1 = partyCreate(100, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(50, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
    Party party3 = partyCreate(30, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
    TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 2), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 1),PARTY_SUCCESS);
    TEST_EQUALS(result, partyAddMember(party1, "1"), PARTY_SUCCESS);
	TEST_EQUALS(result, partyAddMember(party2, "1"), PARTY_SUCCESS);
    TEST_EQUALS(result, partyAddMember(party2, "2"), PARTY_SUCCESS);
	TEST_EQUALS(result, partyAddMember(party3, "1"), PARTY_SUCCESS);
    TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
    copied=knessetCopy(knesset);
	TEST_DIFFERENT(result, knesset, NULL);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 3);
    TEST_EQUALS(result, knessetGetMembersNum(knesset), 4);
    partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
    knessetDestroy(copied);
	knessetDestroy(knesset);
	return result;
}

static bool KnessetAddPartyTest() {
	bool result = true;
	Knesset knesset = knessetCreate(1, 5);
	Party party1 = partyCreate(100, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(50, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
	Party party3 = partyCreate(30, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
	Party party4 = partyCreate(3, 5, 0.01, 0.1);
	TEST_DIFFERENT(result, party4, NULL);
	Party party5 = partyCreate(10, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party5, NULL);
    Party party6 = partyCreate(11, 7, 2.01, 2.01);
	TEST_DIFFERENT(result, party5, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 0);
    TEST_EQUALS(result, knessetGetMembersNum(knesset), 0);
    TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 3);
    TEST_EQUALS(result, knessetGetMembersNum(knesset), 3);
    TEST_EQUALS(result, partySetMandatesNum(party4, 3), PARTY_SUCCESS);
    TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 4);
    TEST_EQUALS(result, knessetGetMembersNum(knesset), 6);
    TEST_EQUALS(result, knessetRemoveParty(knesset, 3), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 4);
    TEST_EQUALS(result, knessetGetMembersNum(knesset), 6);
	TEST_EQUALS(result, partySetMandatesNum(party5, 2), PARTY_SUCCESS);
    TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 5);
    TEST_EQUALS(result, knessetGetMembersNum(knesset), 8);
    TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_ALREADY_INSIDE);
    TEST_EQUALS(result, knessetAddParty(knesset, party6), KNESSET_NO_PLACE_FOR_PARTY);
    partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
	partyDestroy(party4);
	partyDestroy(party5);
    partyDestroy(party6);
	knessetDestroy(knesset);
	return result;
}

static bool KnessetRemovePartyTest() {
	bool result = true;
	Knesset knesset = knessetCreate(1, 5);
	Party party1 = partyCreate(100, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(50, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
	Party party3 = partyCreate(30, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
	Party party4 = partyCreate(3, 5, 0.01, 0.1);
	TEST_DIFFERENT(result, party4, NULL);
	Party party5 = partyCreate(10, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party5, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party4, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party5, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 100), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 4);
	TEST_EQUALS(result, knessetGetMembersNum(knesset), 4);
    TEST_EQUALS(result, knessetRemoveParty(knesset, 30), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 10), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 50), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 0);
	TEST_EQUALS(result, knessetGetMembersNum(knesset), 0);
	TEST_EQUALS(result, partyAddMember(party1, " "), PARTY_SUCCESS);
	TEST_EQUALS(result, partyAddMember(party3, "1"), PARTY_SUCCESS);
	TEST_EQUALS(result, partyAddMember(party2, "1"), PARTY_SUCCESS);
    TEST_EQUALS(result, partyAddMember(party2, "2"), PARTY_SUCCESS);
	TEST_EQUALS(result, partyAddMember(party5, "1"), PARTY_SUCCESS);
    TEST_EQUALS(result, partySetMandatesNum(party1, 3), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party4, 5), PARTY_SUCCESS);
    TEST_EQUALS(result, partySetMandatesNum(party5, 0), PARTY_SUCCESS);
    TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetRemoveParty(knesset, 304),KNESSET_NO_PARTY);
    TEST_EQUALS(result, knessetGetMembersNum(knesset), 10);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 100), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 100), KNESSET_NO_PARTY);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 10), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 3);
	TEST_EQUALS(result, knessetGetMembersNum(knesset), 7);
    partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
	partyDestroy(party4);
	partyDestroy(party5);
	knessetDestroy(knesset);
	return result;
}

static bool KnessetGetPartiesNumTest() {

	bool result = true;
    Knesset knesset = knessetCreate(1, 5);
	Party party1 = partyCreate(100, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(50, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
	Party party3 = partyCreate(30, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
	Party party4 = partyCreate(3, 5, 0.01, 0.1);
	TEST_DIFFERENT(result, party4, NULL);
	Party party5 = partyCreate(10, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party5, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party4, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party5, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 5);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 100), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 4);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 50), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 2);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 10), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 30), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 0);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 1);
    TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
    TEST_EQUALS(result, partySetMandatesNum(party2, 4), PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, partyAddMember(party2, " "), PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 5);
	partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
	partyDestroy(party4);
	partyDestroy(party5);
	knessetDestroy(knesset);
	return result;
}


static bool KnessetGetPartyBySizeTest() {
	bool result = true;
	Knesset knesset = knessetCreate(1, 5);
	Party party1 = partyCreate(1, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(2, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
	Party party3 = partyCreate(3, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
	Party party4 = partyCreate(4, 5, 0.01, 0.1);
	TEST_DIFFERENT(result, party4, NULL);
	Party party5 = partyCreate(5, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party5, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 2), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 3),PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party4, 2), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party5, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 5);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 6), -1);
    partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
	partyDestroy(party4);
	partyDestroy(party5);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 0), 1);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 2), 2);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 4), 3);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 4), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 4);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 0), 1);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 3), 3);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 1), 3);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartyBySize(knesset, 0), -1);
	knessetDestroy(knesset);
	return result;
}


static bool KnessetSetThresholdTest() {
	bool result = true;	Knesset knesset = knessetCreate(1, 5);
	Party party1 = partyCreate(100, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(50, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
	Party party3 = partyCreate(30, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
	Party party4 = partyCreate(3, 5, 0.01, 0.1);
	TEST_DIFFERENT(result, party4, NULL);
	Party party5 = partyCreate(10, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party5, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 4), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party4, 2), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party5, 1),PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetSetThreshold(knesset, 1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 5);
    TEST_EQUALS(result, knessetSetThreshold(knesset, 0),
			KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetSetThreshold(knesset, -20),
			KNESSET_ILLEGAL_ARGUMENT);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 5);
	TEST_EQUALS(result, knessetSetThreshold(knesset, 2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 2);
	TEST_EQUALS(result, knessetSetThreshold(knesset, 1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 2);
	TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetSetThreshold(knesset, 0),
			KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 3);
	TEST_EQUALS(result, knessetSetThreshold(knesset, 15), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetGetPartiesNum(knesset), 0);
	partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
	partyDestroy(party4);
	partyDestroy(party5);
	knessetDestroy(knesset);
	return result;
}


static bool KnessetRecommendVoteTest() {
	bool result = true;
	Knesset knesset = knessetCreate(1, 5);
	Party party1 = partyCreate(100, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(50, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
	Party party3 = partyCreate(30, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
	Party party4 = partyCreate(3, 5, 0.01, 0.1);
	TEST_DIFFERENT(result, party4, NULL);
	Party party5 = partyCreate(10, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party5, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 2), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 3), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party4, 2), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party5, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetRecommendVote(knesset, 3.12, 4.37), 30);
	TEST_EQUALS(result, knessetRecommendVote(knesset, 1, 0.2),100);
	TEST_EQUALS(result, knessetRecommendVote(knesset, 0, 0), 10);
	TEST_EQUALS(result, knessetRecommendVote(knesset, 3.12, -4.37), -1);
	knessetDestroy(knesset);
	partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
	partyDestroy(party4);
	partyDestroy(party5);
	return result;
}

static bool KnessetAssembleCoalitionTest() {
	bool result = true;
	bool coalition = true;
	Knesset knesset = knessetCreate(1, 5);
	TEST_EQUALS(result, knessetAssembleCoalition(knesset, 2, &coalition),
			KNESSET_SUCCESS);
	TEST_EQUALS(result, coalition, false);
	Party party1 = partyCreate(100, 30, 1.5, 0);
	TEST_DIFFERENT(result, party1, NULL);
	Party party2 = partyCreate(50, 10, 2.3, 0);
	TEST_DIFFERENT(result, party2, NULL);
	Party party3 = partyCreate(30, 7, 4, 4);
	TEST_DIFFERENT(result, party3, NULL);
	Party party4 = partyCreate(3, 5, 0.01, 0.1);
	TEST_DIFFERENT(result, party4, NULL);
	Party party5 = partyCreate(10, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party5, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party1, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party2, 1),PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party3, 1), PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party4, 1),PARTY_SUCCESS);
	TEST_EQUALS(result, partySetMandatesNum(party5, 1),PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party1), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party2), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party3), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party4), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party5), KNESSET_SUCCESS);
	TEST_EQUALS(result, knessetAssembleCoalition(knesset, 0.2, &coalition),
			KNESSET_SUCCESS);
	TEST_EQUALS(result, coalition, false);
	TEST_EQUALS(result, knessetAssembleCoalition(knesset, 2, &coalition),
			KNESSET_SUCCESS);
	TEST_EQUALS(result, coalition, true);
	TEST_EQUALS(result, knessetRemoveParty(knesset, 10), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 4);
	TEST_EQUALS(result, knessetGetMembersNum(knesset), 4);
    Party party6 = partyCreate(5, 7, 0.01, 0.01);
	TEST_DIFFERENT(result, party6, NULL);
	TEST_EQUALS(result, partySetMandatesNum(party6, 6),PARTY_SUCCESS);
	TEST_EQUALS(result, knessetAddParty(knesset, party6), KNESSET_SUCCESS);
    TEST_EQUALS(result, knessetGetPartiesNum(knesset), 5);
	TEST_EQUALS(result, knessetGetMembersNum(knesset), 10);
    TEST_EQUALS(result, knessetAssembleCoalition(knesset, 0.05, &coalition),
			KNESSET_SUCCESS);
	TEST_EQUALS(result, coalition, true);
    partyDestroy(party1);
	partyDestroy(party2);
	partyDestroy(party3);
	partyDestroy(party4);
	partyDestroy(party5);
	partyDestroy(party6);
	knessetDestroy(knesset);
	return result;
}

int main() {
    RUN_TEST(KnessetCreateTest);
	RUN_TEST(KnessetCopyTest);
	RUN_TEST(KnessetAddPartyTest);
	RUN_TEST(KnessetRemovePartyTest);
	RUN_TEST(KnessetGetPartiesNumTest);
    RUN_TEST(KnessetGetPartyBySizeTest);
	RUN_TEST(KnessetSetThresholdTest);
	RUN_TEST(KnessetRecommendVoteTest);
	RUN_TEST(KnessetAssembleCoalitionTest);
	return 0;
}
