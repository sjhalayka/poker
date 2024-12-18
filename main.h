#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;


#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14

#define NUM_SUITS 4
#define NUM_CARDS_PER_DECK 52
#define MAX_NUM_CARDS_PER_HAND 5

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


class window
{
public:
	short unsigned int value0 = 0;
	short unsigned int value1 = 0;
	short unsigned int value2 = 0;
	short unsigned int value3 = 0;
	short unsigned int value4 = 0;
};

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

	bool operator<(card& rhs) const
	{
		if (value < rhs.value)
			return true;
		else if (value > rhs.value)
			return false;

		if (suit < rhs.suit)
			return true;
		else if (suit > rhs.suit)
			return false;

		return false;
	}

	bool operator==(card& rhs) const
	{
		if (value == rhs.value && suit == rhs.suit)
			return true;

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

void shuffle_cards(vector<card>& cards)
{
	random_shuffle(cards.begin(), cards.end());
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

void deal_hand(vector<card>& cards, vector<card>& hand, const size_t num_cards)
{
	hand.clear();

	size_t num_cards_to_draw = cards.size();

	if (num_cards_to_draw > num_cards)
		num_cards_to_draw = num_cards;

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

	for (size_t i = 0; i < MAX_NUM_CARDS_PER_HAND; i++)
		suit_counts[sorted_hand[i].suit]++;

	if (suit_counts.size() == 1)
		return true;

	return false;
}

bool is_straight(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < MAX_NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	if (value_counts.size() == 5)
	{
		if (sorted_hand[4].value == ACE)
		{
			if (sorted_hand[0].value == 2 &&
				sorted_hand[1].value == 3 &&
				sorted_hand[2].value == 4 &&
				sorted_hand[3].value == 5)
				return true;
			else if (sorted_hand[0].value == 10 &&
				sorted_hand[1].value == JACK &&
				sorted_hand[2].value == QUEEN &&
				sorted_hand[3].value == KING)
				return true;
		}
		else
		{
			if (sorted_hand[4].value == sorted_hand[0].value + 4)
				return true;
		}
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

	for (size_t i = 0; i < MAX_NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		if (ci->second == 4)
			return true;

	return false;
}

bool is_full_house(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < MAX_NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	if (value_counts.size() == 2)
	{
		bool found_triplet = false;
		bool found_pair = false;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		{
			if (ci->second == 3)
				found_triplet = true;
			else if (ci->second == 2)
				found_pair = true;
		}

		if (found_triplet && found_pair)
			return true;
	}

	return false;
}

bool is_three_of_a_kind(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < MAX_NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		if (ci->second == 3)
			return true;

	return false;
}

bool is_two_pair(const vector<card>& sorted_hand)
{
	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < MAX_NUM_CARDS_PER_HAND; i++)
		value_counts[sorted_hand[i].value]++;

	short unsigned int pair_count = 0;

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

	for (size_t i = 0; i < MAX_NUM_CARDS_PER_HAND; i++)
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

	if (temp_hand.size() != MAX_NUM_CARDS_PER_HAND)
	{
		cout << "Error: hand must contain 5 cards" << endl;
		return HIGH_CARD;
	}

	// THIS IS IMPORTANT
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

bool is_card_in_unflipped_cards(card c, const vector<card>& remaining_unflipped_cards)
{
	for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
		if (remaining_unflipped_cards[i] == c)
			return true;

	return false;
}

bool remove_card_from_unflipped_cards(card c, vector<card>& remaining_unflipped_cards)
{
	for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
	{
		if (remaining_unflipped_cards[i] == c)
		{
			remaining_unflipped_cards.erase(remaining_unflipped_cards.begin() + i);
			return true;
		}
	}

	return false;
}

size_t get_value_count(const short unsigned int value, const vector<card>& remaining_unflipped_cards)
{
	size_t count = 0;

	for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
		if (value == remaining_unflipped_cards[i].value)
			count++;

	return count;
}

size_t get_suit_count(const short unsigned int suit, const vector<card>& remaining_unflipped_cards)
{
	size_t count = 0;

	for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
		if (suit == remaining_unflipped_cards[i].suit)
			count++;

	return count;
}




bool is_possible_flush(const vector<card>& sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	const size_t num_wildcards = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;
	map<short unsigned int, size_t> suit_counts;

	for (size_t i = 0; i < sorted_hand.size(); i++)
	{
		value_counts[sorted_hand[i].value]++;
		suit_counts[sorted_hand[i].suit]++;
	}

	// Is there only one suit?
	if (suit_counts.size() != 1)
		return false;

	size_t the_suit_count = get_suit_count(suit_counts.begin()->first, remaining_unflipped_cards);

	if (the_suit_count < num_wildcards)
		return false;

	return true;
}



bool is_possible_royal_flush(const vector<card>& sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	const size_t num_wildcards = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;
	map<short unsigned int, size_t> suit_counts;

	for (size_t i = 0; i < sorted_hand.size(); i++)
	{
		value_counts[sorted_hand[i].value]++;
		suit_counts[sorted_hand[i].suit]++;
	}

	// Is there only one suit?
	if (suit_counts.size() != 1)
		return false;

	// Are all card values distinct?
	if (value_counts.size() != sorted_hand.size())
		return false;


	short unsigned int the_suit = suit_counts.begin()->first;

	bool found_ace = false;
	bool found_king = false;
	bool found_queen = false;
	bool found_jack = false;
	bool found_10 = false;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
	{
		if (ci->first == ACE || ci->first == 1)
			found_ace = true;
		else if (ci->first == KING)
			found_king = true;
		else if (ci->first == QUEEN)
			found_queen = true;
		else if (ci->first == JACK)
			found_jack = true;
		else if (ci->first == 10)
			found_10 = true;
	}

	size_t num_wildcards_left = num_wildcards;

	if (false == found_ace && num_wildcards_left > 0)
	{
		card c;
		c.suit = the_suit;
		c.value = ACE;

		found_ace = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

		num_wildcards_left--;
	}

	if (false == found_king && num_wildcards_left > 0)
	{
		card c;
		c.suit = the_suit;
		c.value = KING;

		found_king = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

		num_wildcards_left--;
	}

	if (false == found_queen && num_wildcards_left > 0)
	{
		card c;
		c.suit = the_suit;
		c.value = QUEEN;

		found_queen = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

		num_wildcards_left--;
	}

	if (false == found_jack && num_wildcards_left > 0)
	{
		card c;
		c.suit = the_suit;
		c.value = JACK;

		found_jack = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

		num_wildcards_left--;
	}

	if (false == found_10 && num_wildcards_left > 0)
	{
		card c;
		c.suit = the_suit;
		c.value = 10;

		found_10 = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

		num_wildcards_left--;
	}

	if (found_ace == true &&
		found_king == true &&
		found_queen == true &&
		found_jack == true &&
		found_10 == true)
	{
		return true;
	}

	return false;
}




bool is_possible_one_pair(const vector<card>& sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	const size_t num_wildcards = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
	{
		if (ci->second >= 2)
			return true;
		else if (num_wildcards >= 1 && get_value_count(ci->first, remaining_unflipped_cards) >= 1)
			return true;
	}

	// If we made it this far then we're dealing with 
	// making a pair purely out of the remaining unflipped cards
	if (num_wildcards >= 2)
	{
		value_counts.clear();

		for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
			value_counts[remaining_unflipped_cards[i].value]++;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
			if (ci->second >= 2)
				return true;
	}

	return false;
}



bool is_possible_two_pair(const vector<card>& sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	size_t num_wildcards = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		value_counts[sorted_hand[i].value]++;

	size_t pair_count = 0;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
	{
		if (ci->second >= 2)
		{
			pair_count++;
		}
		else if (num_wildcards >= 1 && get_value_count(ci->first, remaining_unflipped_cards) >= 1)
		{
			num_wildcards--;
			pair_count++;
		}
	}

	if (pair_count >= 2)
		return true;

	// If we made it this far then we're dealing with 
	// making two pair purely out of the remaining unflipped cards

	const size_t num_wildcards_needed = 2 * (2 - pair_count);

	if (num_wildcards >= num_wildcards_needed)
	{
		value_counts.clear();

		for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
			value_counts[remaining_unflipped_cards[i].value]++;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
			if (ci->second >= 2)
				pair_count++;
	}

	if (pair_count >= 2)
		return true;

	return false;
}


bool is_possible_three_of_a_kind(const vector<card>& sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	size_t num_wildcards_remaining = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
	{
		if (ci->second >= 3)
			return true;
		else if (num_wildcards_remaining >= 3 - ci->second && get_value_count(ci->first, remaining_unflipped_cards) >= 3 - ci->second)
			return true;
	}

	// If we made it this far then we're dealing with 
	// making a quad purely out of the remaining unflipped cards
	if (num_wildcards_remaining == 3)
	{
		value_counts.clear();

		for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
			value_counts[remaining_unflipped_cards[i].value]++;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
			if (ci->second >= 3)
				return true;
	}

	return false;
}

bool is_possible_four_of_a_kind(const vector<card>& sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	size_t num_wildcards_remaining = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		value_counts[sorted_hand[i].value]++;

	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
	{
		if (ci->second >= 4)
			return true;
		else if (num_wildcards_remaining >= 4 - ci->second && get_value_count(ci->first, remaining_unflipped_cards) >= 4 - ci->second)
			return true;
	}

	// If we made it this far then we're dealing with 
	// making a quad purely out of the remaining unflipped cards
	if (num_wildcards_remaining == 4)
	{
		value_counts.clear();

		for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
			value_counts[remaining_unflipped_cards[i].value]++;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
			if (ci->second >= 4)
				return true;
	}

	return false;
}



bool is_possible_full_house(const vector<card>& sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	size_t num_wildcards = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	short unsigned int triplet_value = 0;
	short unsigned int pair_value = 0;
	bool found_pair = false;
	bool found_triplet = false;

	map<short unsigned int, size_t> value_counts;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		value_counts[sorted_hand[i].value]++;

	// Find triplet in hand
	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
	{
		const size_t hand_count = get_value_count(ci->first, sorted_hand);
		const size_t wildcards_needed = 3 - hand_count;

		if (wildcards_needed <= num_wildcards)
		{
			num_wildcards -= wildcards_needed;
			found_triplet = true;
			triplet_value = ci->first;
			break;
		}
	}

	//  Find triplet in unflipped cards
	if (found_triplet == false && num_wildcards >= 3)
	{
		value_counts.clear();

		for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
			value_counts[remaining_unflipped_cards[i].value]++;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		{
			if (ci->second >= 3)
			{
				num_wildcards -= 3;
				triplet_value = ci->first;
				found_triplet = true;
				break;
			}
		}
	}

	// Find pair in hand
	for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
	{
		if (ci->first == triplet_value)
			continue;

		const size_t hand_count = get_value_count(ci->first, sorted_hand);
		const size_t wildcards_needed = 2 - hand_count;

		if (wildcards_needed <= num_wildcards)
		{
			num_wildcards -= wildcards_needed;
			found_pair = true;
			break;
		}
	}

	// Find pair in unflipped cards
	if (found_pair == false && num_wildcards >= 2)
	{
		value_counts.clear();

		for (size_t i = 0; i < remaining_unflipped_cards.size(); i++)
			value_counts[remaining_unflipped_cards[i].value]++;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		{
			if (ci->first == triplet_value)
				continue;

			if (ci->second >= 2)
			{
				num_wildcards -= 2;
				pair_value = ci->first;
				found_pair = true;
				break;
			}
		}
	}

	if (found_pair && found_triplet)
		return true;

	return false;
}

void get_windows(vector<window> &windows, vector<card> sorted_hand)
{
	windows.clear();

	bool is_all_five_or_less_except_ace = true;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		if (sorted_hand[i].value > 5 && sorted_hand[i].value != ACE)
			is_all_five_or_less_except_ace = false;

	if (is_all_five_or_less_except_ace)
		for (size_t i = 0; i < sorted_hand.size(); i++)
			if (sorted_hand[i].value == ACE)
				sorted_hand[i].value = 1;

	short unsigned min_value = ACE + 1;
	short unsigned max_value = 0;

	for (size_t i = 0; i < sorted_hand.size(); i++)
	{
		if (sorted_hand[i].value < min_value)
			min_value = sorted_hand[i].value;

		if (sorted_hand[i].value > max_value)
			max_value = sorted_hand[i].value;
	}

	size_t spread = max_value - min_value;

	if (spread > 4)
		return;

	long signed int start_window_pos = max_value - 4;
	long signed int end_window_pos = min_value + 4 - 1;

	if (start_window_pos < 1)
		start_window_pos = 1;

	const long unsigned int initial_window_pos = start_window_pos;

	while(1)
	{
		window w;
		w.value0 = static_cast<short unsigned int>(start_window_pos);
		w.value1 = static_cast<short unsigned int>(start_window_pos) + 1;
		w.value2 = static_cast<short unsigned int>(start_window_pos) + 2;
		w.value3 = static_cast<short unsigned int>(start_window_pos) + 3;
		w.value4 = static_cast<short unsigned int>(start_window_pos) + 4;

		windows.push_back(w);

		start_window_pos++;

		if (w.value4 > end_window_pos)
			break;
	}

	//cout << "Window vector size " << windows.size() << endl;

	//for (size_t i = 0; i < windows.size(); i++)
	//	cout << windows[i].value0 << " " << windows[i].value4 << endl;

}

bool is_possible_straight_flush(vector<card> sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	const size_t num_wildcards = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;
	map<short unsigned int, size_t> suit_counts;

	bool is_all_five_or_less_except_ace = true;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		if (sorted_hand[i].value > 5 && sorted_hand[i].value != ACE)
			is_all_five_or_less_except_ace = false;

	if (is_all_five_or_less_except_ace)
		for (size_t i = 0; i < sorted_hand.size(); i++)
			if (sorted_hand[i].value == ACE)
				sorted_hand[i].value = 1;

	for (size_t i = 0; i < sorted_hand.size(); i++)
	{
		value_counts[sorted_hand[i].value]++;
		suit_counts[sorted_hand[i].suit]++;
	}

	// Is there only one suit?
	if (suit_counts.size() != 1)
		return false;

	// Are all card values distinct?
	if (value_counts.size() != sorted_hand.size())
		return false;

	short unsigned int the_suit = suit_counts.begin()->first;

	vector<window> windows;
	get_windows(windows, sorted_hand);

	if (windows.size() == 0)
		return false;

	for (size_t i = 0; i < windows.size(); i++)
	{
		bool found_0 = false;
		const short unsigned int value_0 = windows[i].value0;
		bool found_1 = false;
		const short unsigned int value_1 = windows[i].value1;
		bool found_2 = false;
		const short unsigned int value_2 = windows[i].value2;
		bool found_3 = false;
		const short unsigned int value_3 = windows[i].value3;
		bool found_4 = false;
		const short unsigned int value_4 = windows[i].value4;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		{
			if (ci->first == value_0)
				found_0 = true;
			else if (ci->first == value_1)
				found_1 = true;
			else if (ci->first == value_2)
				found_2 = true;
			else if (ci->first == value_3)
				found_3 = true;
			else if (ci->first == value_4)
				found_4 = true;
		}

		size_t num_wildcards_left = num_wildcards;

		if (false == found_0 && num_wildcards_left > 0)
		{
			card c;
			c.suit = the_suit;
			c.value = value_0;

			if (value_0 == 1)
				c.value = ACE;

			found_0 = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

			num_wildcards_left--;
		}

		if (false == found_1 && num_wildcards_left > 0)
		{
			card c;
			c.suit = the_suit;
			c.value = value_1;

			if (value_1 == 1)
				c.value = ACE;

			found_1 = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

			num_wildcards_left--;
		}

		if (false == found_2 && num_wildcards_left > 0)
		{
			card c;
			c.suit = the_suit;
			c.value = value_2;

			if (value_2 == 1)
				c.value = ACE;

			found_2 = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

			num_wildcards_left--;
		}

		if (false == found_3 && num_wildcards_left > 0)
		{
			card c;
			c.suit = the_suit;
			c.value = value_3;

			if (value_3 == 1)
				c.value = ACE;

			found_3 = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

			num_wildcards_left--;
		}

		if (false == found_4 && num_wildcards_left > 0)
		{
			card c;
			c.suit = the_suit;
			c.value = value_4;

			if (value_4 == 1)
				c.value = ACE;
			
			found_4 = is_card_in_unflipped_cards(c, remaining_unflipped_cards);

			num_wildcards_left--;
		}

		if (found_0 == true &&
			found_1 == true &&
			found_2 == true &&
			found_3 == true &&
			found_4 == true)
		{
			return true;
		}
	}

	return false;
}


bool is_possible_straight(vector<card> sorted_hand, const vector<card>& remaining_unflipped_cards)
{
	const size_t num_wildcards = MAX_NUM_CARDS_PER_HAND - sorted_hand.size();

	map<short unsigned int, size_t> value_counts;
	map<short unsigned int, size_t> suit_counts;

	bool is_all_five_or_less_except_ace = true;

	for (size_t i = 0; i < sorted_hand.size(); i++)
		if (sorted_hand[i].value > 5 && sorted_hand[i].value != ACE)
			is_all_five_or_less_except_ace = false;

	if (is_all_five_or_less_except_ace)
		for (size_t i = 0; i < sorted_hand.size(); i++)
			if (sorted_hand[i].value == ACE)
				sorted_hand[i].value = 1;

	for (size_t i = 0; i < sorted_hand.size(); i++)
	{
		value_counts[sorted_hand[i].value]++;
		suit_counts[sorted_hand[i].suit]++;
	}

	// Are all card values distinct?
	if (value_counts.size() != sorted_hand.size())
		return false;

	vector<window> windows;
	get_windows(windows, sorted_hand);

	if (windows.size() == 0)
		return false;

	for (size_t i = 0; i < windows.size(); i++)
	{
		bool found_0 = false;
		const short unsigned int value_0 = windows[i].value0;
		bool found_1 = false;
		const short unsigned int value_1 = windows[i].value1;
		bool found_2 = false;
		const short unsigned int value_2 = windows[i].value2;
		bool found_3 = false;
		const short unsigned int value_3 = windows[i].value3;
		bool found_4 = false;
		const short unsigned int value_4 = windows[i].value4;

		for (map<short unsigned int, size_t>::const_iterator ci = value_counts.begin(); ci != value_counts.end(); ci++)
		{
			if (ci->first == value_0)
				found_0 = true;
			if (ci->first == value_1)
				found_1 = true;
			if (ci->first == value_2)
				found_2 = true;
			if (ci->first == value_3)
				found_3 = true;
			if (ci->first == value_4)
				found_4 = true;
		}

		size_t num_wildcards_left = num_wildcards;

		if (false == found_0 && num_wildcards_left > 0)
		{
			card c;
			c.value = value_0;

			if (value_0 == 1)
				c.value = ACE;

			size_t count = get_value_count(c.value, remaining_unflipped_cards);

			if (count > 0)
				found_0 = true;

			num_wildcards_left--;
		}

		if (false == found_1 && num_wildcards_left > 0)
		{
			card c;
			c.value = value_1;

			if (value_1 == 1)
				c.value = ACE;

			size_t count = get_value_count(c.value, remaining_unflipped_cards);

			if (count > 0)
				found_1 = true;

			num_wildcards_left--;
		}

		if (false == found_2 && num_wildcards_left > 0)
		{
			card c;
			c.value = value_2;

			if (value_2 == 1)
				c.value = ACE;

			size_t count = get_value_count(c.value, remaining_unflipped_cards);

			if (count > 0)
				found_2 = true;

			num_wildcards_left--;
		}

		if (false == found_3 && num_wildcards_left > 0)
		{
			card c;
			c.value = value_3;

			if (value_3 == 1)
				c.value = ACE;

			size_t count = get_value_count(c.value, remaining_unflipped_cards);

			if (count > 0)
				found_3 = true;

			num_wildcards_left--;
		}

		if (false == found_4 && num_wildcards_left > 0)
		{
			card c;
			c.value = value_4;

			if (value_4 == 1)
				c.value = ACE;

			size_t count = get_value_count(c.value, remaining_unflipped_cards);

			if (count > 0)
				found_4 = true;

			num_wildcards_left--;
		}

		if (found_0 == true &&
			found_1 == true &&
			found_2 == true &&
			found_3 == true &&
			found_4 == true)
		{
			return true;
		}
	}

	return false;
}


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
	else if (is_possible_straight_flush(temp_hand, remaining_unflipped_cards))
		best_class = STRAIGHT_FLUSH;
	else if (is_possible_four_of_a_kind(temp_hand, remaining_unflipped_cards))
		best_class = FOUR_OF_A_KIND;
	else if (is_possible_full_house(temp_hand, remaining_unflipped_cards))
		best_class = FULL_HOUSE;
	else if (is_possible_flush(temp_hand, remaining_unflipped_cards))
		best_class = FLUSH;
	else if (is_possible_straight(temp_hand, remaining_unflipped_cards))
		best_class = STRAIGHT;
	else if (is_possible_three_of_a_kind(temp_hand, remaining_unflipped_cards))
		best_class = THREE_OF_A_KIND;
	else if (is_possible_two_pair(temp_hand, remaining_unflipped_cards))
		best_class = TWO_PAIR;
	else if (is_possible_one_pair(temp_hand, remaining_unflipped_cards))
		best_class = ONE_PAIR;

	return best_class;
}
