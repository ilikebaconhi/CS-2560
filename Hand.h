#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"
#include "Deck.h"
#include <iostream>
using namespace std;

class Hand{
    private: 
        vector<Card> cards;
        int currentPosition;
        int acePosition;
        bool isAce;
    public:
        Hand();
        void addCard(Deck& temp);
        vector<Card> getAllCards() const;
        void addSpecificCard(Card card);
        int totalValue() const;
        void printHand();
        Card getCard(int pos);

};

#endif
