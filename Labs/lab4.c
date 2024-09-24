//10. Числа від 0 до 500, що не зустрічаються а ні в масиві A, а ні в B.
//Алгоритми пошуку: бінарний, Фібоначі.
//Вхідні масиви цілих чисел містять по 500 елементів із випадковими числами зі значеннями від 0 до N-1. N=1000;
//Визначити кількість порівнянь при виконанні різних алгоритмів

#include <iostream>
#include <algorithm>

using namespace std;

// Функція для бінарного пошуку
int binarySearch(int arr[], int size, int target, int &comparisons) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        comparisons++;
        if (arr[mid] == target) {
            return mid;
        }
        comparisons++;
        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;  // Якщо не знайдено
}

// Функція для пошуку Фібоначчі
int fibonacciSearch(int arr[], int size, int target, int &comparisons) {
    // перші два числа Фібоначчі
    int fib2 = 0;  // (m-2)'е число Фібоначчі
    int fib1 = 1;  // (m-1)'е число Фібоначчі
    int fibM = fib2 + fib1;  // m'е число Фібоначчі

    // Знаходимо найменше число Фібоначчі більше або рівне size
    while (fibM < size) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    // Вказуємо на видиму частину масиву
    int offset = -1;

    while (fibM > 1) {
        // Перевіряємо чи валідна позиція
        int i = min(offset + fib2, size - 1);// Якщо (offset + fib2) більше (size - 1), то використовуємо (size - 1), або ж (offset + fib2), якщо (offset + fib2) менше (size - 1)
        comparisons++;
        if (arr[i] < target) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (arr[i] > target) {
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        } else {
            return i;  // Знайдено
        }
    }

    // Якщо залишився один елемент, перевіряємо його
    if (fib1 && arr[offset + 1] == target) {
        comparisons++;
        return offset + 1;
    }

    return -1;  // Якщо не знайдено
}

int main() {
    const int N = 1000;
    const int SEARCH_RANGE = 500;
    int A[500], B[500];

    // Заповнюємо масиви випадковими числами (для прикладу просто задамо вручну)
    for (int i = 0; i < 500; ++i) {
        A[i] = rand() % N;
        B[i] = rand() % N;
    }

    // Сортуємо масиви для застосування пошуку
    sort(A, A + 500);// Функція sort() використовує алгоритм сортування бульбашкою для сортування масиву A
    sort(B, B + 500);//сортування бульбашкою для масиву B

    int binaryComparisons = 0;
    int fibonacciComparisons = 0;

    cout << "Числа, які не входять в жоден з масивів:" << endl;

    for (int i = 0; i <= SEARCH_RANGE; ++i) {
        // Пошук в обох масивах
        int binA = binarySearch(A, SEARCH_RANGE, i, binaryComparisons);//SEARCH_RANGE = 500
        int binB = binarySearch(B, SEARCH_RANGE, i, binaryComparisons);
        int fibA = fibonacciSearch(A, SEARCH_RANGE, i, fibonacciComparisons);
        int fibB = fibonacciSearch(B, SEARCH_RANGE, i, fibonacciComparisons);

        // Якщо не знайдено в жодному з масивів
        if (binA == -1 && binB == -1 && fibA == -1 && fibB == -1) {
            cout << i << "\t";
        }
    }

    cout <<"\n------------------" <<endl;
    cout << "Кількість порівнянь (бінарний пошук): " << binaryComparisons << endl;
    cout << "Кількість порівнянь (пошук Фібоначчі): " << fibonacciComparisons << endl;

    return 0;
}

