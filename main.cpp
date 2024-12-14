#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;


#define JACK 11
#define KING 12
#define QUEEN 13
#define ACE 14

#define NUM_SUITS 4
#define NUM_CARDS_PER_DECK 52
#define NUM_CARDS_PER_HAND 5

#define HIGH_CARD 0
#define ONE_PAIR 1
#define TWO_PAIR 2
#define THREE_OF_A_KIND 3
#define STRAIGHT 4
#define FLUSH 5
#define FULL_HOUSE 6
#define FOUR_OF_A_KIND 7
#define STRAIGHT_FLUSH 8
#define ROYAL_FLUSH 9

#define SPADES 0
#define HEARTS 1
#define DIAMONDS 2
#define CLUBS 3


class card
{
public:
	short unsigned int value;
	short unsigned int suit;

	void print(void)
	{
		if (value >= JACK)
		{
			if (value == JACK)
				cout << "Jack";
			if (value == QUEEN)
				cout << "Queen";
			if (value == KING)
				cout << "King";
			if (value == ACE)
				cout << "Ace";
		}
		else
		{
			cout << value;
		}

		cout << ' ';

		if (suit == SPADES)
			cout << "Spades" << endl;
		else if (suit == HEARTS)
			cout << "Hearts" << endl;
		else if (suit == DIAMONDS)
			cout << "Diamonds" << endl;
		else
			cout << "Clubs" << endl;
	}

	bool operator<(card& rhs)
	{
		if (suit < rhs.suit)
			return true;
		else if (suit > rhs.suit)
			return false;

		if (value < rhs.value)
			return true;
		else if (value > rhs.value)
			return false;

		return false;
	}
};

void init_deck(vector<card>& deck)
{
	deck.clear();

	for (short unsigned int i = 0; i < NUM_SUITS; i++)
	{
		for (short unsigned int j = 2; j <= ACE; j++)
		{
			card c;
			c.value = j;
			c.suit = i;

			deck.push_back(c);
		}
	}
}

void shuffle_cards(vector<card>& cards, const size_t iterations)
{
	if (cards.size() < 2)
		return;

	for (size_t i = 0; i < iterations; i++)
	{
		size_t card_1 = rand() % (cards.size() - 1);
		size_t card_2 = rand() % (cards.size() - 1);

		if (card_1 != card_2)
		{
			card tempc = cards[card_1];
			cards[card_1] = cards[card_2];
			cards[card_2] = tempc;
		}
	}
}

void sort_cards(vector<card>& cards)
{
	if (cards.size() < 2)
		return;

	sort(cards.begin(), cards.end());
}

void print_cards(vector<card>& cards)
{
	for (size_t i = 0; i < cards.size(); i++)
		cards[i].print();
}

void deal_hand(vector<card>& cards, vector<card>& hand)
{
	hand.clear();

	size_t num_cards_to_draw = cards.size();

	if (num_cards_to_draw > NUM_CARDS_PER_HAND)
		num_cards_to_draw = NUM_CARDS_PER_HAND;

	for (size_t i = 0; i < num_cards_to_draw; i++)
	{
		hand.push_back(cards[cards.size() - 1]);
		cards.pop_back();
	}
}

void print_hand_classification(short unsigned int hand_class)
{
	if (hand_class == HIGH_CARD)
		cout << "High Card";
	else if (hand_class == ONE_PAIR)
		cout << "One Pair";
	else if (hand_class == TWO_PAIR)
		cout << "Two Pair";
	else if (hand_class == THREE_OF_A_KIND)
		cout << "Three of a kind";
	else if (hand_class == STRAIGHT)
		cout << "Straight";
	else if (hand_class == FLUSH)
		cout << "Flush";
	else if (hand_class == FULL_HOUSE)
		cout << "Full House";
	else if (hand_class == FOUR_OF_A_KIND)
		cout << "Four of a kind";
	else if (hand_class == STRAIGHT_FLUSH)
		cout << "Straight Flush";
	else if (hand_class == ROYAL_FLUSH)
		cout << "Royal Flush";

	cout << endl;
}

// These classifications assume that the cards are pre-sorted
bool is_flush(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> suit_counts;

	for (size_t i = 0; i < NUM_CARDS_PER_HAND; i++)
		suit_counts[sorted_hand[i].suit]++;

	if (suit_counts.size() == 1)
		return true;

	return false;
}

bool is_straight(const vector<card> sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	if (value_counts.size() == 5)
	{
		if (sorted_hand[4].value == ACE)
		{
			if (sorted_hand[0].value == 2 ||
				sorted_hand[1].value == 3 ||
				sorted_hand[2].value == 4 ||
				sorted_hand[3].value == 5)
			{
				return true;
			}
		}
		
		if (sorted_hand[4].value == sorted_hand[0].value + 4)
			return true;
	}

	return false;
}

bool is_straight_flush(const vector<card>& sorted_hand)
{
	if (is_straight(sorted_hand) && is_flush(sorted_hand))
		return true;

	return false;
}

bool is_royal_flush(const vector<card>& sorted_hand)
{
	if (is_straight_flush(sorted_hand))
	{
		if (sorted_hand[0].value == 10 && sorted_hand[4].value == ACE)
			return true;
	}

	return false;
}

bool is_four_of_a_kind(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		if (ci->second == 4)
			return true;

	return false;
}

bool is_full_house(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	if (value_counts.size() == 2)
	{
		bool found_three = false;
		bool found_two = false;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		{
			if (ci->second == 3)
				found_three = true;
			else if (ci->second == 2)
				found_two = true;
		}

		if (found_three && found_two)
			return true;
	}

	return false;
}

bool is_three_of_a_kind(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		if (ci->second == 3)
			return true;

	return false;
}

bool is_two_pair(const vector<card>& sorted_hand)
{
	short unsigned int pair_count = 0;

	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		if (ci->second == 2)
			pair_count++;

	if (pair_count == 2)
		return true;

	return false;
}

bool is_one_pair(const vector<card>& sorted_hand)
{
	short unsigned int pair_count = 0;

	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		if (ci->second == 2)
			pair_count++;

	if (pair_count == 1)
		return true;

	return false;
}

short unsigned int classify_hand(const vector<card>& hand)
{
	vector<card> temp_hand = hand;

	if (temp_hand.size() != NUM_CARDS_PER_HAND)
	{
		cout << "Error: hand must contain 5 cards" << endl;
		return HIGH_CARD;
	}

	sort_cards(temp_hand);

	short unsigned int hand_class = HIGH_CARD;

	if (is_royal_flush(temp_hand))
		hand_class = ROYAL_FLUSH;
	else if (is_straight_flush(temp_hand))
		hand_class = STRAIGHT_FLUSH;
	else if (is_four_of_a_kind(temp_hand))
		hand_class = FOUR_OF_A_KIND;
	else if (is_full_house(temp_hand))
		hand_class = FULL_HOUSE;
	else if (is_flush(temp_hand))
		hand_class = FLUSH;
	else if (is_straight(temp_hand))
		hand_class = STRAIGHT;
	else if (is_three_of_a_kind(temp_hand))
		hand_class = THREE_OF_A_KIND;
	else if (is_two_pair(temp_hand))
		hand_class = TWO_PAIR;
	else if (is_one_pair(temp_hand))
		hand_class = ONE_PAIR;

	return hand_class;
}


int main(void)
{
	srand(static_cast<unsigned int>(time(0)));

	vector<card> deck;
	init_deck(deck);
	shuffle_cards(deck, 1000000);

	vector<card> hand;
	//deal_hand(deck, hand);


	card c;

	//if (hand_class == HIGH_CARD)
	//	cout << "High Card";
	//else if (hand_class == ONE_PAIR)
	//	cout << "One Pair";
	//else if (hand_class == TWO_PAIR)
	//	cout << "Two Pair";
	//else if (hand_class == THREE_OF_A_KIND)
	//	cout << "Three of a kind";
	//else if (hand_class == STRAIGHT)
	//	cout << "Straight";
	//else if (hand_class == FLUSH)
	//	cout << "Flush";
	//else if (hand_class == FULL_HOUSE)
	//	cout << "Full House";
	//else if (hand_class == FOUR_OF_A_KIND)
	//	cout << "Four of a kind";
	//else if (hand_class == STRAIGHT_FLUSH)
	//	cout << "Straight Flush";
	//else if (hand_class == ROYAL_FLUSH)
	//	cout << "Royal Flush";

	c.value = JACK;
	c.suit = DIAMONDS;
	hand.push_back(c);
	c.value = 10;
	c.suit = SPADES;
	hand.push_back(c);
	c.value = QUEEN;
	c.suit = CLUBS;
	hand.push_back(c);
	c.value = 5;
	c.suit = DIAMONDS;
	hand.push_back(c);
	c.value = 7;
	c.suit = HEARTS;
	hand.push_back(c);

	print_hand_classification(classify_hand(hand));
	print_cards(hand);

	return 0;
}