#include <iostream>
#include <vector>
#include <algorithm>
#include<mmsystem.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

void displayColors(vector<string>& colors);
void displayAlphabets(vector<char>& alphabets);
void displayNumbers(vector<int>& numbers);
void memoryplayLevel1(int &score);
void memoryplayLevel2(int &score);
void memoryplayLevel3(int &score);
void showBlocks(int delay);
void playSound(bool isCorrect);

void showBlocks(int delay) {
    sleep(delay);
}

void playSound(bool isCorrect) {
    if (isCorrect) {
        cout << "*Ding* (Correct Sound)\n";
        PlaySound(TEXT("correctsound.wav"), NULL, SND_SYNC);
        PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC | SND_LOOP);
    } else{
        cout << "*Buzz* (Incorrect Sound)\n";
    	PlaySound(TEXT("wrongsound.wav"), NULL, SND_SYNC);
    	PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC | SND_LOOP);
    }
}

void displayColors(vector<string>& colors) {
    for (const auto& color : colors) {
        cout << "[" << color << "] ";
    }
    cout << endl;
}

void displayAlphabets(vector<char>& alphabets) {
    for (const auto& letter : alphabets) {
        cout << "[" << letter << "] ";
    }
    cout << endl;
}

void displayNumbers(vector<int>& numbers) {
    for (const auto& number : numbers) {
        cout << "[" << number << "] ";
    }
    cout << endl;
}

void memoryplayLevel1(int &score) {
	system("Color 71");
    cout << "\n--- Level 1: Color Blocks ---\n";
    vector<string> colorOptions = {"Red", "Blue", "Green", "Yellow", "Purple"};
    srand(time(0));
    for (int round = 1; round <= 3; round++) {
        vector<string> originalColors;
        for (int i = 0; i < 5; i++) {
            originalColors.push_back(colorOptions[rand() % colorOptions.size()]);
        }
        cout << "Remember the order of the colors:\n";
        displayColors(originalColors);
        showBlocks(3);
		cout << "\033[2J\033[1;1H";
        vector<string> shuffledColors = originalColors;
        random_shuffle(shuffledColors.begin(), shuffledColors.end());
        cout << "Rearrange the colors in the original order you saw: \n";
        displayColors(shuffledColors);
        vector<string> playerAnswer(5);
        for (int i = 0; i < 5; i++) {
            cout << "Enter color " << i + 1 << ": ";
            cin >> playerAnswer[i];
        }
        if (playerAnswer == originalColors) {
            cout << "Correct!\n";
            score+=10;
            playSound(true);
        } else {
            cout << "Incorrect! The correct order was: ";
            displayColors(originalColors);
            playSound(false);
        }
    }
}

void memoryplayLevel2(int &score) {
	system("Color B6");
    cout << "\n--- Level 2: Alphabet Blocks ---\n";
    vector<char> alphabetOptions = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    srand(time(0));
    for (int round = 1; round <= 3; round++) {
        vector<char> originalAlphabets;
        for (int i = 0; i < 5; i++) {
            originalAlphabets.push_back(alphabetOptions[rand() % alphabetOptions.size()]);
        }
        cout << "Remember the order of the alphabets:\n";
        displayAlphabets(originalAlphabets);
        showBlocks(3);
		cout << "\033[2J\033[1;1H";
        vector<char> shuffledAlphabets = originalAlphabets;
        random_shuffle(shuffledAlphabets.begin(), shuffledAlphabets.end());
        cout << "Rearrange the alphabets in the original order you saw: \n";
        displayAlphabets(shuffledAlphabets);
        vector<char> playerAnswer(5);
        for (int i = 0; i < 5; i++) {
            cout << "Enter alphabet " << i + 1 << ": ";
            cin >> playerAnswer[i];
        }
        if (playerAnswer == originalAlphabets) {
            cout << "Correct!\n";
            score+=10;
            playSound("correct");
        } else {
            cout << "Incorrect! The correct order was: ";
            displayAlphabets(originalAlphabets);
            playSound("incorrect");
        }
    }
}

void memoryplayLevel3(int &score) {
	system("Color 04");
    cout << "\n--- Level 3: Number Blocks ---\n";
    srand(time(0));
    for (int round = 1; round <= 3; round++) {
        vector<int> originalNumbers;
        for (int i = 0; i < 5; i++) {
            originalNumbers.push_back(rand() % 10);
        }
        cout << "Remember the order of the numbers:\n";
        displayNumbers(originalNumbers);
        showBlocks(3);
        cout << "\033[2J\033[1;1H";
        vector<int> shuffledNumbers = originalNumbers;
        random_shuffle(shuffledNumbers.begin(), shuffledNumbers.end());
        cout << "Rearrange the numbers in the original order you saw: \n";
        displayNumbers(shuffledNumbers);
        vector<int> playerAnswer(5);
        for (int i = 0; i < 5; i++) {
            cout << "Enter number " << i + 1 << ": ";
            cin >> playerAnswer[i];
        }
        if (playerAnswer == originalNumbers) {
            cout << "Correct!\n";
            score+=10;
            playSound("correct");
        } else {
            cout << "Incorrect! The correct order was: ";
            displayNumbers(originalNumbers);
            playSound("incorrect");
        }
    }
}
