#include "pch.h"
#include "CppUnitTest.h"

#define private public

#include "CardFace.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace hw2test
{
		TEST_CLASS(hw2test)
		{
		public:

				TEST_METHOD(when_calling_card_constructor_a_card_is_created)
				{
						const auto cardFace = CardFace::FIVE;

						Card card(cardFace);

						Assert::AreEqual((int)cardFace, (int)card.getDenomination());
				}

				TEST_METHOD(when_calling_deck_constructor_a_deck_is_created) {
						const auto deckSize = 15;

						Deck deck(deckSize);

						Assert::AreEqual(deckSize, deck.deckSize);

						for (auto i = 0; i < deckSize; ++i) {
								Assert::IsNotNull(deck.cards[i]);
						}
				}

				TEST_METHOD(when_deck_goes_out_of_scope_rsc_are_freed_up) {
						const auto deckSize = 15;
						Deck* ptr = nullptr;

						if (true) {
								Deck deck(deckSize);
								ptr = &deck;
						}

						const Card* expected = (Card*)0xdddddddddddddddd;
						Card* actual = ptr->cards[0];

						Assert::IsTrue(expected == actual);
				}

				TEST_METHOD(when_calling_deck_get_cards_a_deep_copy_is_returned) {
						const auto deckSize = 5;

						Deck deck(deckSize);

						auto** original = deck.cards;
						auto** copy = deck.getCards();

						Assert::IsTrue(original != copy);

						for (auto i = 0; i < deckSize; ++i) {
								Assert::IsTrue(original[i] != copy[i]);
						}
				}

				TEST_METHOD(when_calling_player_constructor_a_player_is_created) {
						const auto* name = "Test1";

						Player p1(name);

						Assert::AreEqual(name, p1.name);
						Assert::IsTrue(name != p1.name);

						for (auto i = 0; i < Player::DECK_SIZE; ++i) {
								Assert::IsNotNull(p1.deck.cards[i]);
						}
				}

				TEST_METHOD(when_player_goes_out_of_scope_rsc_are_freed_up) {
						const auto* name = "Test1";
						Player* ptr = nullptr;

						if (true) {
								Player p1(name);
								ptr = &p1;
						}

						Assert::IsTrue(ptr->name[0] == 'Ý');
				}

				TEST_METHOD(when_calling_player_get_name_a_deep_copy_is_returned) {
						const auto* name = "Test1";

						Player p1(name);

						auto* copy = p1.getName();
						auto* original = p1.name;

						Assert::IsTrue(original != copy);
				}

				TEST_METHOD(when_calling_player_cards_greater_than_the_correct_cards_are_returned) {
						const auto* name = "Test1";

						Player p1(name);

						const auto cardFace = CardFace::ONE;

						auto resultSize = 0;

						auto** result = new Card * [Player::DECK_SIZE];
						auto** cards = p1.deck.getCards();
						for (auto i = 0; i < Player::DECK_SIZE; ++i)
						{
								if ((int)cards[i]->getDenomination() <= (int)cardFace)
								{
										continue;
								}

								result[resultSize] = new Card(cards[i]->getDenomination());
								++resultSize;
						}

						auto receivedResultSize = 0;
						auto** receivedResult = p1.cardsGreaterThan(cardFace, receivedResultSize);

						Assert::AreEqual(resultSize, receivedResultSize);

						for (auto i = 0; i < resultSize; ++i) {
								Assert::AreEqual((int)result[i]->denomination, (int)receivedResult[i]->denomination);
						}
				}
		};
}
