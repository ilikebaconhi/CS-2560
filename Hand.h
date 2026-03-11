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
        void addCard(Deck& temp);
        int totalValue();
        void printHand();
        Card getCard(int pos);
        Hand();


};

#endif