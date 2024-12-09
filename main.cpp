#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <windows.h>
#include "inventory.h"
#include "Memory game.h"
#include "Mental Maths.h"
#include<mmsystem.h>
using namespace std;

string playerName;
string currentLevel = "Start";
int traversalChoice = 1;

void clearScreen() {
    system("CLS");
}

unordered_map<string, pair<string, int>> loadProgress() {
    unordered_map<string, pair<string, int>> progress;
    ifstream file("player_progress.txt");
    if (!file.is_open()) {
        cout << "Progress file not found. Starting fresh.\n";
        return progress;
    }
    string name, level;
    int traversal;
    while (file >> name >> level >> traversal) {
        progress[name] = make_pair(level, traversal);
    }
    file.close();
    return progress;
}

void saveProgress(const unordered_map<string, pair<string, int>>& progress) {
    ofstream file("player_progress.txt");
    if (file.is_open()) {
        for (const auto& entry : progress) {
            file << " " << entry.first << "       " << entry.second.first << "	       	" << entry.second.second << endl;
        }
        file.close();
    }
}

void trackProgress() {
    auto progress = loadProgress();
    if (progress.find(playerName) != progress.end()) {
        currentLevel = progress[playerName].first;
        traversalChoice = progress[playerName].second;
    } else {
        currentLevel = "Start";
        traversalChoice = 1;
        progress[playerName] = make_pair(currentLevel, traversalChoice);
    }
    saveProgress(progress);
}

void updateLevelProgress(const string& levelLabel) {
    auto progress = loadProgress();
    progress[playerName] = make_pair(levelLabel, traversalChoice);
    saveProgress(progress);
}

void welcomePlayer() {
    system("Color 09");
    cout << R"(
    		*****************************************************
    		*                                                   *
    		*            G A M E   A D V E N T U R E            *
    		*                                                   *
    		*****************************************************
			__        __   _                               
        		\ \      / /__| | ___ ___  _ __ ___   ___  
        		 \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \ 
         		  \ V  V /  __/ | (_| (_) | | | | | |  __/ 
           		   \_/\_/ \___|_|\___\___/|_| |_| |_|\___| 
    )" << endl;

    cout << "\nEnter your name: ";
    cin >> playerName;
    trackProgress();
    clearScreen();
    cout << "\nHello, " << playerName << "! Your adventure begins now!\n";
    cout << R"(
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        *  Get ready to explore, solve puzzles, and have fun!       *
        *  Your journey is full of surprises and excitement.        *
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    )" << endl;
    if (currentLevel != "Start") {
        cout << "\nYou are resuming from **Level " << currentLevel << "** using ";
        cout << (traversalChoice == 1 ? "Level-order traversal" : "Preorder traversal") << ".\n";
    } else {
        cout << "\nStarting a brand-new adventure. Let's get started!\n";
    }
    Sleep(5000);
    clearScreen();
}

class SubNode {
public:
    string label;
    bool (*gameFunction)();
    SubNode* left;
    SubNode* right;

    SubNode(string lbl, bool (*func)()) : label(lbl), gameFunction(func), left(nullptr), right(nullptr) {}
};

bool inventoryCall() {
	PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC | SND_LOOP);
    int choice;
    while (1) {
        clearScreen();
        system("Color 0D");
        cout << "=====================================\n";
        cout << "       INVENTORY MANAGEMENT\n";
        cout << "=====================================\n";
        cout << "1. Press 1 to move to the next level.\n";
        cout << "2. Press 2 to visit the inventory.\n";
        cout << "0. Press 0 to exit the game.\n";
        cout << "=====================================\n";
        cin >> choice;
        switch (choice) {
            case 0:
                cout << "Exiting the Game!...." << endl;
                Sleep(1000);
                return false;
            case 1:
                cout << "Moving to Next Level!....." << endl;
                Sleep(1000);
                clearScreen();
                return true;
            case 2:
                cout << "Opening Inventory!....." << endl;
                Sleep(1000);
                clearScreen();
                inventory(score);
                break;
            default:
                cout << "Invalid Input! Please try again." << endl;
                Sleep(1000);
                clearScreen();
        }
    }
}

// Game Levels
bool memoryGame1E() {
	clearScreen();
    cout << "Level 1: Memory Game - Easy\n";
    memoryplayLevel1(score);
    updateLevelProgress("Level1E");
    cout<<"*LEVEL COMPLETED!*"<<endl;
    sleep(5);
    return inventoryCall();
}
bool memoryGame1M() {
	clearScreen();
    cout << "Level 2: Memory Game - Medium\n";
    memoryplayLevel2(score);
    updateLevelProgress("Level1M");
    cout<<"*LEVEL COMPLETED!*"<<endl;
    sleep(5);
    return inventoryCall();
}
bool memoryGame1H() {
	clearScreen();
    cout << "Level 3: Memory Game - Hard\n";
    memoryplayLevel3(score);
    updateLevelProgress("Level1H");
    cout<<"*LEVEL COMPLETED!*"<<endl;
    sleep(5);
    return inventoryCall();
}
bool mathGame2E() {
	clearScreen();
    cout << "Level 4: Mental Math Game - Easy\n";
    solveCountOfObjects(1, score);
    updateLevelProgress("Level2E");
    cout<<"*LEVEL COMPLETED!*"<<endl;
    sleep(5);
    return inventoryCall();
}
bool mathGame2M() {
	clearScreen();
    cout << "Level 5: Mental Math Game - Medium\n";
    solveSums(2, score);
    updateLevelProgress("Level2M");
    cout<<"*LEVEL COMPLETED!*"<<endl;
    sleep(5);
    return inventoryCall();
}
bool mathGame2H() {
	clearScreen();
    cout << "Level 6: Mental Math Game - Hard\n";
    solveMultiplication(3, score);
    updateLevelProgress("Level2H");
    cout<<"*LEVEL COMPLETED!*"<<endl;
    sleep(5);
    return inventoryCall();
}

bool finallevel(){
	cout<<"GAME COMPLETED!"<<endl;
	sleep(5);
	return true;
}

bool resumeFromPreorder(SubNode* node) {
    if (node == nullptr) return false;
    if (node->label == currentLevel) {
        node->gameFunction();
        return true;
    }
    if (resumeFromPreorder(node->left) || resumeFromPreorder(node->right)) {
        return node->gameFunction();
    }
    return false;
}

bool resumeFromLevelOrder(SubNode* root) {
    if (root == nullptr) return false;
    queue<SubNode*> q;
    q.push(root);
    bool startPlaying = false;
    while (!q.empty()) {
        SubNode* current = q.front();
        q.pop();
        if (current->label == currentLevel) {
            startPlaying = true;
            current->gameFunction();
        } else if (startPlaying) {
            if (!current->gameFunction()) break;
        }
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    return startPlaying;
}

void traverseSubtreeLevelOrder(SubNode* root) {
    if (root == nullptr) return;
    queue<SubNode*> q;
    q.push(root);
    while (!q.empty()) {
        SubNode* current = q.front();
        q.pop();
        if (current->gameFunction != nullptr) {
            if (!current->gameFunction()) break;
        }
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

void traverseSubtreePreorder(SubNode* node) {
    if (node == nullptr) return;
    if (node->gameFunction != nullptr) {
        node->gameFunction();
    }
    traverseSubtreePreorder(node->left);
    traverseSubtreePreorder(node->right);
}

void cleanupTree(SubNode* node) {
    if (node == nullptr) return;
    cleanupTree(node->left);
    cleanupTree(node->right);
    delete node;
}

int main() {
	PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC | SND_LOOP);
    welcomePlayer();

    // Define game levels
    SubNode* tree = new SubNode("Start", nullptr);
    tree->left = new SubNode("Level1E", memoryGame1E);
    tree->right = new SubNode("Level2E", mathGame2E);
    tree->left->left = new SubNode("Level1M", memoryGame1M);
    tree->right->right = new SubNode("Level2M", mathGame2M);
    tree->left->left->left = new SubNode("Level1H", memoryGame1H);
    tree->right->right->right = new SubNode("Level2H", mathGame2H);
    tree->left->left->left->left = new SubNode("FINAL", finallevel);
    if (currentLevel != "Start") {
        if (traversalChoice == 1) {
            resumeFromLevelOrder(tree);
        } else {
            resumeFromPreorder(tree);
        }
    } else {
    	system("Color 0D");
        cout << "=====================================\n";
        cout << "   WELCOME TO THE GAME ADVENTURE!\n";
        cout << "=====================================\n";
        cout << " 1. Level-order traversal (Sequential)\n";
        cout << " 2. Preorder traversal (Explore freely)\n";
        cout << " Enter your choice: ";
        cin >> traversalChoice;
        while (traversalChoice < 1 || traversalChoice > 2) {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin >> traversalChoice;
        }
        updateLevelProgress("Start");
        if (traversalChoice == 1) {
            traverseSubtreeLevelOrder(tree);
        } else {
            traverseSubtreePreorder(tree);
        }
    }
    cleanupTree(tree); // Free memory
    PlaySound(NULL, NULL, 0);
    return 0;
}
