#include <iostream>
using namespace std;
#include<string>
#include <utility>
#include<vector>
#include <algorithm>
#include <random>


class Card {
protected:
    string suit;
    int rank;

public:
    Card(string  suit, const int&  rank) : suit(std::move(suit)), rank(rank){};

    string GetCardSuit() const{
        return suit;
    }
    int GetCardValue() const{
        if (rank>10) return 10;
        return rank;
    }
    void PrintRank() const{
        if (rank == 1)                            cout<<"Ace"<< " of "<<suit<<endl;
        else if (rank == 11)                      cout<<"Jack"<< " of "<<suit<<endl;
        else if (rank == 12)                      cout<<"Queen"<<" of "<<suit<<endl;
        else if (rank == 13)                      cout<<"King"<<" of "<<suit<<endl;
        else                                      cout<<rank<<" of "<<suit<<endl;
    }
    void PrintSuits() const{
        cout<<" "<<suit<<endl;

    }
};

class DeckOfCards{
protected:
    vector<Card> deck;

public:
    DeckOfCards(){
        string culori[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        for (auto & i : culori) {
            for (int rank = 1; rank <= 13; rank++) {
                deck.emplace_back(i, rank);
            }
        }
    }
    void AfiseazaPachet() {
        cout << "--- Continut Pachet (" << deck.size() << " carti) ---" << endl;
        for (Card& c : deck) {
            c.PrintRank();
        }
    }
    void ShuffleDeck() {
        random_device rd;
        mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
    }
    Card DealCards() {
        Card top = deck.back();
        deck.pop_back();
        return top;
    }
};

class Hand {
protected:
    vector<Card> cards;

public:
    void AddCard(const Card& c) {
        cards.push_back(c);
    }
    int GetTotal() {
        int total = 0;
        int aces = 0;

        for (Card& c : cards) {
            total += c.GetCardValue();
            if (c.GetCardValue() == 1) aces++;
        }

        for (int i = 0; i < aces; i++) {
            if (total + 10 <= 21) total += 10;
        }

        return total;
    }

    void PrintHand() {
        for (Card& c : cards) {
            c.PrintRank();
        }
    }
    void PrintHandHidden() const {
        cards[0].PrintRank();
        cout << "Carte ascunsa" << endl;
    }
    bool IsBlackjack() {
        if (cards.size() != 2) return false;

        bool hasAce = false;
        bool hasTen = false;

        for (Card& c : cards) {
            if (c.GetCardValue() == 1)  hasAce = true;
            if (c.GetCardValue() == 10) hasTen = true;
        }

        return hasAce && hasTen;
    }

};

int main() {
    DeckOfCards deck;
    deck.ShuffleDeck();

    Hand playerHand;
    Hand dealerHand;

    playerHand.AddCard(deck.DealCards());
    dealerHand.AddCard(deck.DealCards());
    playerHand.AddCard(deck.DealCards());
    dealerHand.AddCard(deck.DealCards());

    if (playerHand.IsBlackjack() && dealerHand.IsBlackjack()) {
        cout << "\nAmbii au Blackjack! Egalitate!" << endl;
        return 0;
    }
    if (playerHand.IsBlackjack()) {
        cout << "\nBlackjack! Tu castigi!" << endl;
        return 0;
    }
    if (dealerHand.IsBlackjack()) {
        cout << "\nDealerul are Blackjack! Dealer castiga!" << endl;
        return 0;
    }

    cout << "--- Mana ta ---" << endl;
    playerHand.PrintHand();
    cout << "Total: " << playerHand.GetTotal() << endl;

    cout << "\n--- Mana dealerului ---" << endl;
    dealerHand.PrintHandHidden();

    char choice;
    while (playerHand.GetTotal() < 21) {
        cout << "\nHit (h) sau Stand (s)? ";
        cin >> choice;

        if (choice == 'h') {
            playerHand.AddCard(deck.DealCards());
            playerHand.PrintHand();
            cout << "Total: " << playerHand.GetTotal() << endl;
        } else {
            break;
        }
    }
    if (playerHand.GetTotal() > 21) {
        cout << "\nAi depasit 21! Dealer castiga!" << endl;
        return 0;
    }
    cout << "\n--- Dealerul joaca ---" << endl;
    while (dealerHand.GetTotal() < 17) {
        dealerHand.AddCard(deck.DealCards());
    }
    cout << "\n--- Dealerul isi dezvaluie mana ---" << endl;
    dealerHand.PrintHand();
    cout << "Total dealer: " << dealerHand.GetTotal() << endl;

    if (dealerHand.GetTotal() > 21) {
        cout << "\nDealerul a depasit 21! Tu castigi!" << endl;
    } else if (playerHand.GetTotal() > dealerHand.GetTotal()) {
        cout << "\nTu castigi!" << endl;
    } else if (playerHand.GetTotal() < dealerHand.GetTotal()) {
        cout << "\nDealer castiga!" << endl;
    } else {
        cout << "\nEgalitate!" << endl;
    }

    return 0;
};
