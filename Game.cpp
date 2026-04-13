#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;
void initializeGame(Player& user, Hand& userHand, Deck& gameDeck, int& wagerAmount) {
    cout << "Welcome to the BlackJack Table." << endl;
    cout << "How many chips would you like to wager? (Available: " << user.getChips() << "): ";    
    cin >> wagerAmount;

    while (wagerAmount > user.getChips() || wagerAmount < 0) {
        cout << "Invalid Number of Chips (You don't have that many or you tried to bet negative chips)" << endl;
        cout << "How many chips would you like to wager? (Available: " << user.getChips() << "): ";    
        cin >> wagerAmount;
    }

    user.placeBet(wagerAmount);
    userHand.addCard(gameDeck);
    userHand.addCard(gameDeck);
    
}

int main() {
    string playAgain = "yes";
    string playerName;
    string drawAnswer;
    Deck gameDeck;
    Hand playerHand;
    int wagerAmount;
    int gamesPlayed = 0;
    AIPlayer dealer("Dealer", 1000);
    AIPlayer A1("Joe", 1000);
    AIPlayer A2("Bobby", 1000);
    cout << "Welcome, please enter your name: ";
    cin >> playerName;
    Player user(playerName, 1000);

    initializeGame(user, playerHand, gameDeck, wagerAmount);
    while (playAgain == "yes") {
        Hand opponentHand;
        bool blackJack = false;
        bool youLose = false;
        string drawAnswer;

        cout << "Your hand is: " << endl;
        playerHand.printHand();

        if (playerHand.totalValue() == 21) {
            blackJack = true;
            cout << "Blackjack! You win!" << endl;
            user.winBet();
            playerHand.clearHand();
        } else {
            while (true) {
                cout << "Would you like to hit or stand? ";
                cin >> drawAnswer;
                cout << endl;

                if (drawAnswer == "hit") {
                    playerHand.addCard(gameDeck);

                    cout << "Your hand is: " << endl;
                    playerHand.printHand();

                    int handVal = playerHand.totalValue();

                    if (handVal > 21) {
                        cout << "Bust! You lose this round." << endl;
                        user.loseBet();
                        youLose = true;
                        playerHand.clearHand();
                        break;
                    } 
                    else if (handVal == 21) {
                        cout << "Blackjack! You win!" << endl;
                        user.winBet();
                        playerHand.clearHand();
                        break;
                    }
                } 
                else if (drawAnswer == "stand") {
                    break;
                } 
                else {
                    cout << "Invalid choice. Please enter hit or stand." << endl;
                }
            }
        }

        cout << "Play again? ";
        cin >> playAgain;

        if (playAgain == "yes") {
            initializeGame(user, playerHand, gameDeck, wagerAmount);
        }

        cout << endl;
    }
}
