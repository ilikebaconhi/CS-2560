#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card {
private:
    string face;
    string suite;
    int value;

public:
    Card(string face, string suit, int value);

    string getFace() const ;
    string getSuite() const ;
    int getValue() const ;

    void setValue(int newVal);
    void printCard() const;
};

#endif