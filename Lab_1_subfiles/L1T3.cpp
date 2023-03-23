#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <random>

using namespace std;
unsigned seed = 1001;
default_random_engine rng(seed);

int GetRandomNumber(int N)
{
    uniform_int_distribution<unsigned> dstr(0, N);
	int num = dstr(rng);
    return num;
}
bool sumpoisk(int* mas, int N, int sum)
    {
    int l = 0, r = N-1;
    
    while (l!= r)
    {
        int cur_sum = mas[l] + mas[r];
        
        if (cur_sum > sum) r--;
        
        else if (cur_sum < sum) l++;
        
        else return true;
    }
    
    return false;
}


int main(){
    int h=5000;
    int shag=1000;
    int ite=1;
    int MAX=100000;
    int k = (ite)*(MAX-100)/shag;
    ofstream fin("numbers.txt");
    fin << k;
    fin << endl;
    for(int j=0; j<ite; j++){
    for (int N=100; N<MAX; N=N+shag){
        int* arr = new int[N];
        for(int i=0;i<N; i++){
            arr[i]=i;
        }
    long long count=0;
    for (k=0; k<h; k++){
    long long p=GetRandomNumber(2*N);
    auto start = chrono::steady_clock::now();
    sumpoisk(arr, N, p);
    auto stop = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast < chrono::nanoseconds> (stop - start);
    count=count+time_span.count();
    }
    int time = count/h; 
    fin << time;
    fin << endl;
    fin << N;
    fin << endl;
    }}
    }