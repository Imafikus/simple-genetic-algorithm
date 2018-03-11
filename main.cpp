#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>

const double MAX_VAL = 65536;

using namespace std;


double binary_to_dec(vector<int> &v)
{
    double dec_number = 0;
    int i = -v.size()/2;
    int limit = v.size()/2-1;
    for(int i; i < limit; i++)
        {
            if(v.at(i) = 1) dec_number += pow(2, i);
        }
}
void vector_init(vector<int> &v)
{
    int vec_size = 16;
    int val;
    srand(time(NULL));

    for(int i = 0; i < vec_size; i++)
        {
            val = rand() % 2;
            v.push_back(val);
        }

}
void print_vector(vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
        cout << v.at(i) << " " << endl;

}
int main()
{
    //srand(time(NULL));

    //int n = rand() % 1000;

    vector<int> v;
    vector_init(v);
    print_vector(v);
}
