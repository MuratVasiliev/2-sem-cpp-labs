# Лабораторная работа 2
## Часть 1: Шейкерная сортировка
В первой части я реализовал алгоритмы сортировки пузырьком и шейкерной сортировки. Вот код, реализующий их, а также сохраняющий время работы программы в отдельный файл, из которого затем я строил график.
```
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


void bubble_sort(int *arr, int n){
for (unsigned int i = 0; i < n-1; i++) {
        bool swapped = false;
        for (unsigned int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }}
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
    while (left < right ) {
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
```
Я построил график времени работы от числа элементов для сортировки пузырьком:

![This is an image](/Lab_2_subfiles/G_1.png)

И для шейкерной сортировки

![This is an image](/Lab_2_subfiles/G_2.png)

Ассимтотика и там и там квадратична.
##Сортировка расческой
Далее я написал код для реализации сортировки расческой:

```
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

void bubble_sort(int *arr, int n){
for (unsigned int i = 0; i < n-1; i++) {
        bool swapped = false;
        for (unsigned int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }}
void change_order(int *arr, int n, int gap, int i){
    if (arr[i]>arr[i+gap]) {
        int temp = arr[i];
        arr[i] = arr[i+gap];
        arr[i+gap] = temp;
}}

void ras_sort(int *arr, int n){
    int gap = n/2;
    while(gap > 2){
        for(int i = 0; i < n - gap; i+=gap){
            change_order(arr, n, gap, i);}
        gap /= 2;
    }
    bubble_sort(arr, n);
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
    ras_sort(arr, N);
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
```
Вот график для времени работы от количества элементов:

![This is an image](/Lab_2_subfiles/G_3.png)

Также я немного переписал этот код, чтобы построить график количества перестановок от N. Функции сортировки теперь имеют тип int и выдают как раз количество перестановок:
```
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
```
И график количества перестановок от N:

![This is an image](/Lab_2_subfiles/G_4.png)

## Сортировка Шелла
Сортировка Шелла с первой данной последовательностью шагов это и есть сортировка расческой, которая была мною реализована в прошлом пункте. Реализую вторую последовательность:
