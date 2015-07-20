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

int main() {
	//cout << analyze_one()->number_to_pursue << endl;
	print_two_probabilities();
 }