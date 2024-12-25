#include "main.h"

int main(void)
{
	srand(static_cast<unsigned int>(time(0)));

	map<short unsigned int, size_t> hand_class_counts;

	const size_t count = 2598960;

	const size_t num_init_cards = 4;	//MAX_NUM_CARDS_PER_HAND;

	for(size_t i = 0; i < count; i++)
	{
		if (i % 10000 == 0)
			cout << i / static_cast<long double>(count) << endl;

		vector<card> deck;
		init_deck(deck);
		shuffle_cards(deck);

		vector<card> hand;
		deal_hand(deck, hand, num_init_cards);

		short unsigned int classification = 0;
		
		if (num_init_cards < MAX_NUM_CARDS_PER_HAND)
			classification = get_best_classification(hand, deck);
		else
			classification = classify_hand(hand);

		hand_class_counts[classification]++;

		//if (classification == ROYAL_FLUSH)
		//{
		//	print_hand_classification(classification);
		//	print_cards(hand);
		//	cout << endl;
		//	exit(0);
		//}
	}

	string filename = "d" + to_string(num_init_cards) + ".txt";

	ofstream out_file(filename.c_str());

	// See frequency in: https://en.wikipedia.org/wiki/Poker_probability
	for (map<short unsigned int, size_t>::const_iterator ci = hand_class_counts.begin(); ci != hand_class_counts.end(); ci++)
	{
		print_hand_classification(ci->first);
		cout << ci->second << endl << endl;

		out_file << ci->first << " " << ci->second << endl;
	}




	//card c;
	//vector<card> deck;
	//init_deck(deck);

	//vector<card> hand;

	//c.value = 9;
	//c.suit = CLUBS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);

	//c.value = 10;
	//c.suit = DIAMONDS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);

	//c.value = 10;
	//c.suit = HEARTS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);

	//c.value = 9;
	//c.suit = HEARTS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);

	//print_hand_classification(get_best_classification(hand, deck));
	//print_cards(hand);

	return 0;
}