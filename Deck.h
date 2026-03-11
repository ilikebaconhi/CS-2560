#ifndef DECK_H
#define DECK_H

#include <string>
#include <vector>
#include "Card.h"
using namespace std;

class Deck{
    private:
        vector<Card> deck;
        int nextCard;

    public:
        Deck();
        Card getCard();
        void shuffle();

};


#endif
