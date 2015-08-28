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
#include <cmath>
#include <algorithm>
#include <cstring>
#define PURSUE_PERCENT .50

using namespace std;

#define NUMBER_OF_SIDES 6
double one_die_prob[NUMBER_OF_SIDES];
double two_die_prob[NUMBER_OF_SIDES*2];
double three_die_prob[NUMBER_OF_SIDES*3];
double four_die_prob[NUMBER_OF_SIDES*4];
double five_die_prob[NUMBER_OF_SIDES*5];
double six_die_prob[NUMBER_OF_SIDES*6];

int roll() {
    return rand() % NUMBER_OF_SIDES + 1;
}
void set_table_values() {
    int one_die_values[NUMBER_OF_SIDES];
    int two_die_values[NUMBER_OF_SIDES*2];
    int three_die_values[NUMBER_OF_SIDES*3];
    int four_die_values[NUMBER_OF_SIDES*4];
    int five_die_values[NUMBER_OF_SIDES*5];
    int six_die_values[NUMBER_OF_SIDES*6];

    for (int i = 0; i<NUMBER_OF_SIDES; i++)
        one_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES; i++)
        one_die_values[i]++;
    for (int i = 0; i<NUMBER_OF_SIDES; i++)
        one_die_prob[i] = (double)one_die_values[i]/pow((double) 6,1);

    for (int i = 0; i<NUMBER_OF_SIDES*2; i++)
        two_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES; i++) {
        for (int j = 0; j<NUMBER_OF_SIDES; j++) {
            for (int k = one_die_values[i]; k > 0; k--)
                two_die_values[i+j+1]++;
        }
    }
    for (int i = 0; i<NUMBER_OF_SIDES*2; i++)
        two_die_prob[i] = (double)two_die_values[i]/pow((double) 6,2);

    for (int i = 0; i<NUMBER_OF_SIDES*3; i++)
        three_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES*2; i++) {
        for (int j = 0; j<NUMBER_OF_SIDES; j++) {
            for (int k = two_die_values[i]; k > 0; k--)
                three_die_values[i+j+1]++;
        }
    }
    for (int i = 0; i<NUMBER_OF_SIDES*3; i++)
        three_die_prob[i] = (double)three_die_values[i]/pow((double) 6,3);

    for (int i = 0; i<NUMBER_OF_SIDES*4; i++)
        four_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES*3; i++) {
        for (int j = 0; j<NUMBER_OF_SIDES; j++) {
            for (int k = three_die_values[i]; k > 0; k--)
                four_die_values[i+j+1]++;
        }
    }
    for (int i = 0; i<NUMBER_OF_SIDES*4; i++)
        four_die_prob[i] = (double)four_die_values[i]/pow((double) 6,4);

    for (int i = 0; i<NUMBER_OF_SIDES*5; i++)
        five_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES*4; i++) {
        for (int j = 0; j<NUMBER_OF_SIDES; j++) {
            for (int k = four_die_values[i]; k > 0; k--)
                five_die_values[i+j+1]++;
        }
    }
    for (int i = 0; i<NUMBER_OF_SIDES*5; i++)
        five_die_prob[i] = (double)five_die_values[i]/pow((double) 6,5);


    for (int i = 0; i<NUMBER_OF_SIDES*6; i++)
        six_die_values[i] = 0;
    for (int i = 0; i<NUMBER_OF_SIDES*5; i++) {
        for (int j = 0; j<NUMBER_OF_SIDES; j++) {
            for (int k = five_die_values[i]; k > 0; k--)
                six_die_values[i+j+1]++;
        }
    }
    for (int i = 0; i<NUMBER_OF_SIDES*6; i++)
        six_die_prob[i] = (double)six_die_values[i]/pow((double) 6,6);

}
void print_value_tables(){
    for (int i = 0; i<NUMBER_OF_SIDES; i++)
        cout << i+1 << ": " << one_die_prob[i] << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*2; i++)
        cout << i+1 << ": " << two_die_prob[i] << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*3; i++)
        cout << i+1 << ": " << three_die_prob[i] << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*4; i++)
        cout << i+1 << ": " << four_die_prob[i] << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*5; i++)
        cout << i+1 << ": " << five_die_prob[i] << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*6; i++) {
        cout << i+1 << ": " << six_die_prob[i] << endl;
    }
}
void print_six_value_lists() {
    cout << "no_reroll_6 = [" << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*6; i++) {
        cout << six_die_prob[i] << "," << endl;
    }
    cout << "]" << endl;
    cout << "no_reroll_5 = [" << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*5; i++) {
        cout << five_die_prob[i] << "," << endl;
    }
    cout << "]" << endl;
    cout << "no_reroll_4 = [" << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*4; i++) {
        cout << four_die_prob[i] << "," << endl;
    }
    cout << "]" << endl;
    cout << "no_reroll_3 = [" << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*3; i++) {
        cout << three_die_prob[i] << "," << endl;
    }
    cout << "]" << endl;
    cout << "no_reroll_2 = [" << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*2; i++) {
        cout << two_die_prob[i] << "," << endl;
    }
    cout << "]" << endl;
    cout << "no_reroll_1 = [" << endl;
    for (int i = 0; i<NUMBER_OF_SIDES*1; i++) {
        cout << one_die_prob[i] << "," << endl;
    }
    cout << "]" << endl;
}
int sum_array(int * start, int size) {
    int sum = 0;
    for (int i = 0; i<size; i++)
        sum += start[i];
    return sum;
}
int get_max(int * start, int size) {
    int max = 0;
    for (int i = 0; i<size; i++) {
        if (start[i] > max)
            max = start[i];
    }
    return max; 
}
void set_rolls(int * start, int size) {
    for (int i = 0; i<size; i++)
        start[i] = roll();
}
void simulate_with_rerolls_6() {
    int one_roll[36] = {0};
    int every_reroll[36] = {0};
    double cases = 1e9;
    for (int i = 0; i<cases; i++) {
        int rolls[6];
        set_rolls(rolls, 6);
        one_roll[sum_array(rolls, 6) - 1]++;
        //reroll and take max
        for (int j = 0; j<6; j++) {
            rolls[j] = get_max(rolls+j, 6-j);
            set_rolls(rolls+j+1, 5-j);
        }
        every_reroll[sum_array(rolls, 6) - 1]++;
    }
    cout << "#these are simulated probabilities based on " << cases;
    cout << " test cases" << endl;
    cout << "one_roll_6 = [" << endl;
    for (int i = 0; i<36; i++) {
        cout << double(one_roll[i])/cases << "," << endl;
    }
    cout << "]" << endl;

    cout << "every_reroll_6 = [" << endl;
    for (int i = 0; i<36; i++) {
        cout << double(every_reroll[i])/cases << "," << endl;
    }
    cout << "]" << endl;

}



bool wayToSort(int i, int j) { return i > j; }
void analyze_roll(int rolls[], int size){
    sort(rolls, rolls+size, wayToSort);
    for (int i = 0; i<size; i++)
        cout << rolls[i] << endl;
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
    //set_table_values();

    //cout << analyze_one()->number_to_pursue << endl;
    //tabled_two_die();

    //print_two_probabilities();
    //print_two_die_varing_PP();
    //print_value_tables();
    //print_six_value_lists();
    simulate_with_rerolls_6();
}
