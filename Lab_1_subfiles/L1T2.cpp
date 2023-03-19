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


bool binpoisk(int* mas, int N, int a){
    int midd = 0;
    int right=N-1;
    int left=0;
	while (1)
	{
		midd = (left + right) / 2;
		
		if (a < mas[midd])       
			right = midd - 1;      
		else if (a > mas[midd])  
			left = midd + 1;	   
		else                       
			return true;           

		if (left > right)          
			return false;
	}
    }


int main(){
    int h=60000;
    int shag=500;
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
    auto start = chrono::steady_clock::now();
    binpoisk(arr, N, GetRandomNumber(N));
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