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
#include <vector>

using namespace std;

// adds pausing to improve game flow
void pause(int ms) {
    this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// reduces repetition in main
void dealCardToUser(Player& user, Deck& deck, AIPlayer& dealer, AIPlayer& A1, AIPlayer& A2) {
    Card newCard = user.addCard(deck);
    dealer.observeCard(newCard);
    A1.observeCard(newCard);
    A2.observeCard(newCard);
}

// deals a card to an AI player and lets the other AIs observe it if visible
void dealCardToAI(AIPlayer& current, Deck& deck, AIPlayer& dealer, AIPlayer& A1, AIPlayer& A2, bool visible = true) {
    Card newCard = current.addCard(deck);

    if (!visible) {
        return;
    }

    if (&dealer != &current) {
        dealer.observeCard(newCard);
    }
    if (&A1 != &current) {
        A1.observeCard(newCard);
    }
    if (&A2 != &current) {
        A2.observeCard(newCard);
    }
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
    cout << "The other players at the table are "
         << A1.getName() << ", " << A2.getName() << ", and the dealer." << endl;

    while (true) {
        cout << "How many chips would you like to wager? You currently have "
             << user.getChips() << " chips. The minimum bet is 5." << endl;

        if (!(cin >> wagerAmount)) {
            cout << "Error: Invalid number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (wagerAmount < 0 || wagerAmount > user.getChips()) {
            cout << "Invalid number of chips." << endl;
            continue;
        }

        if (wagerAmount < 5) {
            wagerAmount = 5;
        }

        break;
    }

    user.placeBet(wagerAmount);
    gameDeck.shuffle();

    // user initial hand
    dealCardToUser(user, gameDeck, dealer, A1, A2);
    dealCardToUser(user, gameDeck, dealer, A1, A2);

    // dealer initial hand: first visible, second hidden
    dealCardToAI(dealer, gameDeck, dealer, A1, A2, true);
    dealCardToAI(dealer, gameDeck, dealer, A1, A2, false);

    cout << "Your hand is: " << endl;
    user.printHand();
    cout << endl;
    pause(500);
    dealer.showDealerHand(false);
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

void playAITurn(AIPlayer& ai, Deck& deck, AIPlayer& dealer, AIPlayer& A1, AIPlayer& A2, bool& aiLose) {
    pause(500);
    cout << endl;
    cout << ai.getName() << "'s turn has started" << endl;
    cout << endl;
    pause(500);

    int bet = ai.makeBet();
    ai.placeBet(bet);

    dealCardToAI(ai, deck, dealer, A1, A2, true);
    dealCardToAI(ai, deck, dealer, A1, A2, true);

    cout << ai.getName() << "'s hand is: " << endl;
    pause(600);
    ai.printHand();

    pause(500);

    if (ai.getHandValue() == 21) {
        cout << ai.getName() << " has BlackJack!" << endl;
        ai.winBlackJackBet();
        return;
    }

    if (!ai.shouldHit()) {
        cout << ai.getName() << " stands" << endl;
        return;
    }

    while (ai.shouldHit() && !aiLose) {
        cout << endl;
        cout << ai.getName() << " hits" << endl;
        pause(800);

        dealCardToAI(ai, deck, dealer, A1, A2, true);

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

void playDealerTurn(AIPlayer& dealer, Deck& deck, AIPlayer& A1, AIPlayer& A2, bool& dealerLose) {
    pause(500);
    cout << endl;
    cout << "Dealer's turn has started" << endl;
    cout << endl;
    pause(500);

    cout << "Dealer reveals hidden card:" << endl;
    dealer.showDealerHand(true);

    const vector<Card>& dealerCards = dealer.getHand().getAllCards();
    if (dealerCards.size() >= 2) {
        A1.observeCard(dealerCards[1]);
        A2.observeCard(dealerCards[1]);
    }

    pause(500);

    while (dealer.getHandValue() < 17) {
        cout << endl;
        cout << "Dealer hits" << endl;
        pause(800);

        dealCardToAI(dealer, deck, dealer, A1, A2, true);

        cout << endl;
        cout << "Dealer's hand is: " << endl;
        pause(600);
        dealer.showDealerHand(true);
        pause(500);

        if (dealer.getHandValue() > 21) {
            cout << "Dealer <Bust!>" << endl;
            dealerLose = true;
            return;
        }
    }

    cout << endl;
    cout << "Dealer stands" << endl;
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
        playDealerTurn(dealer, gameDeck, A1, A2, DealerLose);

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