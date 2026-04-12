#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player(string playerName, int startingChips) {
    name = playerName;
    chips = startingChips;
}

void Player::placeBet(int amount) {
    currentBet = amount;
    chips -= currentBet;
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

int Player::getHandValue() {
    return hand.totalValue();
}

string Player::getName() const {
    return name;
}

void Player::printHand() {
    hand.printHand();
}
