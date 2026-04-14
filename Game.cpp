#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

void initializeGame(Deck& gameDeck, Player& user, AIPlayer& A1, AIPlayer& A2, AIPlayer& dealer, int& wagerAmount) {
    vector<Player*> players = { &user, &A1, &A2};
    vector<AIPlayer*> AIPlayers = {&A1, &A2};

    dealer.resetCount();
    A1.resetCount();
    A2.resetCount();
    user.clearHand();
    dealer.clearHand();
    A1.clearHand();
    A2.clearHand();
    cout << "Welcome to the BlackJack Table." << endl;
    cout << "Other players at the table: "
        << A1.getName() << " and " << A2.getName() << "." << endl;
    cout << "How many chips would you like to wager? You currently have " << user.getChips() << " chips." << endl;
    cin >> wagerAmount;

    while (wagerAmount > user.getChips() || wagerAmount < 0) {
        cout << "Invalid Number of chips (You don't have that many or you tried to bet negative chips)" << endl;
        cout << endl;
        cout << "How many chips would you like to wager? You currently have " << user.getChips() << " chips." << endl;
        cin >> wagerAmount;
    }
    user.placeBet(wagerAmount);
    cout << A1.getName() << " has " << A1.getChips() << " chips." << endl;
    cout << A1.getName() << " bets " << A1.makeBet() << " chips." << endl;
    cout << A2.getName() << " has " << A1.getChips() << " chips." << endl;
    cout << A2.getName() << " bets " << A2.makeBet() << " chips." << endl;

    for(int round = 0; round < 2; round++){
        for(Player* current : players){
            Card c = current->addCard(gameDeck);
            dealer.observeCard(c);

            for(AIPlayer* ai : AIPlayers){
                // AI should NOT observe its own card
                if(ai != current){
                    ai->observeCard(c);
                }
            }
        }
    }

    //dealer has a hidden card
    Card c1 = dealer.addCard(gameDeck);
    A1.observeCard(c1);
    A2.observeCard(c1);
    //hole card
    Card c2 = dealer.addCard(gameDeck);
    cout << endl;
    cout << "Your hand is: " << endl;
    user.printHand();
}

void playAITurns(vector<AIPlayer*>& AIPlayers, Deck& gameDeck, bool youLose) {
    bool blackJack = false;
    for (int i=0; i < AIPlayers.size(); i++) {
        AIPlayer* currentPlayer = AIPlayers.at(i);
        if (i == 0 && !youLose) {
            cout << "Your turn has ended, it is now " << currentPlayer->getName() << "'s turn" << endl;
        } else {
            cout << endl;
            cout << AIPlayers.at((i - 1 + AIPlayers.size()) % AIPlayers.size())->getName() << "'s turn has ended, it is now " << currentPlayer->getName() << "'s turn" << endl;
        }

        cout << currentPlayer->getName() << "'s hand is: " << endl;
        currentPlayer->printHand();
        if (!currentPlayer->shouldHit()) {
            cout << currentPlayer->getName() << " stands" << endl;
            cout << endl;
        } else {
            while (currentPlayer->shouldHit() && currentPlayer->getHandValue() < 21) {
                cout << currentPlayer->getName() << " hits" << endl;
                cout << endl;
                Card temp = currentPlayer->addCard(gameDeck);
                currentPlayer->observeCard(temp);
                cout << currentPlayer->getName() << "'s hand is: " << endl;
                currentPlayer->printHand();
                cout << endl;
                if (currentPlayer->getHandValue() > 21) {
                    cout << currentPlayer->getName() << " <Bust!>" << endl;
                    AIPlayers.erase(AIPlayers.begin() + i);
                } else if (currentPlayer->getHandValue() == 21) {
                    cout << currentPlayer->getName() << " wins!";
                    blackJack = true;
                    return;
                }
            }  
            
            if (currentPlayer->getHandValue() < 21) {
                cout << currentPlayer->getName() << " stands" << endl;
            }
            
        }
    }
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
    bool youLose = false;
    vector<AIPlayer*> AIPlayers = {&A1, &A2};

    cout << "Welcome, please enter your name: ";
    cin >> playerName;
    Player user(playerName, 1000);
    initializeGame(gameDeck, user, A1, A2, dealer, wagerAmount);

  while (playAgain == "yes") {
    bool blackJack = false;
    if (user.getHandValue() == 21) {
        blackJack = true;
        break;
    }
    if (!youLose) {
        cout << "Do you want to stand or hit?" << endl;
        cin >> drawAnswer;
    } else {
        playAITurns(AIPlayers, gameDeck, youLose);
    }

    if (drawAnswer == "hit") {
      user.addCard(gameDeck);
      cout << endl;
      cout << "Your hand is: " << endl;
      user.printHand();

      int handVal = user.getHandValue();
      if (handVal > 21) {
        cout << "<Bust!>" << endl;
        youLose = true;
        drawAnswer = "stand";
      } else if (handVal == 21) {
        cout << "You win!";
        blackJack = true;
      }
    } else if (drawAnswer == "stand") {
        cout << endl;
        playAITurns(AIPlayers, gameDeck, youLose);
    } else {
        cout << "Invalid input. Type 'hit' to draw a card or 'stand' to hold: ";    
    }


    for (AIPlayer* Player : AIPlayers) {
        if (Player->getHandValue() == 21) {
            cout << Player->getName() << " got blackjack!. They win!";
            youLose = true;
            Player->winBet();
            break;
        }
    }
    
    //fix the problem where everybody stands it results in an infinite loop
  }
    
}
