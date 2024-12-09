#include <iostream>
#include<mmsystem.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void solveCountOfObjects(int level,int &score);
void solveSums(int level,int &score);
void solveMultiplication(int level,int &score);
void playSoundEffect(bool isCorrect);

void printObjects(int count) {
    for (int i = 0; i < count; i++) {
        cout << "   @   \n";
        cout << "  @@@  \n"; 
        cout << " @@@@@ \n"; 
        cout << "   |   \n";
        cout << "   |   \n"; 
        cout << endl;
        
    }
}

void playSoundEffect(bool isCorrect) {
    if (isCorrect) {
        cout<<"[Correct Answer! Ding!]"<<endl;
    	PlaySound(TEXT("correctsound.wav"), NULL, SND_SYNC);
    	PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC | SND_LOOP);
    } else {
        cout<<"[Incorrect Answer! Buzzer!]"<<endl;
    	PlaySound(TEXT("wrongsound.wav"), NULL, SND_SYNC);
    	PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC | SND_LOOP);
    }
}

void solveCountOfObjects(int level, int &score) {
	system("Color 71");
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 1; i <= 3; i++) {
        int objectCount = rand() % (5 * level) + 1;
        cout << "Problem " << i << ": How many flowers do you see?"<<endl;
        printObjects(objectCount);
        int answer;
        cout << "Your answer: ";
        cin >> answer;
        if (answer == objectCount) {
            playSoundEffect(true);
            score+=10;
        } else {
            playSoundEffect(false);
            cout << "Incorrect! The correct answer was " << objectCount << ".\n";
        }
    }
    system("CLS");
}

void solveSums(int level,int &score) {
	system("Color B6");
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 1; i <= 3; i++) {
        int num1 = rand() % (5 * level) + 1;
        int num2 = rand() % (5 * level) + 1;
        int correctSum = num1 + num2;
        cout << "Problem " << i << ": What is " << num1 << " + " << num2 << "?\n";
        int answer;
        cout << "Your answer: ";
        cin >> answer;
        if (answer == correctSum) {
            playSoundEffect(true);
            score+=10;
        } else {
            playSoundEffect(false);
            cout << "Incorrect! The correct answer was " << correctSum << ".\n";
        }
    }
    return;
}

void solveMultiplication(int level, int &score) {
	system("Color 04");
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 1; i <= 3; i++) {
        int num1 = rand() % (4 * level) + 1;
        int num2 = rand() % (4 * level) + 1;
        int correctProduct = num1 * num2;
        cout << "Problem " << i << ": What is " << num1 << " * " << num2 << "?\n";
        int answer;
        cout << "Your answer: ";
        cin >> answer;
        if (answer == correctProduct) {
            playSoundEffect(true);
            score+=10;
        } else {
            playSoundEffect(false);
            cout << "Incorrect! The correct answer was " << correctProduct << ".\n";
        }
    }
}