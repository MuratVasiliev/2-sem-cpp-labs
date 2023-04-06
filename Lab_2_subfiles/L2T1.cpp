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
void swap(int xp, int yp)
{
    int temp = xp;
    xp = yp;
    yp = temp;
}

void bubble_sort(int* arr, int const begin_idx, int const end_idx){
    for (int i = begin_idx; i < end_idx; i++){
        for (int j = begin_idx; j < end_idx - i; j++){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
                }}}
}
void forward_step(int *arr, int const begin_idx, int const end_idx) {
    for (int i = begin_idx; i < end_idx; ++i) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }
}

void backward_step(int *arr, int const begin_idx, int const end_idx) {
    for (int i = end_idx; i > begin_idx; --i) {
        if (arr[i] < arr[i - 1]) {
            swap(arr[i], arr[i - 1]);
        }
    }
}

void shaker_sort(int *arr, int const size) {
    int left = 0;
    int right = size - 1;
    while (left < right) {
        forward_step(arr, left, right);
        --right;
        backward_step(arr, left, right);
        ++left;
    }
}

int main(){
    int h=8;
    int shag=1000;
    int ite=1;
    int MAX=30000;
    int k = (ite)*(MAX-100)/shag;
    ofstream fin("numbers.txt");
    fin << k;
    fin << endl;
    for(int j=0; j<ite; j++){
    for (int N=100; N<MAX; N=N+shag){
        int* arr = new int[N];
        for(int i=0;i<N; i++){
            arr[i]=N-1-i;
        }
    long long count=0;
    for (k=0; k<h; k++){
    long long p=GetRandomNumber(N);
    auto start = chrono::steady_clock::now();
    shaker_sort(arr, N);
    auto stop = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast < chrono::nanoseconds> (stop - start);
    count=count+time_span.count();
    }
    int time = count/h; 
    fin << time;
    fin << endl;
    fin << N;
    fin << endl;
    } 
    }
    
    }