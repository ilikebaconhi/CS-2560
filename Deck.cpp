#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Deck.h"
#include "Card.h"
using namespace std;  

Deck::Deck() {
    srand(time(0));

    nextCard = -1;

    string face = "";
    string suit = "";
    int value = 0;

    for(int o = 0; o < 4; o++){

        switch(o){
            case 0:
                suit = "Spades";
                break;
            case 1:
                suit = "Hearts";
                break;
            case 2:
                suit = "Diamonds";
                break;
            case 3:
                suit = "Clubs";
                break;
        }

        for(int i = 1; i < 14; i++){

            value = i;

            switch(i){
                case 1:
                    face = "Ace";
                    value = 11;
                    break;
                case 2:
                    face = "Two";
                    break;
                case 3:
                    face = "Three";
                    break;
                case 4:
                    face = "Four";
                    break;
                case 5:
                    face = "Five";
                    break;
                case 6:
                    face = "Six";
                    break;
                case 7:
                    face = "Seven";
                    break;
                case 8:
                    face = "Eight";
                    break;
                case 9:
                    face = "Nine";
                    break;
                case 10:
                    face = "Ten";
                    break;
                case 11:
                    face = "Jack";
                    value = 10;
                    break;
                case 12:
                    face = "Queen";
                    value = 10;
                    break;
                case 13:
                    face = "King";
                    value = 10;
                    break;
            }

            deck.push_back(Card(face, suit, value));
        }
    }
}

Card Deck::getCard(){
    nextCard = rand() % 26;
    Card randomCard = deck[nextCard];
    deck.erase(deck.begin() + nextCard);
    return randomCard;

}

void Deck::shuffle(){

    for(int i = 0; i < deck.size(); i++){
        int r = rand() % deck.size();

        Card temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }

    nextCard = -1;
}