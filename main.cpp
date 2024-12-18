#include "main.h"









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

	c.value = KING;
	c.suit = CLUBS;
	hand.push_back(c);
	remove_card_from_unflipped_cards(c, deck);
	
	c.value = 9;
	c.suit = CLUBS;
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