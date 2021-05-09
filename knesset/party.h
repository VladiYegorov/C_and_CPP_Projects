#ifndef PARTY_H_
#define PARTY_H_

/**
 * The party structure
 */
typedef struct party_t* Party;
struct party_t {
        int partyID;
        char** members;
        int maxMembersNum;
        int mandatesNum;
        double politicalPlatform;
        double economicalPlatform;
};

/**
 * Results and errors codes
 */
typedef enum {
        PARTY_SUCCESS,
        PARTY_OUT_OF_MEMORY,
        PARTY_ILLEGAL_ARGUMENT,
        PARTY_NO_PLACE_FOR_MEMBER,
        PARTY_NO_MEMBER,
        PARTY_ALREADY_MEMBER
} PartyResult;

/**
 * Creates a new party.
 *
 *
 * @return
 *      A new allocated party,
 *      or NULL in case of error.
 */
Party partyCreate(int partyID, int maxMembersNum, double politicalPlatform,
                double economicalPlatform);

/**
 * Copies a party.
 *
 * @return
 *      A new allocated copy of the party,
 *      or NULL in case of error.
 */
Party partyCopy(Party copied);

/**
 * Returns the number of members in a party.
 *
 * @return
 *      The number of members.
 */
int partyGetMembersNum(Party party);

/**
 * Adds a member to the party.
 *
 * @return
 *      Result code.
 */
PartyResult partyAddMember(Party party, char* member);

/**
 * Removes a member from the party.
 *
 * @return
 *      Result code.
 */
PartyResult partyRemoveMember(Party party, char* member);

/**
 * Returns the place of a party member.
 *
 * @return
 *      The member's place,
 *      or -1 in case of error.
 */
int partyGetMemberPlace(Party party, char* member);

/**
 * Sets a member to be the chairman of the party.
 *
 * @return
 *      Result code.
 */
PartyResult partySetChairman(Party party, char* member);

/**
 * Returns the party member in a given place.
 *
 * @return
 *      The member in the given place,
 *      or NULL in case of error.
 */
char* partyGetMemberByPlace(Party party, int i);

/**
 * Sets the mandates number of the party.
 *
 * @return
 *      Result code.
 */
PartyResult partySetMandatesNum(Party party, int mandatesNum);

/**
 * Returns the party caucus.
 *
 * @return
 *      The caucus,
 *      or NULL in case of error.
 */
char** partyGetCaucus(Party party);

/**
 * Returns the ID of the party.
 *
 * @return
 *      The ID.
 */
int partyGetID(Party party);

/**
 * Returns the party's number of mandates.
 *
 * @return
 *      The number of mandates.
 */
int partyGetMandatesNum(Party party);

/**
 * Unions two parties, frees them and returns the united party.
 *
 * @return
 *      The united party,
 *      or NULL in case of error.
 */
Party partyUnion(Party party1, Party party2);

/**
 * Returns the political platform of the party.
 *
 * @return
 *      The political platform.
 */
double partyGetPoliticalPlatform(Party party);

/**
 * Returns the economical platform of the party.
 *
 * @return
 *      The economical platform.
 */
double partyGetEconomicalPlatform(Party party);

/**
 * Destroys a party - frees its memory.
 */
void partyDestroy(Party party);

#endif /* PARTY_H_ */
