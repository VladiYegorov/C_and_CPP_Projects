#ifndef KNESSET_H_
#define KNESSET_H_

#include <stdbool.h>
#include "party.h"

/**
 * The knesset structure
 */
typedef struct knesset_t* Knesset;

/**
 * Results and errors codes
 */
typedef enum {
	KNESSET_SUCCESS,
	KNESSET_OUT_OF_MEMORY,
	KNESSET_ILLEGAL_ARGUMENT,
	KNESSET_NO_PLACE_FOR_PARTY,
	KNESSET_ALREADY_INSIDE,
	KNESSET_NO_PARTY,
} KnessetResult;

/**
 * Creates a new knesset.
 *
 *
 * @return
 * 	A new allocated knesset,
 * 	or NULL in case of error.
 */
Knesset knessetCreate(int knessetID, int maxPartiesNum);

/**
 * Copies a knesset.
 *
 * @return
 * 	A new allocated copy of the knesset,
 * 	or NULL in case of error.
 */
Knesset knessetCopy(Knesset copied);

/**
 * Adds a party to the knesset.
 *
 * @return
 * 	Result code.
 */
KnessetResult knessetAddParty(Knesset knesset, Party party);

/**
 * Removes a party from the knesset.
 *
 * @return
 * 	Result code.
 */
KnessetResult knessetRemoveParty(Knesset knesset, int partyID);

/**
 * Returns the number of parties in the knesset.
 *
 * @return
 * 	The number of parties.
 */
int knessetGetPartiesNum(Knesset knesset);

/**
 * Returns the ID of the party in the given place.
 *
 * @return
 * 	The ID,
 * 	or -1 in case of error.
 */
int knessetGetPartyBySize(Knesset knesset, int place);

/**
 * Removes all parties whose number of mandates is lower than the threshold.
 *
 * @return
 * 	Result code.
 */
KnessetResult knessetSetThreshold(Knesset knesset, int threshold);

/**
 * Returns the ID of the party whose platform is the closest to the citizen.
 *
 * @return
 * 	The ID,
 * 	or -1 in case of error.
 */
int knessetRecommendVote(Knesset knesset, double politicalPlatform,
		double economicalPlatform);

/**
 * Returns the number of members in the knesset.
 *
 * @return
 * 	The number of members.
 */
int knessetGetMembersNum(Knesset knesset);

/**
 * Returns whether a coalition is possible in the knesset.
 *
 * @return
 * 	Result code.
 */
KnessetResult knessetAssembleCoalition(Knesset knesset, double gap,
		bool* coalitionExists);

/**
 * Destroys a knesset - frees its memory.
 */
void knessetDestroy(Knesset knesset);

#endif /* KNESSET_H_ */
