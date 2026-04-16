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
        void addSpecificCard(Card card);
        int totalValue();
        void printHand();
        Card getCard(int pos);


};

#endif