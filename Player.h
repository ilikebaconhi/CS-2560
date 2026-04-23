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
        bool placeBet(int amount); // returns true if bet is successfully placed, false otherwise
        void winBet();
        void winBlackJackBet(); //when the user gets blackjack in the first two cards drawn
        void loseBet();
        void pushBet();
        Hand getHand() const;
        int getChips() const;
        int getCurrentBet() const;
        string getName() const;
        int getHandValue() const;
        Card addCard(Deck& deck);
        void clearHand();
        void printHand();

};


#endif