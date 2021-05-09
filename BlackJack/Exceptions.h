#ifndef BLACKJACK_EXCEPTIONS_H
#define BLACKJACK_EXCEPTIONS_H

namespace blackJack {

	class blackJackException {};

	class CardException : public blackJackException {};
	class CardWrongArgsException : public CardException {};

	class DeckException : public blackJackException {};
	class CardDeckIsEmptyException : public DeckException {};

	class MapException : public blackJackException {};
	class MapElementNotFoundException : public MapException {};

	class BlackjackException : public blackJackException {};
	class PlayerAlreadytExistException : public BlackjackException {};
	class PlayerDoesNotExistException : public BlackjackException {};
	class NotEnoughCardsException : public BlackjackException {};
	class NoPlayersException : public BlackjackException {};
}

#endif