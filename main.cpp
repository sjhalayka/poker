#include "main.h"






short unsigned int get_best_wild_classification(const vector<card>& hand, const vector<card>& remaining_unflipped_cards)
{
	vector<card> temp_hand = hand;

	if (temp_hand.size() >= MAX_NUM_CARDS_PER_HAND || temp_hand.size() == 0)
	{
		cout << "Error: hand must contain between 1 and 4 cards" << endl;
		return HIGH_CARD;
	}

	// THIS IS IMPORTANT
	sort_cards(temp_hand);

	short unsigned int best_class = HIGH_CARD;

	if (is_possible_royal_flush(temp_hand, remaining_unflipped_cards))
		best_class = ROYAL_FLUSH;
	 if (is_possible_straight_flush(temp_hand, remaining_unflipped_cards))
		best_class = STRAIGHT_FLUSH;
	else if (is_possible_four_of_a_kind(temp_hand, remaining_unflipped_cards))
		best_class = FOUR_OF_A_KIND;
	else if (is_possible_full_house(temp_hand, remaining_unflipped_cards))
		best_class = FULL_HOUSE;
	else if (is_possible_flush(temp_hand, remaining_unflipped_cards))
		best_class = FLUSH;
	//else if (is_possible_straight(temp_hand, remaining_unflipped_cards))
	//	best_class = STRAIGHT;
	else if (is_possible_three_of_a_kind(temp_hand, remaining_unflipped_cards))
		best_class = THREE_OF_A_KIND;
	else if (is_possible_two_pair(temp_hand, remaining_unflipped_cards))
		best_class = TWO_PAIR;
	else if (is_possible_one_pair(temp_hand, remaining_unflipped_cards))
		best_class = ONE_PAIR;

	return best_class;
}




int main(void)
{
	srand(static_cast<unsigned int>(time(0)));

	vector<card> deck;
	init_deck(deck);
	shuffle_cards(deck, 1000000);

	vector<card> hand;
	//deal_hand(deck, hand, 3);
//print_hand_classification(classify_hand(hand));
	


	card c;
	hand.clear();

	c.value = 4;
	c.suit = HEARTS;
	hand.push_back(c);
	remove_card_from_unflipped_cards(c, deck);
	
	c.value = 5;
	c.suit = HEARTS;
	hand.push_back(c);
	remove_card_from_unflipped_cards(c, deck);

	//c.value = 7;
	//c.suit = CLUBS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);

	//c.value = 7;
	//c.suit = DIAMONDS;
	//hand.push_back(c);
	//remove_card_from_unflipped_cards(c, deck);


	//c.value = KING;
	//c.suit = DIAMONDS;
	//hand.push_back(c);
	//c.value = 9;
	//c.suit = HEARTS;
	//hand.push_back(c);

	
	


	print_hand_classification(get_best_wild_classification(hand, deck));

	print_cards(hand);







	return 0;
}