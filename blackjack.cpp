#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

class Card {
public:
    string suit;
    string rank;
    int value;
    
    Card(string s, string r, int v) : suit(s), rank(r), value(v) {}
    
    string toString() { return rank + " of " + suit; }
};

class Deck {
private:
    vector<Card> cards;
    
public:
    Deck() {
        string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
        
        for (size_t s = 0; s < sizeof(suits)/sizeof(suits[0]); s++) {
            for (size_t i = 0; i < 13; i++) {
                cards.push_back(Card(suits[s], ranks[i], values[i]));
            }
        }
        shuffle();
    }
    
    void shuffle() {
        srand(time(0));
        for (size_t i = 0; i < cards.size(); i++) {
            size_t j = i + rand() % (cards.size() - i);
            swap(cards[i], cards[j]);
        }
    }
    
    Card deal() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

class Hand {
protected:
    vector<Card> cards;
    
public:
    void add(Card card) { cards.push_back(card); }
    
    int getTotal() {
        int total = 0;
        int aces = 0;
        
        for (size_t i = 0; i < cards.size(); i++) {
            total += cards[i].value;
            if (cards[i].rank == "Ace") aces++;
        }
        
        while (total > 21 && aces) {
            total -= 10;
            aces--;
        }
        
        return total;
    }
    
    void show(bool showFirst = true) {
        for (size_t i = 0; i < cards.size(); i++) {
            if (i == 0 && !showFirst) cout << "[hidden]\n";
            else cout << cards[i].toString() << "\n";
        }
    }
    
    Card getLastCard() { return cards.back(); }
};

class BlackjackGame {
private:
    Deck deck;
    Hand player;
    Hand dealer;
    
public:
    void play() {
        cout << "Welcome to Blackjack!\n\n";
        
        // Initial deal
        player.add(deck.deal());
        dealer.add(deck.deal());
        player.add(deck.deal());
        dealer.add(deck.deal());
        
        // Player's turn
        cout << "Dealer's hand:\n";
        dealer.show(false);
        cout << "\nYour hand (" << player.getTotal() << "):\n";
        player.show();
        
        while (player.getTotal() < 21) {
            cout << "\nHit or stand? (h/s): ";
            char choice;
            cin >> choice;
            
            if (tolower(choice) == 'h') {
                player.add(deck.deal());
                cout << "\nYour hand (" << player.getTotal() << "):\n";
                player.show();
            } else {
                break;
            }
        }
        
        // Dealer's turn
        cout << "\nDealer's hand (" << dealer.getTotal() << "):\n";
        dealer.show();
        
        while (dealer.getTotal() < 17) {
            dealer.add(deck.deal());
            cout << "\nDealer hits:\n" << dealer.getLastCard().toString();
            cout << "\nDealer's hand (" << dealer.getTotal() << "):\n";
            dealer.show();
        }
        
        // Determine winner
        int playerTotal = player.getTotal();
        int dealerTotal = dealer.getTotal();
        
        cout << "\nFinal Scores:\n";
        cout << "You: " << playerTotal << "  Dealer: " << dealerTotal << "\n";
        
        if (playerTotal > 21) cout << "You busted. Dealer wins!\n";
        else if (dealerTotal > 21) cout << "Dealer busted. You win!\n";
        else if (playerTotal > dealerTotal) cout << "You win!\n";
        else if (playerTotal < dealerTotal) cout << "Dealer wins!\n";
        else cout << "It's a tie!\n";
    }
};

int main() {
    BlackjackGame game;
    game.play();
    return 0;
}