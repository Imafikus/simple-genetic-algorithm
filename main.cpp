#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>

const double MAX_VAL = 1 << 16;
const double Epsilon = 0.000000001;
const int VECTOR_SIZE = 32;///size of the binary number, 8 points above and 8 below .
const int POPULATION_NUMBER = 16; ///MUST BE EVEN

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

    if(e1 <= e2) return p1;
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
vector<int> mutate_bits(vector<int> v1)
{
    ///pick random gene from chromosome and mutate it
    int k = rand() % v1.size();

    if (v1.at(k) == 0) v1.at(k) = 1;
    else v1.at(k) = 0;

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
void mutation(vector<vector<int> >cross_chrom, vector<vector<int> > &muta_chrom)///should be vector<vector<int> > type instead of void
{
    ///add chromosomes from tournament selection to crossover chromosomes
    for(int i = 0; i < cross_chrom.size(); i++)
        muta_chrom.push_back(cross_chrom.at(i) );


    ///mutate 1/4 of the whole population and add to muta population
    for(int i = 0; i < POPULATION_NUMBER/4; i++)
    {
        /// pick  random index
        int k1 = rand() % cross_chrom.size();

        ///mutate bit and add it to muta
        vector<int> val = mutate_bits(cross_chrom.at(k1));
        muta_chrom.push_back(val);
    }
}

///if check is not true, it just ignores best_fit and best_fit_index
void check_fitness(vector<vector<int> > pop, double fitness, double &best_fit, int &best_fit_index, bool &check)
{
    check = false;
    vector<double> pop_dec;
    for(int i = 0; i < pop.size(); i++)
    {
        double dec_val = binary_to_dec(pop.at(i));
        pop_dec.push_back(dec_val);
    }

    best_fit = pop_dec.at(0);
    best_fit_index = 0;

    for(int i = 0; i < pop_dec.size(); i++)
    {
        double current_dec_val = pop_dec.at(i);
        if(abs(current_dec_val - fitness) <= Epsilon)
        {
            check = true;
            if(best_fit > current_dec_val)
            {
                best_fit = current_dec_val;
                best_fit_index = i;
            }
        }
    }
}
int main()
{

    double number;
    cout << "Pick a number 0 < x <= " << MAX_VAL << endl;
    cin >> number;
    //check(number);

    ///fitness function, in this case sqrt of the given number
    double fitness = sqrt(number);


    /// generate random seed
    srand(time(NULL));

    /// generate random starting population
    vector<vector<int> > population(POPULATION_NUMBER);
    population_init(population);
    print_population(population);
    cout << endl;

    int generation = 0;
    bool check;
    double best_fit;
    int best_fit_index;

    do
    {

        /// tournament selection
        vector<vector<int> >select_chrom;
        selection(population, fitness, select_chrom);


        ///crossover
        vector<vector<int> >cross_chrom;
        crossover(select_chrom, cross_chrom);

        ///mutation
        vector<vector<int> >muta_chrom;
        mutation(cross_chrom, muta_chrom);

        //double best_fit;
        //int best_fit_index;
        //bool check;

        check_fitness(muta_chrom, fitness, best_fit, best_fit_index, check);


        ///takes muta_chrom as new population if fitness check fails
        swap(muta_chrom, population);

        ///clear
        select_chrom.clear();
        cross_chrom.clear();
        muta_chrom.clear();

        generation++;
    }while(check == false);

    if(check == true)
    {
        cout << generation << " is good Generation.  " << "Best fit:" << endl;
        print_vector(population.at(best_fit_index) );
        cout << binary_to_dec(population.at(best_fit_index) ) << endl;
    }
}
