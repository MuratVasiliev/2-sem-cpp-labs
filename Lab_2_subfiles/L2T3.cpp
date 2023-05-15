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

int bubble_sort(int *arr, int n, int per){
for (unsigned int i = 0; i < n-1; i++) {
        bool swapped = false;
        for (unsigned int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
                per+=1;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return per;}


void change_order(int *arr, int n, int gap, int i){
    if (arr[i]>arr[i+gap]) {
        int temp = arr[i];
        arr[i] = arr[i+gap];
        arr[i+gap] = temp;
}}

int ras_sort(int *arr, int n){
    int per=0;
    int gap = n/2;
    while(gap > 2){
        for(int i = 0; i < n - gap; i+=gap){
            change_order(arr, n, gap, i);
            per+=1;}
        gap /= 2;

    }
    bubble_sort(arr, n, per);
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
    fin << ras_sort(arr, N);
    fin << endl;
    fin << N;
    fin << endl;
    } 
    }  
    }