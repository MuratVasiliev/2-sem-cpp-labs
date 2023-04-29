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

void bubble_sort(int* arr, int const begin_idx, int const end_idx, float per){
    bool VV=true;
    while(VV){
    VV=false;
    for (int i = begin_idx; i < end_idx; i++){
        for (int j = begin_idx; j < end_idx - i; j++){
            if (arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                per++;
                VV=true;
                }}}}
}
void change_order(int *arr, int n, int gap, int i, float per){
    if (arr[i] > arr[i + gap]) {
        int temp = arr[i];
        arr[i] = arr[i+gap];
        arr[i+gap] = temp;
        per++;
}}

void ras_sort(int *arr, int n, float per){
    int gap = n/2;
    while(gap > 2){
        for(int i = 0; i < n - gap; i+=gap){
            change_order(arr, n, gap, i, per);}
        gap /= 2;
    }
    bubble_sort(arr, 0, n, per);
}

int main(){
    int h=6;
    float c=0;
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
    c=0;
    for (k=0; k<h; k++){
    long long p=GetRandomNumber(N);
    auto start = chrono::steady_clock::now();
    ras_sort(arr, N, c);
    auto stop = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast < chrono::nanoseconds> (stop - start);
    count=count+time_span.count();
    }
    int time = count/h; 
    int z=c/h;
    fin << time;
    fin << endl;
    fin << N;
    fin << endl;
    } 
    }  
    }