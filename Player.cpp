#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player(string playerName, int startingChips) {
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

void Player::winBlackJackBet() {
    chips += currentBet * 2.5;
}

void Player::loseBet() {
    // do nothing
}

void Player::pushBet() {
    chips += currentBet;
}

Hand Player::getHand() const{
    return hand;
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

Card Player::addCard(Deck& deck) {
    Card drawn = deck.getCard();
    hand.addSpecificCard(drawn);
    return drawn;
}

void Player::clearHand() {
    hand = Hand();
}
