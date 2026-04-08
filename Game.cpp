#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  string playAgain = "yes";
  string playerName;
  Deck gameDeck;
  Hand playerHand;
  Hand opponentHand;

  cout << "Welcome to the BlackJack Table." << endl;
  cout << "Please enter your name: ";
  cin >> playerName;

  playerHand.addCard(gameDeck);
  playerHand.addCard(gameDeck);

  playerHand.printHand();
}

