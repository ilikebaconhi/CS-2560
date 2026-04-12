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
  string drawAnswer;
  int wagerAmount;
  int gamesPlayed = 0;
  AIPlayer dealer("Dealer", 1000);
  AIPlayer A1("Joe", 1000);
  AIPlayer A2("Bobby", 1000);
  cout << "Welcome, please enter your name: ";
  cin >> playerName;
  Player user(playerName, 1000);
  while(playAgain == "yes"){
    Deck gameDeck;
    Hand playerHand;
    Hand opponentHand;
    bool blackJack = false;
    bool youLose = false;
    cout << "Welcome to the BlackJack Table." << endl;
    cout << "How many chips would you like to wager?" << endl;
    cin >> wagerAmount;
    user.placeBet(wagerAmount);
    playerHand.addCard(gameDeck);
    playerHand.addCard(gameDeck);
    if(playerHand.totalValue() == 21){
      blackJack = true;
    }
    cout << "Your hand is: " << endl;
    playerHand.printHand();
    cout << "Do you want to stand or hit?" << endl;
    cout << endl;
    cin >> drawAnswer;
    while(drawAnswer == "hit"){
      playerHand.addCard(gameDeck);
      cout << "Your hand is: " << endl;
      playerHand.printHand();
      int handVal = playerHand.totalValue();
      if(handVal > 21){
        cout << "<Bust!>" << endl;
        user.loseBet();
        youLose = true;
        break;
      }else{
        cout << "Do you want to stand or hit?" << endl;
        cout << endl;
        cin >> drawAnswer;
      }
    }
    
  
  
  
  
  }
}
