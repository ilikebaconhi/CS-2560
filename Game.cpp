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
#include <cmath>
#include <cstdlib>

using namespace std;

//reduces repetition in main
void dealCardToUser(Player& user, Deck& deck, AIPlayer& dealer, AIPlayer& A1, AIPlayer& A2) {
    Card newCard = user.addCard(deck);
    dealer.observeCard(newCard);
    A1.observeCard(newCard);
    A2.observeCard(newCard);
}

void setupGame(Deck& gameDeck, Player& user, AIPlayer& A1, AIPlayer& A2, AIPlayer& dealer, int& gamesPlayed) {
    vector<Player*> players = { &user, &A1, &A2, &dealer };
    vector<AIPlayer*> AIPlayers = { &A1, &A2, &dealer };

    int wagerAmount;
    gamesPlayed++;

    for (AIPlayer* aiPlayer : AIPlayers) {
        aiPlayer->resetCount();
    }

    for (Player* player : players) {
        player->clearHand();
    }
    cout << endl;
    cout << "Welcome to the BlackJack Table." << endl;
    cout << "The other players at the table are "  << A1.getName() << ", " << A2.getName() << ", and the dealer." << endl;
    cout << "How many chips would you like to wager? You currently have "
         << user.getChips() << " chips. The minimum bet is 5." << endl;

    // fix error checking later...
    while (!(cin >> wagerAmount)) {
        cout << "Error: Not a number." << endl;
        cin.clear(); // reset failbit
        cin.ignore(1000, '\n'); // skip bad input
        cout << "How many chips would you like to wager? You currently have "
         << user.getChips() << " chips. The minimum bet is 5." << endl;
    }

    while (wagerAmount > user.getChips() || wagerAmount < 0) {
        cout << "Invalid Number of chips (You don't have that many or you tried to bet negative chips)" << endl;
        cout << endl;
        cout << "How many chips would you like to wager? You currently have "
            << user.getChips() << " chips." << endl;
    }  

    if (wagerAmount < 5) {
        wagerAmount = 5;
    }
    
    user.placeBet(wagerAmount);
    gameDeck.shuffle();
    dealCardToUser(user, gameDeck, dealer, A1, A2);
    dealCardToUser(user, gameDeck, dealer, A1, A2);
    cout << "Your hand is: " << endl;
    user.printHand();
}

void resolveBets(Player& p, AIPlayer& dealer, bool playerLose) {
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

void printEndResults(bool youLose, Player& user, AIPlayer& dealer, int& gamesWon, int gamesPlayed, int userChips, string& playAgain) {
    int userHand = user.getHandValue();
    int dealerHand = dealer.getHandValue();
    if (youLose) {
        cout << "You lose." << endl;
    }
    else if (dealerHand > 21 || userHand > dealerHand) {
        cout << "You win!" << endl;
        gamesWon++;
    }
    else if (dealerHand > userHand) {
        cout << "You lose." << endl;
    }
    else {
        cout << "Push." << endl;
    }

    printResults(gamesWon, gamesPlayed, user.getChips(), playAgain);
}

bool handlePlayerTurn(Player& user, Deck& gameDeck, AIPlayer& dealer, AIPlayer& A1, AIPlayer& A2, int gamesPlayed, int& gamesWon, string& playAgain, bool& youLose) {
    string drawAnswer;
    if (user.getHandValue() == 21) {
        cout << "BlackJack, You win" << endl;
        user.winBlackJackBet();
        gamesWon++;
        printResults(gamesWon, gamesPlayed, user.getChips(), playAgain);
        return false;
    }

    cout << "\nDo you want to stand or hit? ";
    cin >> drawAnswer;

    while (drawAnswer != "hit" && drawAnswer != "Hit" && drawAnswer != "stand" && drawAnswer != "Stand") {
        cout << "Invalid BlackJack Move. Type \"hit\" or \"stand\"" << endl;
        cin >> drawAnswer;
    }

    while (drawAnswer == "hit" || drawAnswer == "Hit") {
        dealCardToUser(user, gameDeck, dealer, A1, A2);

        cout << "Your hand is: " << endl;
        user.printHand();

        int handVal = user.getHandValue();

        if (handVal > 21) {
            cout << "<Bust!>" << endl;
            pause(1000);
            youLose = true;
            break;
        }
        else {
            cout << "\nDo you want to stand or hit? ";
            cin >> drawAnswer;
        }
    }
    return true;
}

int main() {
    srand(time(0));

    string playerName;
    cout << "Welcome! Please enter your name: ";
    getline(cin, playerName);

    Player user(playerName, 1000);
    AIPlayer dealer("Dealer", 1000);
    AIPlayer A1("Joe", 1000);
    AIPlayer A2("Bobby", 1000);
    Deck gameDeck;

    string playAgain = "yes";
    int gamesWon = 0;
    int gamesPlayed = 0;

    while (playAgain == "yes" || playAgain == "Yes") {

        setupGame(gameDeck, user, A1, A2, dealer, gamesPlayed);

        bool youLose = false;
        bool AI1Lose = false;
        bool AI2Lose = false;
        bool DealerLose = false;

        bool continueRound = handlePlayerTurn(user, gameDeck, dealer, A1, A2, gamesPlayed, gamesWon, playAgain, youLose);
        if (!continueRound) {
            continue;
        }

        playAITurn(A1, gameDeck, dealer, A1, A2, AI1Lose);
        playAITurn(A2, gameDeck, dealer, A1, A2, AI2Lose);
        playAITurn(dealer, gameDeck, dealer, A1, A2, DealerLose, true);

        resolveBets(user, dealer, youLose);
        resolveBets(A1, dealer, AI1Lose);
        resolveBets(A2, dealer, AI2Lose);

        printEndResults(youLose, user, dealer, gamesWon, gamesPlayed, user.getChips(), playAgain);

        if (user.getChips() < 5) {
            cout << "You have run out of chips, you may no longer play" << endl;
            break;
        }
    }

    cout << "Thank you for playing" << endl;
}