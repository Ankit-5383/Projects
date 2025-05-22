#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Card {
    string name;
    char suit;
    int value;
};

vector<string> names = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
vector<int> values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
vector<char> suits = {'H', 'D', 'S', 'C'};

Card generateCard(int currentSum) {
    int idx = rand() % 13;
    int val = values[idx];

    // Adjust Ace value based on current sum
    if (val == 11 && currentSum + 11 > 21) val = 1;

    Card card = {names[idx], suits[rand() % 4], val};
    return card;
}

void printHand(const vector<Card>& hand, int sum, const string& who) {
    cout << who << "'s cards: ";
    for (auto& c : hand) cout << c.name << c.suit << " ";
    cout << "| Sum: " << sum << "\n";
}

int main() {
    srand(time(0));

    vector<Card> player, dealer;
    int Psum = 0, Dsum = 0;
    char choice;

    // Initial two cards for player
    for (int i = 0; i < 2; ++i) {
        Card c = generateCard(Psum);
        Psum += c.value;
        player.push_back(c);
    }

    // Player's turn
    while (true) {
        printHand(player, Psum, "Player");
        if (Psum >= 21) break;
        cout << "Draw another card? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') break;

        Card c = generateCard(Psum);
        Psum += c.value;
        player.push_back(c);
    }

    if (Psum > 21) {
        printHand(player, Psum, "Player");
        cout << "You busted! Dealer wins.\n";
        return 0;
    }

    // Dealer's turn (auto-draws until 17 or higher)
    while (Dsum < 17) {
        Card c = generateCard(Dsum);
        Dsum += c.value;
        dealer.push_back(c);
    }

    printHand(dealer, Dsum, "Dealer");

    if (Dsum > 21) {
        cout << "Dealer busted! You win.\n";
        return 0;
    }

    // Final comparison
    cout << "\n=== Final Result ===\n";
    printHand(player, Psum, "Player");
    printHand(dealer, Dsum, "Dealer");

    if (Psum > Dsum) cout << "Result: Player wins!\n";
    else if (Dsum > Psum) cout << "Result: Dealer wins!\n";
    else cout << "Result: It's a draw!\n";

    return 0;
}
