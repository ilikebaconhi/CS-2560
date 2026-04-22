# BlackJack

## Description  

This is a simple command-line Blackjack game written in C++. You play against a dealer along with a few AI players. The game handles dealing cards, calculating hand values, and basic gameplay flow. The AI players also keep track of cards that have been played to get a rough idea of how good the deck is, which influences their decisions.

---

## How to Compile and Run

### Prerequisites

- A C++ compiler such as `g++` (with support for standard libraries)

### Compilation

```bash
g++ Game.cpp AIPlayer.cpp Card.cpp Deck.cpp Hand.cpp Player.cpp -o blackjack
```

### Running the Program

```bash
./blackjack
```

---

## Gameplay Instructions

### Blackjack Rules

> "A blackjack game has a dealer and one or more players. Each player plays against the dealer. All players get two cards to begin and can ask for more until they bust (their total exceeds 21) or they stand (are happy with the total of their cards). Face cards count 10, ace may be 1 or 11. The dealer is dealt one card face up and one face down, and plays a fixed strategy: hit 16 or less, stand on 17 or more. The player loses if they bust, wins if they do not bust and the dealer does. Otherwise the player wins if her total is closer to 21 than the dealer's. No money changes hands in the case of ties. If the player's first two cards total 21, this is a blackjack and they win 1.5 times their bet (unless the dealer also has one and a tie results)."  
> — [Duke University Blackjack Rules](https://sites.math.duke.edu/~rtd/MEC/prob/blackjack.html)
---

### How to Play

1. Enter your name and place a bet (minimum 5 chips).
2. You will be dealt two cards.
3. Choose one of the following:
   - **Hit** → take another card
   - **Stand** → keep your current hand
4. Try to get as close to **21** as possible without going over.
5. After your turn:
   - Other players and the dealer will take their turns automatically.
6. The winner is whoever has a hand closest to 21 without busting.

### Special Rules

- Going over 21 is a **bust** (automatic loss).
- If you and the dealer have the same value, it’s a **push** (tie).
- Getting 21 with your first two cards is a **Blackjack** and wins immediately.

### Game End

- You can keep playing rounds until you run out of chips or choose to stop.
- 
## Code Structure and Class Descriptions

The program is organized into several classes and helper functions to separate game logic, player behavior, and game flow:

- **Card / Deck / Hand**
  - `Card` represents a single playing card.
  - `Deck` manages the collection of cards and handles shuffling and dealing.
  - `Hand` stores a player’s cards and calculates hand values.

- **Player / AIPlayer**
  - `Player` handles user-related actions such as betting, drawing cards, and tracking chips.
  - `AIPlayer` extends player behavior with automated decision-making (hit/stand and betting strategy).

- **Game Flow (main.cpp)**
  - Controls the overall game loop (rounds, replay, and termination).
  - Uses helper functions to keep logic modular:
    - `setupGame()` initializes each round (bets, shuffle, initial deal).
    - `handlePlayerTurn()` manages the user’s turn.
    - `playAITurn()` runs AI and dealer turns.
    - `resolveBets()` determines outcomes and updates chips.
    - `printResults()` and `printEndResults()` display game statistics.
