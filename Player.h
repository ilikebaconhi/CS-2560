#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Hand.h"
#include "Deck.h"

using namespace std;

class Player{
    private:
        string name;
        Hand hand;
        int chips;
        int currentBet;
        int wins;

    public: 
        Player(string playerName = "Player", int startingChips = 100);
        bool placeBet(int amount);
        void winBet();
        void loseBet();
        void pushBet();

        int getChips() const;
        int getCurrentBet() const;
        string getName() const;
        int getHandValue();
        void drawCard(Deck& deck);
        void clearHand();

        void printHand();

};


#endif
