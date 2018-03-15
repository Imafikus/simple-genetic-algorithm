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

///compares 2 chormosomes and returns one with the greater fitness score
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
        val = better_fit(p.at(k1), p.at(k2), fitness);
        select_chrom.push_back(val);
    }

}
vector<int> swap_bits(vector<int> v1, vector<int> v2, int pivot)
{
    for(int i = 0; i < pivot; i++)
        swap(v1.at(i), v2.at(i) );
    return v1;
}
void crossover(vector<vector<int> >select_chrom, vector<vector<int> > &cross_chrom)///should be vector<vector<int> > type instead of void
{
    ///add chromosomes from tournament selection to crossover chromosomes
    for(int i = 0; i < select_chrom.size(); i++)
        cross_chrom.push_back(select_chrom.at(i) );


    ///generate random pivot point for crossover
    int pivot = rand() % 8;
    pivot = abs(pivot - rand() % 8);


    ///crossover 1/4 of the whole population and add to crossover population
    for(int i = 0; i < POPULATION_NUMBER/4; i++)
    {
        /// pick first random index
        int k1 = rand() % select_chrom.size();

        /// pick second random index
        int k2 = rand() % select_chrom.size();

        ///pick one crossovered chromosome
        vector<int> val = swap_bits(select_chrom.at(k1), select_chrom.at(k2), pivot);
        cross_chrom.push_back(val);
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

    /// tournament selection
    vector<vector<int> >select_chrom;
    selection(population, fitness, select_chrom);


    cout << "Selection" << endl;
    for(int i = 0; i < select_chrom.size(); i++)
        print_vector(select_chrom.at(i) );
    cout << endl;

    ///crossover
    vector<vector<int> >cross_chrom;
    crossover(select_chrom, cross_chrom);

    cout << "Crossover" << endl;
    for(int i = 0; i < cross_chrom.size(); i++)
            print_vector(cross_chrom.at(i) );
    cout << endl;

}
