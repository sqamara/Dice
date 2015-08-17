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
int one_die_values[NUMBER_OF_SIDES];
int two_die_values[NUMBER_OF_SIDES*2];
int three_die_values[NUMBER_OF_SIDES*3];
int four_die_values[NUMBER_OF_SIDES*4];
int five_die_values[NUMBER_OF_SIDES*5];
int six_die_values[NUMBER_OF_SIDES*6];

int roll() {
    return rand() % NUMBER_OF_SIDES + 1;
}
void set_one_die_values() {
    for (int i = 0; i<NUMBER_OF_SIDES; i++)
        one_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES; i++)
        one_die_values[i]++;
}
void set_two_die_values() {
    for (int i = 0; i<NUMBER_OF_SIDES*2; i++)
        two_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES; i++) {
        for (int j = 0; j<NUMBER_OF_SIDES; j++)
            two_die_values[i+j+1]++;
    }
}
void set_three_die_values() {
    for (int i = 0; i<NUMBER_OF_SIDES*3; i++)
        three_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES; i++) {
        for (int j = 0; j<NUMBER_OF_SIDES; j++) {
            for (int k = 0; k<NUMBER_OF_SIDES; k++)
                three_die_values[i+j+k+2]++;
        }
    }
}
void generate_value_tables(){
    set_one_die_values();
    set_two_die_values();
    set_three_die_values();
}
void print_value_tables(){
    for (int i = 0; i<NUMBER_OF_SIDES; i++)
        cout << i+1 << ": " << one_die_values[i] << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*2; i++)
        cout << i+1 << ": " << two_die_values[i] << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*3; i++)
        cout << i+1 << ": " << three_die_values[i] << endl;
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

double probability_of_better_one(int r) {
    double one_die[] = {1/6., 1/6., 1/6., 1/6., 1/6., 1/6.};
    double sum = 0;
    for (--r;r<6; r++) {
        sum += one_die[r];
    }
    return sum;
}
void print_two_die_varing_PP() {
    int die1_by_die2_by_rerollmin[6][6][6];
    int count[12];
    for (double pp = .48; pp <= .52; pp+=.01) {
        //for each PP
        // prob of any individual element in array is 1/6^3
        // values between 2 and 12 inclusive
        for (int die1 = 0; die1 < 6; die1++) {
            for (int die2 = 0; die2 < 6; die2++) {
                for (int rerollmin = 0; rerollmin < 6; rerollmin++) {
                    if (pp <= probability_of_better_one(min((die1+1), (die2+1))))
                        die1_by_die2_by_rerollmin[die1][die2][rerollmin] = max((die1+1), (die2+1)) + (rerollmin+1);
                    else 
                        die1_by_die2_by_rerollmin[die1][die2][rerollmin] = (die1+1) + (die2+1);
                }
            }
        }

        for (int i = 0; i<12; i++)
            count[i] = 0;
        for (int die1 = 0; die1 < 6; die1++) {
            for (int die2 = 0; die2 < 6; die2++) {
                for (int rerollmin = 0; rerollmin < 6; rerollmin++)
                    count[ die1_by_die2_by_rerollmin[die1][die2][rerollmin]-1]++;
            }
        }
        /*
           for (int rerollmin = 0; rerollmin < 6; rerollmin++) {
           for (int die1 = 0; die1 < 6; die1++) {
           for (int die2 = 0; die2 < 6; die2++) {
           printf("%2d ",die1_by_die2_by_rerollmin[die1][die2][rerollmin]);
           }
           cout << endl;
           }
           cout << endl;
           }*/


        cout << "pp_equals_" << (int) (pp * 100 + .01) << " = [" << endl;
        for (int i = 0; i<12; i++)
            printf("%lf,\n", double(count[i])/(6*6*6));
        cout << "]" << endl << endl;
    }


    for (int i = 1; i<=6; i++) {
        cout << i << " " << probability_of_better_one(i) << endl;
    }
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
    //tabled_two_die();

    //print_two_probabilities();
    //print_two_die_varing_PP();
    generate_value_tables();
    print_value_tables();
}
