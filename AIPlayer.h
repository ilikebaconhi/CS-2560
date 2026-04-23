#ifndef AIPLAYER__H
#define AIPLAYER_H

#include "Player.h"

class AIPlayer : public Player{
private:
    int Count;
    
public:
    AIPlayer(string playerName = "Dealer", int startingChips = 1000);
    void showDealerHand(bool hideFirstCard) const;
    void resetCount();
    void observeCard(const Card& card);
    int getCount() const;
    bool shouldHit();
    int makeBet() const;
};

#endif