#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>

const double MAX_VAL = 65536;
const double E = 0.001;
const int VECTOR_SIZE = 4;///size of the binary number, 8 points above and 8 below .
const int POPULATION_NUMBER = 8; ///MUST BE EVEN

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
void selection(vector<vector<int> > p, double fitness, vector<vector<int> > &select_chrom)///FIXME
{
    vector<int> val;
    /// "tournament strategy" selection
    for(int i = 0; i < POPULATION_NUMBER/2; i++)
    {
        /// pick first random index
        int k1 = rand() % POPULATION_NUMBER;

        /// pick second random index
        int k2 = rand() % POPULATION_NUMBER;

        /// return better
        if(k1 != k2) val = better_fit(p.at(k1), p.at(k2), fitness);
        select_chrom.push_back(val);
    }
}
void crossover()///should be vector<vector<int> > type instead of void
{
    vector<int> v1 = {1, 0, 0, 1, 0, 1, 0};
    vector<int> v2 = {0, 1, 1, 0, 1, 0, 1};

    int pivot = rand() % 8;
    pivot = abs(pivot - rand() % 8);


    cout << "pivot " << pivot << endl;

    for(int i = 0; i < pivot; i++)
        swap(v1.at(i), v2.at(i));


    cout << "1st vector swaped " << endl;
    for(int i = 0; i < v1.size(); i++)
        cout << v1.at(i) << " ";
    cout << endl;

    cout << "2nd vector swaped " << endl;
    for(int i = 0; i < v2.size(); i++)
        cout << v2.at(i) << " ";
    cout << endl;





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

    /// tournament selection
    vector<vector<int> >select_chrom;
    selection(population, fitness, select_chrom);
    cout << "Prosao selection" << endl;


    for(int i = 0; i < select_chrom.size(); i++)
        print_vector(select_chrom.at(i) );

    crossover();

}
