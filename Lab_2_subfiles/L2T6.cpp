#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <random>
#include <cmath>
using namespace std;

unsigned seed = 1001;
default_random_engine rng(seed);
int GetRandomNumber(int N)
{
    uniform_int_distribution<unsigned> dstr(0, N);
	int num = dstr(rng);
    return num;
}
int fib(int N){
    if (N==1) {return 1;}
    if (N==2) {return 1;}
    return fib(N-1)+fib(N-2);
}
int max_fib(int N){
    int y=1;
    while (fib(y)<=N){
        y+=1;
    }
    return y-1;
}

void vstavka_sort(int* arr, int n) {
    int i, key, j;
    for (i=1; i<n; i++) {
        key = arr[i];
        j=i-1;
        while (j>=0 && arr[j]>key) {
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}


void change_order(int *arr, int n, int gap, int i){
    if (arr[i]>arr[i+gap]) {
        int temp = arr[i];
        arr[i] = arr[i+gap];
        arr[i+gap] = temp;
}}

void shell3_sort(int *arr, int n){
    int y=max_fib(n);
    int gap = fib(y);
    while(y > 1){
        for(int i = 0; i < n - gap; i+=gap){
            change_order(arr, n, gap, i);}
        y-=1;
        gap=fib(y);
    }
    //vstavka_sort(arr, n);
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
    shell3_sort(arr, N);
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