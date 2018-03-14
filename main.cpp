#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>

const double MAX_VAL = 65536;
const int VECTOR_SIZE = 16;///size of the binary number, 8 points above and 8 below .
const int POPULATION_NUMBER = 4;

using namespace std;

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

int main()
{
    srand(time(NULL)); /// generate random seed before any for loop
    vector<vector<int> > population(POPULATION_NUMBER);
    population_init(population);
    print_population(population);



    /*
    vector<int> v;
    vector_init(v);
    print_vector(v);
    double n = binary_to_dec(v);
    cout << n << endl;
    */

}
