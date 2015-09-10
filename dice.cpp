/* Author: Sebastian Amara
 * Filename: dice.cpp
 * Description
 * A program that simulates the game know as dice
 * The game has the following rules
 *	1. The winner of the game is the player with the highest number
 *	2. For a players number to qualify for winning, One die must be a
 *		4 and another must be a 1.  These two dice do not contribute to
 *		the final sum.
 *	3. The player may roll the dice as many times as he/she likes; however
 *		the player must take at least one die per roll.  Therefore the max 
 *		number of rolls is 6
 *
 *	Special rule: player can call 'bottoms' such that ever number that was 
 rolled is now the number on the opposite side of the die
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

#define NUMBER_OF_SIDES 6
const string one = " _______\n|       |\n|   o   |\n|       |\n'-------'\n";
const string two = " _______\n|       |\n| o   o |\n|       |\n'-------'\n";
const string three = " _______\n| o     |\n|   o   |\n|     o |\n'-------'\n";
const string four = " _______\n| o   o |\n|       |\n| o   o |\n'-------'\n";
const string five = " _______\n| o   o |\n|   o   |\n| o   o |\n'-------'\n";
const string six = " _______\n| o   o |\n| o   o |\n| o   o |\n'-------'\n";


int roll() {
    return rand() % NUMBER_OF_SIDES + 1;
}
void rollForTurn(int outputArray[6], int numOfDie) {
    for (int i = 0; i<numOfDie; i++) {
        outputArray[roll()-1]++;
    }
}
bool isPlayersSetValid(int rolls[6]) {
    if (rolls[0] != 0 && rolls[3] != 0) {
        --rolls[0];
        --rolls[3];
        return true;
    }
    return false;
}
int getPlayerSum(int rolls[6]){
    int sum = 0;
    for (int i = 0; i<6; i++)
        sum += rolls[i]*(i+1);
    return sum;
}
void showRolls(int rolls[]) {
    string toPrint = "";
    for (int i = 0; i<6; i++) {
        for (int j = rolls[i]; j>0; j--) {
            switch (i+1) {
                case 1: 
                    toPrint += one; 
                    break;
                case 2: 
                    toPrint += two; 
                    break;
                case 3: 
                    toPrint += three; 
                    break;
                case 4: 
                    toPrint += four; 
                    break;
                case 5: 
                    toPrint += five; 
                    break;
                case 6: 
                    toPrint += six; 
                    break;
            }
        }
    }
    cout << toPrint << endl;

}

int handlePlayerResponse() {
    string input;
    cin >> input;
    int inputNum;
    try {
        inputNum = atoi(input.c_str());
    }
    catch (int e) {
        for (int i = 0; i<input.length(); i++)
            input[i] = tolower(input[i]);
        if (input.compare("roll") == 0)
            return 0;
        else 
            return -1;
    }
    return inputNum;
}

int playerTurn() {
    int diceToRoll = 6, currentRoll[6], savedRolls[6];
    for (int i = 0; i<6; i++) 
        savedRolls[i] = 0;
    for (int diceToRoll = 6; diceToRoll>0;) {
        for (int i = 0; i<6; i++) 
            currentRoll[i] = 0;
        rollForTurn(currentRoll, diceToRoll);
        cout << "Your new roll is" << endl;
        showRolls(currentRoll);
        cout << "Your saved roll is" << endl;
        showRolls(savedRolls);
        cout << "Which die or dice would you like to take?" << endl;
        cout << "(REMINDER: you must take at least one)" << endl;
        int toTake, taken = 0;
        while(1) {
            toTake = handlePlayerResponse();
            if (toTake == 0 && taken != 0) {
                break;
            }
            else if (toTake != 0 && currentRoll[toTake-1] != 0 &&
                    toTake <= NUMBER_OF_SIDES) {
                currentRoll[toTake-1]--;
                taken++;
                --diceToRoll;
                savedRolls[toTake-1]++;
                if (diceToRoll == 0)
                    break;
                cout << "Would you like to choose another?";
                cout << " (enter 0 for your next roll)" << endl;
            }
            else 
                cout << "Invalid number to take, please pick again" << endl;
        }
    }
    cout << "Your final set of dice are" << endl;
    showRolls(savedRolls);
    cout << "Your final score is ";
    int score = (isPlayersSetValid(savedRolls) ? getPlayerSum(savedRolls) : 0);
    cout << score << endl << endl;;

    return score;
}

void playWithMultiplePeople() {
    int players;
    cout << "How many players?" << endl;
    while (1) {
        players = handlePlayerResponse();
        if (players == 1) {
            playerTurn();
            return;
        }
        else if (players < 1) {
            cout << "Invalid number" << endl;
            continue;
        }
        else 
            break;
    }
    int playerID[players];
    for (int i = 0; i<players; i++)
        playerID[i] = i+1;
playagain:
    int scores[players];
    for (int i = 0; i<players; i++) {
        cout << "\nIt is now Player " << playerID[i] << "'s turn" << endl;
        scores[i] = playerTurn();
    }

//    for (int i = 0; i<players-1; i+=2)
//        scores[i] = 24;

    int max = -1, ties = 0;
    int maxIndex[players];
    for (int i = 0; i<players; i++) 
        maxIndex[i] = 0;
    for (int i = 0; i<players; i++) {
        if (scores[i] > max) {
            max = scores[i];
            maxIndex[0] = i;
            ties = 0;
        }
        else if (scores[i] == max) {
            ties++;
            maxIndex[ties] = i;
        }
    }
    if (ties == 0) 
        cout << "The winner is Player " << playerID[maxIndex[0]] << " with a score of " << max << endl;
    else {
        cout << "There is a draw between players ";
        for (int i = 0; i<=ties; i++) {
            cout << " " << maxIndex[i]+1;
            playerID[i] = maxIndex[i]+1;
            if (i + 1 <= ties)
                cout << " and";
        }
        cout << endl << "Another round will be played with those who tied" << endl;
        players = ties+1;
        goto playagain;
    }
}

void test1() {
    for (int i=0; i<10; i++) {
        int rolls[6];
        for (int j = 0; j<6; j++)
            rolls[j] = 0;
        for (int j = 0; j<6; j++)
            rolls[roll()-1]++;

        if (isPlayersSetValid(rolls))
            cout << getPlayerSum(rolls) << endl;
        else
            cout << "Roll was invaid" << endl;
        //for (int j = 0; j<6; j++)
        //	cout << rolls[j] << " ";
        showRolls(rolls);
        cout << "\n\n";
    }
}

void rolling() {
    while (1) {
        string toPrint = "";
        int i = roll();
        switch (i) {
            case 1: 
                toPrint += one; 
                break;
            case 2: 
                toPrint += two; 
                break;
            case 3: 
                toPrint += three; 
                break;
            case 4: 
                toPrint += four; 
                break;
            case 5: 
                toPrint += five; 
                break;
            case 6: 
                toPrint += six; 
                break;
        }
        cout << toPrint;
    }
}

int main() {
    srand(time(NULL));

    //test1();
    //playerTurn();
    //rolling();
    playWithMultiplePeople();

}
