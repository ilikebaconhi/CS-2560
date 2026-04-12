#include "Hand.h"
#include <iostream>
#include <string>
using namespace std;

Hand::Hand() {
    currentPosition = -1;
    acePosition = -1;
    isAce = false;
}

Card Hand::getCard(int pos){
    return cards[pos];
}

void Hand::addCard(Deck& temp) {
    Card toAdd = temp.getCard();
    currentPosition++;
    cards.push_back(toAdd);

    if (toAdd.getFace() == "Ace") {
        isAce = true;
        acePosition = currentPosition;
    }

    if (isAce && totalValue() > 21) {
        cards[acePosition].setValue(1);
    }      
}

int Hand::totalValue() {
    int total = 0;
    int aceCount = 0;

    for (int i = 0; i < static_cast<int>(cards.size()); i++) {
        total += cards[i].getValue();
        if (cards[i].getFace() == "Ace") {
            aceCount++;
        }
    }

    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }

    return total;
}

void Hand::printHand() {
    int num = totalValue();

    for (int i = 0; i < cards.size(); i++) {
        Card temp = cards[i];
        temp.printCard();
    }

    cout << "<" << num << " points>" << endl;
}
