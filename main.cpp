#include "main.h"

int main(void)
{
	srand(static_cast<unsigned int>(time(0)));

	while (1)
	{
		vector<card> deck;
		init_deck(deck);
		shuffle_cards(deck);

		vector<card> hand;
		deal_hand(deck, hand, 4);

		short unsigned int c = get_best_wild_classification(hand, deck);

		if (c == FULL_HOUSE)
		{
			print_hand_classification(c);
			print_cards(hand);
			cout << endl;
		}
	}


	//card c;
	//hand.clear();

	//c.value = ACE;
	//c.suit = CLUBS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);
	//
	//c.value = ACE;
	//c.suit = DIAMONDS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);

	//c.value = 7;
	//c.suit = SPADES;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);

	//c.value = 6;
	//c.suit = DIAMONDS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);


	//c.value = KING;
	//c.suit = DIAMONDS;
	//hand.push_back(c);
	//c.value = 9;
	//c.suit = HEARTS;
	//hand.push_back(c);

	
	/*
	print_hand_classification(get_best_wild_classification(hand, deck));

	print_cards(hand);*/

	return 0;
}