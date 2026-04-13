#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

void initializeGame(Deck& gameDeck, Player& user, AIPlayer& A1, AIPlayer& A2, AIPlayer& dealer, int& wagerAmount) {
    vector<Player*> players = { &user, &A1, &A2, &dealer };
    vector<AIPlayer*> AIPlayers = { &A1, &A2, &dealer };

    dealer.resetCount();
    A1.resetCount();
    A2.resetCount();
    user.clearHand();
    dealer.clearHand();
    A1.clearHand();
    A2.clearHand();
    cout << "Welcome to the BlackJack Table." << endl;
    cout << "How many chips would you like to wager? You currently have " << user.getChips() << " chips." << endl;
    cin >> wagerAmount;
    user.placeBet(wagerAmount);
    Card c1 = user.addCard(gameDeck);
    dealer.observeCard(c1);
    A1.observeCard(c1);
    A2.observeCard(c1);
    Card c2 = user.addCard(gameDeck);
    A1.observeCard(c2);
    A2.observeCard(c2);
    dealer.observeCard(c2);
    cout << "Your hand is: " << endl;
    user.printHand();
}

int main() {
    string playAgain = "yes";
    string playerName;
    string drawAnswer;
    int wagerAmount;
    Deck gameDeck;

    int gamesPlayed = 0;
    AIPlayer dealer("Dealer", 1000);
    AIPlayer A1("Joe", 1000);
    AIPlayer A2("Bobby", 1000);
    cout << "Welcome, please enter your name: ";
    cin >> playerName;
    Player user(playerName, 1000);
    initializeGame(gameDeck, user, A1, A2, dealer, wagerAmount);
    cout << "Do you want to stand or hit?" << endl;
    cin >> drawAnswer;
  while (playAgain == "yes") {
    bool blackJack = false;
    bool youLose = false;
    bool AI1Lose = false;
    if (user.getHandValue() == 21) {
        blackJack = true;
        break;
    }

    if (drawAnswer == "hit") {
      user.addCard(gameDeck);
      cout << "Your hand is: " << endl;
      user.printHand();

      int handVal = user.getHandValue();
      if (handVal > 21) {
        cout << "<Bust!>" << endl;
        youLose = true;
        break;
      } else if (user.getHandValue() == 21) {
        cout << "You win!";
        blackJack = true;
      } else {
        cout << "Do you want to stand or hit?" << endl;
        cin >> drawAnswer;
      }
    } else if (drawAnswer == "stand") {
      cout << "Your turn has ended, it is now " << A1.getName() << "'s turn" << endl;
      A1.makeBet();
      Card c3 = A1.addCard(gameDeck);
      dealer.observeCard(c3);
      A2.observeCard(c3);
      Card c4 = A1.addCard(gameDeck);
      dealer.observeCard(c4);
      A2.observeCard(c4);
      if (!A1.shouldHit()) {
        cout << A1.getName() << " stands" << endl;
      } else {
        while (A1.shouldHit() && !AI1Lose) {
            cout << A1.getName() << " hits" << endl;
            Card temp = A1.addCard(gameDeck);
            A1.observeCard(temp);
            cout << A1.getName() << "'s hand is: " << endl;
            A1.printHand();
            if (A1.getHandValue() > 21) {
                cout << A1.getName() << " <Bust!>" << endl;
                AI1Lose = true;
                break;
            } else if (A1.getHandValue() == 21) {
                cout << A1.getName() << " wins!";
                blackJack = true;
                break;
            }
        }  
      }
    }

    cout << "Do you want to stand or hit?" << endl;
    cin >> drawAnswer;

    if (blackJack) {
    break;
    }
    
  }
    
}
