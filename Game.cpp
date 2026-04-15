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

void playAITurn(AIPlayer& ai, Deck& deck, AIPlayer& dealer, AIPlayer& A1, AIPlayer& A2, bool& aiLose, bool isDealer = false) {

    cout << ai.getName() << "'s turn has started" << endl;

    if (!isDealer) {
        int bet = ai.makeBet();
        ai.placeBet(bet);
    }

    Card temp = ai.addCard(deck);
    dealer.observeCard(temp);
    A1.observeCard(temp);
    A2.observeCard(temp);

    temp = ai.addCard(deck);
    dealer.observeCard(temp);
    A1.observeCard(temp);
    A2.observeCard(temp);

    cout << ai.getName() << "'s hand is: " << endl;
    ai.printHand();

    if (!ai.shouldHit()) {
        cout << ai.getName() << " stands" << endl;
        return;
    }

    while (ai.shouldHit() && !aiLose) {
        cout << ai.getName() << " hits" << endl;

        Card temp = ai.addCard(deck);
        dealer.observeCard(temp);
        A1.observeCard(temp);
        A2.observeCard(temp);

        cout << ai.getName() << "'s hand is: " << endl;
        ai.printHand();

        if (ai.getHandValue() > 21) {
            cout << ai.getName() << " <Bust!>" << endl;
            aiLose = true;
            return;
        }
    }

    cout << ai.getName() << " stands" << endl;
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
    playAITurn(A1, gameDeck, dealer, A1, A2, AI1Lose);
    playAITurn(A2, gameDeck, dealer, A1, A2, AI2Lose);
    playAITurn(dealer, gameDeck, dealer, A1, A2, DealerLose, true);

    
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
