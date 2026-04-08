#include "AIPlayer.h"

AIPlayer::AIPlayer(string name, int startingChips)
    : Player(name, startingChips){
    Count = 0;    
    }

void AIPlayer::resetCount(){
    Count = 0;
}

void AIPlayer::observeCard(const Card& card){
    int val = card.getValue();

    if(val >= 2 && val <= 6){
        Count++;
    } else if(val == 10 || val == 11){
        Count--;
    }
}

int AIPlayer::getCount() const{
    return Count;
}

bool AIPlayer::shouldHit(){
    int total = getHandValue();

    if (Count >= 3) {
        return total < 16;
    }
    else if (Count <= -3) {
        return total < 18;
    }
    else {
        return total < 17;
    }
}

int AIPlayer::makeBet() const {
    
    if (Count >= 3 && getChips() >= 50) {
        return 50;
    }
    else if (getChips() >= 25) {
        return 25;
    }
    else {
        return getChips();
    }

    return -1;

}