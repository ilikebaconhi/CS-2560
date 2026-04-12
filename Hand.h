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
        int totalValue();
        void printHand();
        void clearHand();
        Card getCard(int pos);


};

#endif