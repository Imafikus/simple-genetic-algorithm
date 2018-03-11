#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>

const double MAX_VAL = 65536;
const int VECTOR_SIZE = 16;

using namespace std;

///NOTE, this always converts upper half to the whole numbers, and lower half to values < 1
double binary_to_dec(vector<int> &v)
{
    //cout << "Size: " << v.size() << endl;
    double dec_number = 0;
    int lower_limit= -v.size()/2;
    int upper_limit = v.size()/2-1;

    //cout << "lower: " << lower_limit << " upper: " << upper_limit << endl;

    int pos = 0;
    for(int i = upper_limit; i >= lower_limit; i--)
        {
            if(v.at(pos) == 1)
            {
                dec_number += pow(2, i);
                //double vr = pow(2, i);
                //cout << "vr: " << vr << endl;
            }
            pos++;
        }
    return dec_number;
}
///NOTE size of the binary number is determined by
void vector_init(vector<int> &v)
{
    int val;
    srand(time(NULL));

    for(int i = 0; i < VECTOR_SIZE; i++)
        {
            val = rand() % 2;
            v.push_back(val);
        }

}
void print_vector(vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
        cout << v.at(i) << " ";
    cout << endl;

}
int main()
{
    //srand(time(NULL));

    //int n = rand() % 1000;

    vector<int> v;
    vector_init(v);
    print_vector(v);
    double n = binary_to_dec(v);
    cout << n << endl;
}
