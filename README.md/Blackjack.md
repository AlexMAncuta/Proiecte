# Blackjack (C++)

A console-based Blackjack game played against a dealer, written in C++ using object-oriented programming.

## How to compile and run

```bash
g++ -o blackjack main.cpp -std=c++17
./blackjack
```

## How to play

1. The deck is shuffled automatically at the start of each game.
2. You and the dealer each receive 2 cards. One of the dealer's cards is hidden.
3. On your turn, choose:
   - `h` — **Hit**: draw another card
   - `s` — **Stand**: keep your current hand
4. If your total exceeds 21, you **bust** and the dealer wins.
5. After you stand, the dealer reveals their hand and draws until reaching at least 17.
6. The hand closest to 21 without going over wins.

### Special rules implemented
- **Blackjack**: an Ace + any 10-value card on the initial deal wins instantly (unless both players have it — that's a tie).
- **Aces**: counted as 11 if it doesn't cause a bust, otherwise as 1.
- **Face cards** (Jack, Queen, King): worth 10 points.

## Project structure

```
main.cpp
│
├── class Card          — represents a single playing card
│     ├── GetCardValue()    — returns point value (face cards = 10, Ace = 1 or 11)
│     └── PrintRank()       — prints human-readable card name
│
├── class DeckOfCards   — a standard 52-card deck
│     ├── ShuffleDeck()     — randomizes card order
│     └── DealCards()       — removes and returns the top card
│
└── class Hand          — holds a player's or dealer's cards
      ├── AddCard()         — adds a card to the hand
      ├── GetTotal()        — calculates hand value (handles Ace logic)
      ├── IsBlackjack()     — checks for natural Blackjack
      ├── PrintHand()       — prints all cards
      └── PrintHandHidden() — prints only the first card (used for dealer)
```

## Technologies used

- **Language**: C++17
- **Standard library**: `<vector>`, `<string>`, `<algorithm>`, `<random>`
- **Concepts**: OOP (classes, inheritance, encapsulation), vectors, randomization with `mt19937`

## Example output

```
--- Mana ta ---
Ace of Hearts
King of Spades
Total: 21

--- Mana dealerului ---
7 of Clubs
Carte ascunsa

Blackjack! Tu castigi!
```
