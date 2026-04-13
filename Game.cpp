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
    dealer.resetCount();
    A1.resetCount();
    A2.resetCount();
    user.clearHand();
    dealer.clearHand();
    A1.clearHand();
    A2.clearHand();
    bool blackJack = false;
    bool youLose = false;
    cout << "Welcome to the BlackJack Table." << endl;
    cout << "How many chips would you like to wager?" << endl;
    cin >> wagerAmount;
    user.placeBet(wagerAmount);
    Card c1 = user.drawCard(gameDeck);
    dealer.observeCard(c1);
    A1.observeCard(c1);
    A2.observeCard(c1);
    Card c2 = user.drawCard(gameDeck);
    A1.observeCard(c2);
    A2.observeCard(c2);
    dealer.observeCard(c2);
    if(user.getHandValue() == 21){
      blackJack = true;
    }
    cout << "Your hand is: " << endl;
    user.printHand();
    cout << "Do you want to stand or hit?" << endl;
    cout << endl;
    cin >> drawAnswer;
    while(drawAnswer == "hit"){
      user.addCard(gameDeck);
      cout << "Your hand is: " << endl;
      user.printHand();
      int handVal = user.getHandValue();
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
    if(!youLose){
      cout << "Your turn has ended, it is now " << A1.getName() << "'s turn" << endl;
      A1.makeBet();
      Card c3 = A1.drawCard(gameDeck);
      dealer.observeCard(c3);
      A2.observeCard(c3);
      Card c4 = A1.drawCard(gameDeck);
      dealer.observeCard(c4);
      A2.observeCard(c4);
      while(A1.shouldHit()){
        cout << A1.getName() << " hits" << endl;
        Card temp = A1.drawCard(gameDeck);
        A1.observeCard(temp);
        A1.printHand();
      }  
      
      
    }
    
    
    
  
  
  
  
  }
}

