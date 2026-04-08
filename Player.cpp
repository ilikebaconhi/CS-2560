#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player(string playerName = "Player", int startingChips = 100) {
    name = playerName;
    chips = startingChips;
}

bool Player::placeBet(int amount) {
    if (amount > chips || amount < 0) {
        return false;
    }

    currentBet = amount;
    chips -= currentBet;
    return true;
}

void Player::winBet() {
    chips += (currentBet * 2);
}

void Player::loseBet() {
    // do nothing
}

void Player::pushBet() {
    chips += currentBet;
}

int Player::getChips() const {
    return chips;
}

int Player::getCurrentBet() const {
    return currentBet;
}

int Player::getHandValue() const{
    return hand.totalValue();
}

string Player::getName() const {
    return name;
}

void Player::printHand() {
    hand.printHand();
}
