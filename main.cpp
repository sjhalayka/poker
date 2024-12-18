#include "main.h"

int main(void)
{
	srand(static_cast<unsigned int>(time(0)));

	map<short unsigned int, size_t> hand_class_counts;

	size_t count = 1000000;

	for(size_t i = 0; i < count; i++)
	{
		vector<card> deck;
		init_deck(deck);
		shuffle_cards(deck);

		vector<card> hand;

		size_t num_init_cards = 5;

		deal_hand(deck, hand, num_init_cards);

		short unsigned int classification = 0;
		
		if (num_init_cards < 5)
			classification = get_best_wild_classification(hand, deck);
		else
			classification = classify_hand(hand);

		hand_class_counts[classification]++;


		//if (c >= FULL_HOUSE)
		//{
		//	print_hand_classification(c);
		//	print_cards(hand);
		//	cout << endl;
		//}
	}


	ofstream out_file("distribution.txt");

	for (map<short unsigned int, size_t>::const_iterator ci = hand_class_counts.begin(); ci != hand_class_counts.end(); ci++)
	{
		print_hand_classification(ci->first);
		cout << ci->second << endl << endl;

		out_file << ci->first << " " << ci->second << endl;
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