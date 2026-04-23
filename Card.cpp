#include <iostream>
#include <string>
#include "Card.h"
using namespace std;    
Card::Card(string face, string suite, int value){
    this -> face = face;
    this -> suite = suite;
    this -> value = value;
}

string Card::getFace() const {
    return face;
}

int Card::getValue() const {
    return value;
}

string Card::getSuite() const {
    return suite;
}

void Card::setValue(int newVal){
    value = newVal;
}

void Card::printCard() const{
    cout << face << " of " << suite << " ";
}