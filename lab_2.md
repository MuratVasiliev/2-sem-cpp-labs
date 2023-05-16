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
В этой части я сначала написал алгоритм сортировки вставками (функция vstavka_sort), и затем три сортировки Шелла для данных последовательностей. 
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

void shell1_sort(int *arr, int n){
    int gap = n;
    while(gap > 0){
        for(int i = 0; i < n - gap; i+=gap){
            change_order(arr, n, gap, i);}
        gap /= 2;
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
    shell1_sort(arr, N);
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

```
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
int max_i(int N){
    int i=0;
    while(pow(2, i)-1<= N){
        i+=1;
    }
    return i-1;
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

void shell2_sort(int *arr, int n){
    int y=max_i(n);
    int gap = pow(2, y)-1;
    while(y > 0){
        for(int i = 0; i < n - gap; i+=gap){
            change_order(arr, n, gap, i);}
        y-=1;
        gap=pow(2, y)-1;
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
    shell2_sort(arr, N);
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

```
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
```
Отмечу, что я специально закомментил проводящуюся в конце сортировку вставками. Она имеет квадратичную ассимтотику, и, как я увидел, убивает практически все различие между последовательностями. Поэтому я исследовал только ассимптотику предварительных проходов. Ниже графики для 1, 2 и 3 последовательностей в логарифмическом масштабе.

![This is an image](/Lab_2_subfiles/G_5.png)

![This is an image](/Lab_2_subfiles/G_6.png)

![This is an image](/Lab_2_subfiles/G_7.png)

Наклоны прямых составили 0.89, 1.01 и 1.1. То есть, быстрее всего с использованием первой последовательности.
