#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"

#include <iostream>
#include <thread>
#include <chrono>
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
    cout << "How many chips would you like to wager? You currently have "
         << user.getChips() << " chips." << endl;

    cin >> wagerAmount;

    while (wagerAmount > user.getChips() || wagerAmount < 0) {
        cout << "Invalid Number of chips (You don't have that many or you tried to bet negative chips)" << endl;
        cout << endl;
        cout << "How many chips would you like to wager? You currently have "
             << user.getChips() << " chips." << endl;
        cin >> wagerAmount;
    }

    user.placeBet(wagerAmount);
}


void determineBetOutcome(Player& p, AIPlayer& dealer, bool playerLose) {
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

void pause(int ms) {
    this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void playAITurn(AIPlayer& ai, Deck& deck, AIPlayer& dealer, AIPlayer& A1, AIPlayer& A2, bool& aiLose, bool isDealer = false) {
    pause(500);
    cout << endl;
    cout << ai.getName() << "'s turn has started" << endl;
    cout << endl;
    pause(500);

    if (!isDealer) {
        int bet = ai.makeBet();
        ai.placeBet(bet);
    }

    Card newCard = ai.addCard(deck);
    dealer.observeCard(newCard);
    A1.observeCard(newCard);
    A2.observeCard(newCard);

    newCard = ai.addCard(deck);
    dealer.observeCard(newCard);
    A1.observeCard(newCard);
    A2.observeCard(newCard);

    cout << ai.getName() << "'s hand is: " << endl;
    pause(600);

    ai.printHand();

    pause(500);
    if (!ai.shouldHit()) {
        cout << ai.getName() << " stands" << endl;
        return;
    }

    while (ai.shouldHit() && !aiLose) {
        cout << endl;
        cout << ai.getName() << " hits" << endl;
        pause(800);
        Card newCard = ai.addCard(deck);
        dealer.observeCard(newCard);
        A1.observeCard(newCard);
        A2.observeCard(newCard);

        cout << endl;
        cout << ai.getName() << "'s hand is: " << endl;
        pause(600);
        ai.printHand();
        pause(500);
        if (ai.getHandValue() > 21) {
            cout << ai.getName() << " <Bust!>" << endl;
            aiLose = true;
            return;
        }
    }
    pause(500);
    cout << endl;
    cout << ai.getName() << " stands" << endl;
}


void printResults(int& gamesWon, int gamesPlayed, int userChips, string& playAgain) {
    cout << "\n=== Results ===" << endl;

    cout << "\nGames Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;

    double winRate = 0.0;
    if (gamesPlayed > 0) {
        winRate = (double)gamesWon / gamesPlayed * 100;
    }

    cout << "Win Rate: " << winRate << "%" << endl;
    cout << "Chips: " << userChips << endl;

    cout << "\nDo you want to play again? (yes/no): ";
    cin >> playAgain;
}

void printEndResults(bool youLose, Player user, AIPlayer dealer, AIPlayer A1, AIPlayer A2, int& gamesWon, int gamesPlayed, int userChips, string& playAgain) {
    int userHand = user.getHandValue();
    int dealerHand = dealer.getHandValue();
    int A1Hand = A1.getHandValue();
    int A2Hand = A2.getHandValue();
    if (youLose) {
        cout << "You lose.";
    }
    else if (dealerHand > 21 || userHand > dealerHand) {
        cout << "You win!" << endl;
        gamesWon++;
    } else {
        cout << "Push." << endl;
    }

    cout << "\n=== Results ===" << endl;

    cout << "\nGames Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;

    double winRate = 0.0;
    if (gamesPlayed > 0) {
        winRate = (double)gamesWon / gamesPlayed * 100;
    }

    cout << "Win Rate: " << winRate << "%" << endl;
    cout << "Chips: " << userChips << endl;

    cout << "\nDo you want to play again? (yes/no): ";
    cin >> playAgain;
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

        Card newCard = user.addCard(gameDeck);
        dealer.observeCard(newCard);
        A1.observeCard(newCard);
        A2.observeCard(newCard);

        newCard = user.addCard(gameDeck);
        A1.observeCard(newCard);
        A2.observeCard(newCard);
        dealer.observeCard(newCard);


        cout << "Your hand is: " << endl;
        user.printHand();


        if (user.getHandValue() == 21) {
            cout << "BlackJack, You win" << endl;
            user.winBet();
            gamesWon++;

            printResults(gamesWon, gamesPlayed, user.getChips(), playAgain);
            continue;
        }

        cout << "\nDo you want to stand or hit? ";
        cin >> drawAnswer;


        while (drawAnswer == "hit") {
            newCard = user.addCard(gameDeck);
            dealer.observeCard(newCard);
            A1.observeCard(newCard);
            A2.observeCard(newCard);

            cout << "Your hand is: " << endl;
            user.printHand();

            int handVal = user.getHandValue();

            if (handVal > 21) {
                cout << "<Bust!>" << endl;
                pause(1200);
                youLose = true;
                break;
            }
            else {
                cout << "\nDo you want to stand or hit? ";
                cin >> drawAnswer;
            }
        }


        playAITurn(A1, gameDeck, dealer, A1, A2, AI1Lose);
        playAITurn(A2, gameDeck, dealer, A1, A2, AI2Lose);
        playAITurn(dealer, gameDeck, dealer, A1, A2, DealerLose, true);

        determineBetOutcome(user, dealer, youLose);
        determineBetOutcome(A1, dealer, AI1Lose);
        determineBetOutcome(A2, dealer, AI2Lose);


        printEndResults(youLose, user, dealer, A1, A2, gamesWon, gamesPlayed, user.getChips(), playAgain);
    }

    cout << "Thank you for playing" << endl;
}