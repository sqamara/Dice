/* Author: Sebastian Amara
 * Filename: roll_analyzer.cpp
 * Description: A program that determines the probability of getting
 *				particular rolls/values and pursue the best value with 
 * 				a specified risk percentage.
 */

 /* TODO: 
  * FIRST, develop decision tree for getting two dice to the highest value 
  * 	with pursue percent decisions
  * SECOND, make automated decision tree for all six die to get max with
  *		pursue percent decision
  * THIRD, Incoperate qulification value
 */

#include <iostream>
#define PURSUE_PERCENT .50

using namespace std;
#define NUMBER_OF_SIDES 6

int roll() {
	return rand() % NUMBER_OF_SIDES + 1;
}

struct bestChoice {
	double probability;
	int number_to_pursue;
};

bestChoice * analyze_one() {
	double one_die[] = {1/6., 1/6., 1/6., 1/6., 1/6., 1/6.};
	bestChoice * toReturn = new bestChoice();
	toReturn->probability = 0;
	toReturn->number_to_pursue = 0;

	for (int i = 6; i>0; i--) {
		if (one_die[i-1] > PURSUE_PERCENT) {
			toReturn->probability = one_die[i-1];
			toReturn->number_to_pursue = i;
			cout << "found highest number with probablity above PURSUE_PERCENT" << endl;
			return toReturn;
		}
		else if (one_die[i-1] > toReturn->probability){
			toReturn->probability = one_die[i-1];
			toReturn->number_to_pursue = i;
		}
	}
	cout << "found best number associated with the highest likely hood" << endl;
	return toReturn;
}

void print_two_probabilities() {
	int toPrint[12];
	for (int i = 0; i<12; i++)
		toPrint[i] = 0;
	for (int i = 0; i<6; i++) {
		for (int j = 0; j<6; j++) {
			toPrint[(i+1)+(j+1)-1]++;
		}
	}
	float total = 0;
	for (int i = 0; i<12; i++)
		total += toPrint[i];
	for (int i = 0; i<12; i++) 
		cout << i+1 << ": " << toPrint[i] / total << endl;
	cout << endl;
}

void tabled_two_die() {
	int die1_by_die2_by_rerollmin[6][6][6];
	// prob of any individual element in array is 1/6^3
	// values between 2 and 12 inclusive
	for (int die1 = 0; die1 < 6; die1++) {
		for (int die2 = 0; die2 < 6; die2++) {
			for (int rerollmin = 0; rerollmin < 6; rerollmin++) {
				die1_by_die2_by_rerollmin[die1][die2][rerollmin] = max((die1+1), (die2+1)) + (rerollmin+1);
			}
		}
	}

	for (int rerollmin = 0; rerollmin < 6; rerollmin++) {
		for (int die1 = 0; die1 < 6; die1++) {
			for (int die2 = 0; die2 < 6; die2++) {
				printf("%2d ",die1_by_die2_by_rerollmin[die1][die2][rerollmin]);
			}
			cout << endl;
		}
		cout << endl;
	}

	int count[12];
	for (int i = 0; i<12; i++)
		count[i] = 0;
	for (int die1 = 0; die1 < 6; die1++) {
		for (int die2 = 0; die2 < 6; die2++) {
			for (int rerollmin = 0; rerollmin < 6; rerollmin++)
				count[ die1_by_die2_by_rerollmin[die1][die2][rerollmin]-1]++;
		}
	}

	for (int i = 0; i<12; i++)
		printf("%lf\n", double(count[i])/(6*6*6));
		//printf("%d: %d: %lf\n", i+1, count[i], double(count[i])/(6*6*6));



	//simulate
	int simulate[12];
	int simulate_with_reroll[12];

	for (int i = 0; i<12; i++) {
		simulate[i] = 0;
		simulate_with_reroll[i] = 0;
	}
	int cases = 100;
	for (int i = 0; i<cases; i++) {
		int roll1 = roll();
		int roll2 = roll();
		simulate[roll1+roll2-1]++;
		simulate_with_reroll[max(roll1, roll2) + roll()-1]++;
	}
	for (int i = 0; i<12; i++)
		printf("%lf,\n", double(simulate[i])/cases);

}


int main() {
	srand(time(NULL));

	//cout << analyze_one()->number_to_pursue << endl;
	tabled_two_die();

	print_two_probabilities();

 }