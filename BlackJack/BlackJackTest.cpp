#include "BlackJack.h"
#include "Exceptions.h"
#include "TestMacros.h"

using blackJack::PlayerAlreadytExistException;
using blackJack::PlayerDoesNotExistException;
using blackJack::NotEnoughCardsException;

bool blackJackConstractorTest() {
	CardDeck deck1;
	BlackJack bj1(deck1);
	CardDeck deck2(CardDeck::getFullDeck());
	BlackJack bj2(deck2);

	return true;
}

bool addPlayerTest() {
	CardDeck deck;
	BlackJack bj(deck);

	bj.addPlayer(1, BlackJack::CASINO, 50);
	bj.addPlayer(2, BlackJack::CALCULATED, 50);

	ASSERT_THROW(PlayerAlreadytExistException,
			bj.addPlayer(1, BlackJack::CALCULATED, 100));
	ASSERT_THROW(PlayerAlreadytExistException,
			bj.addPlayer(2, BlackJack::CASINO, 100));
	bj.addPlayer(3, BlackJack::CASINO, 100);

	ASSERT_THROW(PlayerAlreadytExistException,
			bj.addPlayer(3, BlackJack::CALCULATED, 100));

	return true;
}

bool joinGameTest() {
	CardDeck deck;

	BlackJack bj(deck);
	bj.addPlayer(1, BlackJack::CASINO, 50);
	bj.addPlayer(2, BlackJack::CALCULATED, 60);
	bj.addPlayer(3, BlackJack::CASINO, 70);
	bj.addPlayer(4, BlackJack::CALCULATED, 80);

	bj.joinGame(1);
	ASSERT_THROW(PlayerDoesNotExistException, bj.joinGame(5));
	bj.joinGame(1);

	vector<int> id;
	id.push_back(1); id.push_back(2); id.push_back(3);
	bj.joinGame(id);

	id.push_back(5);
	ASSERT_THROW(PlayerDoesNotExistException, bj.joinGame(id));

	return true;
}

bool leaveGameTest() {
	CardDeck deck;
	BlackJack bj(deck);
	bj.addPlayer(1, BlackJack::CASINO, 50);
	bj.addPlayer(2, BlackJack::CALCULATED, 60);
	bj.addPlayer(3, BlackJack::CASINO, 70);
	bj.addPlayer(4, BlackJack::CALCULATED, 80);
	vector<int> id;
	for(int i=0;i<4;i++) {
		id.push_back(i+1) ;
	}
	bj.joinGame(id);

	bj.leaveGame(1);
	ASSERT_THROW(PlayerDoesNotExistException, bj.joinGame(5));
	bj.leaveGame(1);

	bj.leaveGame(id);

	return true;
}

bool reloadDeckTest() {
	CardDeck deck;
	BlackJack bj(deck);

	ASSERT_THROW(NotEnoughCardsException, bj.playRound());
	deck += Card(Card::Diamond,'K');
	ASSERT_THROW(NotEnoughCardsException, bj.playRound());

	CardDeck fullDeck = CardDeck::getFullDeck();
	fullDeck.draw();
	deck += Card(Card::Diamond,10);
	bj.reloadDeck(fullDeck);
	ASSERT_THROW(NotEnoughCardsException, bj.playRound());

	return true;
}

bool playRound1Test() {
	CardDeck deck = CardDeck::getFullDeck();
	deck += Card(Card::Diamond,10); deck+= Card(Card::Diamond,2);
	deck += Card(Card::Spade,9); deck += Card(Card::Spade,8);
	deck += Card(Card::Diamond,5); deck += Card(Card::Diamond,'J');
	deck += Card(Card::Club,7); deck += Card(Card::Heart,8);
	deck += Card(Card::Diamond,'A'); deck += Card(Card::Heart,6);
	deck+= Card(Card::Diamond,'A'); deck += Card(Card::Diamond,'Q');
	BlackJack bj(deck);
	bj.addPlayer(1, BlackJack::CASINO, 50);
	bj.addPlayer(2, BlackJack::CALCULATED, 60);
	bj.addPlayer(3, BlackJack::CASINO, 70);
	bj.addPlayer(4, BlackJack::CALCULATED, 80);
	vector<int> id;
	for(int i=0;i<4;i++) {
		id.push_back(i+1);
	}
	bj.joinGame(id);

	bj.playRound();
	ASSERT_EQUALS(50, bj.getBalance(1));
	ASSERT_EQUALS(90, bj.getBalance(2));
	ASSERT_EQUALS(69, bj.getBalance(3));
	ASSERT_EQUALS(100, bj.getBalance(4));

	ASSERT_EQUALS(4, bj.getRichest());
	bj.leaveGame(id);

	return true;
}

bool playRound2Test() {
	CardDeck deck = CardDeck::getFullDeck();
	deck += Card(Card::Diamond,'K'); deck+= Card(Card::Diamond,'J');
	deck += Card(Card::Spade,'A'); deck += Card(Card::Spade,8);
	deck += Card(Card::Diamond,'Q'); deck += Card(Card::Diamond,'A');
	deck += Card(Card::Club,'J'); deck += Card(Card::Heart,'K');
	deck += Card(Card::Diamond,'A'); deck += Card(Card::Heart,10);
	BlackJack bj(deck);
	bj.addPlayer(1, BlackJack::CASINO, 50);
	bj.addPlayer(2, BlackJack::CALCULATED, 50);
	bj.addPlayer(3, BlackJack::CASINO, 50);
	bj.addPlayer(4, BlackJack::CALCULATED, 50);
	vector<int> id;
	for(int i=0;i<4;i++) {
		id.push_back(i+1);
	}
	bj.joinGame(id);

	bj.playRound();
	ASSERT_EQUALS(49, bj.getBalance(1));
	ASSERT_EQUALS(30, bj.getBalance(2));
	ASSERT_EQUALS(50, bj.getBalance(3));
	ASSERT_EQUALS(30, bj.getBalance(4));
	ASSERT_EQUALS(3, bj.getRichest());

	deck += Card(Card::Diamond,10); deck+= Card(Card::Diamond,9);
	deck += Card(Card::Spade,3); deck += Card(Card::Spade,'K');
	deck += Card(Card::Diamond,4); deck += Card(Card::Diamond,8);
	deck += Card(Card::Club,6); deck += Card(Card::Heart,2);
	deck += Card(Card::Diamond,5); deck += Card(Card::Heart,10);
	deck += Card(Card::Club,'A'); deck += Card(Card::Heart,6);
	deck += Card(Card::Diamond,10);
	bj.reloadDeck(deck);

	bj.playRound();
	ASSERT_EQUALS(47, bj.getBalance(1));
	ASSERT_EQUALS(49, bj.getBalance(2));
	ASSERT_EQUALS(51, bj.getBalance(3));
	ASSERT_EQUALS(49, bj.getBalance(4));
	ASSERT_EQUALS(3, bj.getRichest());

	bj.leaveGame(id);

	return true;
}

bool blackJackExample() {
	CardDeck deck;
	BlackJack bj(deck);
	bj.addPlayer(1, BlackJack::CASINO, 100);
	bj.addPlayer(2, BlackJack::CALCULATED, 100);
	ASSERT_THROW(PlayerDoesNotExistException, bj.joinGame(3));
	bj.joinGame({ 1, 2 });
	ASSERT_THROW(NotEnoughCardsException, bj.playRound());
	bj.reloadDeck(CardDeck::getFullDeck());
	bj.playRound();
	ASSERT_EQUALS(120, bj.getBalance(2));
	ASSERT_EQUALS(2, bj.getRichest());
	bj.leaveGame({ 1, 2 });

	return true;
}

bool blackJackTest() {
	RUN_TEST(blackJackConstractorTest);
	RUN_TEST(addPlayerTest);
	RUN_TEST(joinGameTest);
	RUN_TEST(leaveGameTest);
	RUN_TEST(reloadDeckTest);
	RUN_TEST(playRound1Test);
	RUN_TEST(playRound2Test);
	RUN_TEST(blackJackExample);
	return true;
}

