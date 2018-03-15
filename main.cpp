#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>

const double MAX_VAL = 65536;
const double E = 0.001;
const int VECTOR_SIZE = 16;///size of the binary number, 8 points above and 8 below .
const int POPULATION_NUMBER = 8; ///MUST BE EVEN

using namespace std;

///dec for decimal value, and index, so you can find binary number in population vector
typedef struct
{
    double dec;
    int index;
}pop;
///NOTE, this always converts upper half to the whole numbers, and lower half to values < 1
double binary_to_dec(vector<int> &v)
{
    double dec_number = 0;
    int lower_limit= -v.size()/2;
    int upper_limit = v.size()/2-1;

    int pos = 0;
    for(int i = upper_limit; i >= lower_limit; i--)
        {
            if(v.at(pos) == 1)
            {
                dec_number += pow(2, i);
            }
            pos++;
        }
    return dec_number;
}

///print, init for the one chromosome
void vector_init(vector<int> &v)
{
    int val;


    for(int i = 0; i < VECTOR_SIZE; i++)
        {
            val = rand() % 2;
            v.push_back(val);
        }
}
void print_vector(vector<int> v)
{
    for(int i = 0; i < VECTOR_SIZE; i++)
    {
        cout << v.at(i) << " ";
        if(i == VECTOR_SIZE/2-1) cout <<". ";
    }
    cout << endl;

}

///print, init for the whole population
void population_init(vector<vector<int> > &p)
{
    for(int i = 0; i < POPULATION_NUMBER; i++)
        vector_init(p.at(i) );
}

void print_population(vector<vector<int> > p)
{
    for(int i = 0; i < POPULATION_NUMBER; i++)
        print_vector(p.at(i) );
}

///compares 2 chormosomes and returnes one with the greater fitness score
vector<int> better_fit(vector<int> p1, vector<int> p2, double fitness)
{
    double dec_p1 = binary_to_dec(p1);
    double dec_p2 = binary_to_dec(p2);

    double e1 = abs(dec_p1 - fitness);
    double e2 = abs(dec_p2 - fitness);

    if(e1 >= e2) return p1;
    else return p2;
}
void selection(vector<vector<int> > p, double fitness, vector<vector<int> > &next_gen)///FIXME
{
    vector<int> val;
    /// "tournament strategy" seletion
    for(int i = 0; i < POPULATION_NUMBER/2; i++)
    {
        /// pick first random index
        int k1 = rand() % POPULATION_NUMBER;

        /// pick second random index
        int k2 = rand() % POPULATION_NUMBER;

        /// return better
        if(k1 != k2) val = better_fit(p.at(k1), p.at(k2), fitness );
        next_gen.push_back(val);
    }
}

int main()
{


    double number;
    cout << "Pick a number 0 < x <= " << MAX_VAL << endl;
    //cin >> number;
    //check(number);

    ///fitness function, in this case sqrt of the given number
    double fitness = 30;// sqrt(number);


    /// generate random seed before any for loop
    srand(time(NULL));

    /// generate random population
    vector<vector<int> > population(POPULATION_NUMBER);
    population_init(population);
    print_population(population);
    cout << endl;

    vector<vector<int> >next_gen;
    selection(population, fitness, next_gen);


    for(int i = 0; i < next_gen.size(); i++)
        print_vector(next_gen.at(i) );





    /*
    vector<int> v;
    vector_init(v);
    print_vector(v);
    double n = binary_to_dec(v);
    cout << n << endl;
    */

}
