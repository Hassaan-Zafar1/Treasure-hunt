#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;

void showInventory();
bool inventory(int &score);
void updateInventoryProgress();
bool loadInventoryProgress();

struct Toy {
    string name;
    int cost;
};

vector<Toy> userInventory;
int score = 0;

bool inventory(int &score) {
	system("Color 0A");
    loadInventoryProgress();
    vector<Toy> toysForSale = {
        {"Teddy Bear", 30},
        {"Magic Pencils", 15},
        {"Color Pencils", 10},
        {"Action Figure", 50},
        {"Board Game", 70}
    };
    int choice;
    while (true) {
        cout << "=== INVENTORY MENU ===" << endl;
        cout << "Your Points: " << score << endl;
        cout << "1. View Items for Sale" << endl;
        cout << "2. View Your Inventory" << endl;
        cout << "3. Exit Inventory" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "=== ITEMS FOR SALE ===" << endl;
            for (size_t i = 0; i < toysForSale.size(); i++) {
                cout << i + 1 << ". " << toysForSale[i].name << " - " << toysForSale[i].cost << " points" << endl;
            }
            cout << "Choose a toy to purchase (0 to cancel): ";
            int purchaseChoice;
            cin >> purchaseChoice;
            if (purchaseChoice > 0 && purchaseChoice <= toysForSale.size()) {
                if (score >= toysForSale[purchaseChoice - 1].cost) {
                    score -= toysForSale[purchaseChoice - 1].cost;
                    userInventory.push_back(toysForSale[purchaseChoice - 1]);
                    cout << "You purchased: " << toysForSale[purchaseChoice - 1].name << endl;
                    updateInventoryProgress();
                } else {
                    cout << "Not enough points to purchase " << toysForSale[purchaseChoice - 1].name << "!" << endl;
                }
            } else if (purchaseChoice == 0) {
                cout << "Purchase cancelled." << endl;
            } else {
                cout << "Invalid choice." << endl;
            }
            Sleep(2000);
        } else if (choice == 2) {
            showInventory();
            Sleep(2000);
        } else if (choice == 3) {
            cout << "Returning to Main Menu..." << endl;
            Sleep(1000);
            return false;
        } else {
            cout << "Invalid choice. Please select again." << endl;
        }
        system("CLS");
    }
}

void showInventory() {
    if (userInventory.empty()) {
        cout << "Your inventory is empty." << endl;
    } else {
        cout << "=== YOUR INVENTORY ===" << endl;
        for (const Toy& toy : userInventory) {
            cout << "- " << toy.name << endl;
        }
    }
    cout << "Current Score: " << score << endl;
}

void updateInventoryProgress() {
    ofstream file("player_inventory.txt");
    if (file.is_open()) {
        file << score << endl;
        for (const auto& toy : userInventory) {
            file << toy.name << "|" << toy.cost << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file to save inventory progress." << endl;
    }
}
bool loadInventoryProgress() {
    ifstream file("player_inventory.txt");
    if (file.is_open()) {
        string line;
        vector<Toy> savedInventory;
        if (getline(file, line)) {
            stringstream ss(line);
            ss >> score;
        }
        while (getline(file, line)) {
            string toyName;
            int toyCost;
            stringstream ss(line);
            ss >> toyName >> toyCost;
            savedInventory.push_back({toyName, toyCost});
        }
        userInventory = savedInventory;
        file.close();
        return true;
    }
    return false;
}