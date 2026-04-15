#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
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
    
}

void resolvePlayer(Player& p, AIPlayer& dealer, bool playerLose) {
    int playerTotal = p.getHandValue();
    int dealerTotal = dealer.getHandValue();

    if (playerLose || playerTotal > 21) {
        return; 
    }
    else if (dealerTotal > 21 || playerTotal > dealerTotal) {
        p.winBet();
    }
    else if (playerTotal == dealerTotal) {
        p.pushBet();
    }

}

int main() {
    srand(time(0));
    string playAgain = "yes";
    string playerName;
    string drawAnswer;
    int wagerAmount;
    Deck gameDeck;
    int gamesWon = 0;

    int gamesPlayed = 0;
    AIPlayer dealer("Dealer", 1000);
    AIPlayer A1("Joe", 1000);
    AIPlayer A2("Bobby", 1000);
    cout << "Welcome, please enter your name: ";
    cin >> playerName;
    Player user(playerName, 1000);
    
    
  while (playAgain == "yes") {
    initializeGame(gameDeck, user, A1, A2, dealer, wagerAmount);
    gameDeck.shuffle();
    bool youLose = false;
    bool AI1Lose = false;
    bool AI2Lose = false;
    bool DealerLose = false;
    gamesPlayed++;
    Card temp = user.addCard(gameDeck);
    dealer.observeCard(temp);
    A1.observeCard(temp);
    A2.observeCard(temp);
    temp = user.addCard(gameDeck);
    A1.observeCard(temp);
    A2.observeCard(temp);
    dealer.observeCard(temp);
    cout << "Your hand is: " << endl;
    user.printHand();
    if (user.getHandValue() == 21) {
      cout << "BlackJack, You win" << endl;
      user.winBet();
      gamesWon++;
      cout << "\nGames Played: " << gamesPlayed << endl;
      cout << "Games Won: " << gamesWon << endl;
      cout << "Chips: " << user.getChips() << endl;
      cout << "\nDo you want to play again? (yes/no): ";
      cin >> playAgain;

    continue;
    }
    cout << "Do you want to stand or hit? ";
    cin >> drawAnswer;
    while (drawAnswer == "hit") {
      temp = user.addCard(gameDeck);
      dealer.observeCard(temp);
      A1.observeCard(temp);
      A2.observeCard(temp);
      cout << "Your hand is: " << endl;
      user.printHand();

      int handVal = user.getHandValue();
      if (handVal > 21) {
        cout << "<Bust!>" << endl;
        youLose = true;
        break;
      } else {
        cout << "Do you want to stand or hit? ";
        cin >> drawAnswer;
      }
    }
      cout << "Your turn has ended, it is now " << A1.getName() << "'s turn" << endl;
      int bet = A1.makeBet();
      A1.placeBet(bet);
      temp = A1.addCard(gameDeck);
      dealer.observeCard(temp);
      A1.observeCard(temp);
      A2.observeCard(temp);
      temp = A1.addCard(gameDeck);
      dealer.observeCard(temp);
      A1.observeCard(temp);
      A2.observeCard(temp);
      cout << A1.getName() << "'s hand is: " << endl;
      A1.printHand();
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
            }
        }
        cout << A1.getName() << " stands" << endl;  
      }

      cout << A1.getName() <<"'s turn has ended, it is now " << A2.getName() << "'s turn" << endl;
      bet = A2.makeBet();
      A2.placeBet(bet);
      temp = A2.addCard(gameDeck);
      dealer.observeCard(temp);
      A1.observeCard(temp);
      A2.observeCard(temp);
      temp = A2.addCard(gameDeck);
      dealer.observeCard(temp);
      A1.observeCard(temp);
      A2.observeCard(temp);
      cout << A2.getName() << "'s hand is: " << endl;
      A2.printHand();
      if (!A2.shouldHit()) {
        cout << A2.getName() << " stands" << endl;
      } else {
        while (A2.shouldHit() && !AI2Lose) {
            cout << A2.getName() << " hits" << endl;
            Card temp = A2.addCard(gameDeck);
            A2.observeCard(temp);
            cout << A2.getName() << "'s hand is: " << endl;
            A2.printHand();
            if (A2.getHandValue() > 21) {
                cout << A2.getName() << " <Bust!>" << endl;
                AI2Lose = true;
            }
        }
        cout << A2.getName() << " stands" << endl;  
      }

      cout << A2.getName() <<"'s turn has ended, it is now " << dealer.getName() << "'s turn" << endl;
      temp = dealer.addCard(gameDeck);
      dealer.observeCard(temp);
      A1.observeCard(temp);
      A2.observeCard(temp);
      temp = dealer.addCard(gameDeck);
      dealer.observeCard(temp);
      A1.observeCard(temp);
      A2.observeCard(temp);
      cout << dealer.getName() << "'s hand is: " << endl;
      dealer.printHand();
      if (!dealer.shouldHit()) {
        cout << dealer.getName() << " stands" << endl;
      } else {
        while (dealer.shouldHit() && !DealerLose) {
            cout << dealer.getName() << " hits" << endl;
            Card temp = dealer.addCard(gameDeck);
            dealer.observeCard(temp);
            cout << dealer.getName() << "'s hand is: " << endl;
            dealer.printHand();
            if (dealer.getHandValue() > 21) {
                cout << dealer.getName() << " <Bust!>" << endl;
                DealerLose = true;
            }
        }
        cout << dealer.getName() << " stands" << endl;  
      }


    
    int userChipsBefore = user.getChips();

    resolvePlayer(user, dealer, youLose);
    resolvePlayer(A1, dealer, AI1Lose);
    resolvePlayer(A2, dealer, AI2Lose);

    int userTotal = user.getHandValue();
    int dealerTotal = dealer.getHandValue();

    cout << "\n=== Results ===" << endl;

    if (youLose) {
        cout << "You lose." << endl;
    }else if (dealerTotal > 21 || userTotal > dealerTotal) {
        cout << "You win!" << endl;
        gamesWon++;
    }
    else if (userTotal < dealerTotal) {
        cout << "Dealer wins." << endl;
    }
    else {
        cout << "Push." << endl;
    }


    cout << "\nGames Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    double winRate = 0.0;
    if (gamesPlayed > 0) {
      winRate = (double)gamesWon / gamesPlayed * 100; 
    }

    cout << "Win Rate: " << winRate << "%" << endl;
    cout << "Chips: " << user.getChips() << endl;

    cout << "\nDo you want to play again? (yes/no): ";
    cin >> playAgain;

  }
  cout << "Thank you for playing" << endl;
    
}
