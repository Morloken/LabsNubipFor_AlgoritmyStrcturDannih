#include <iostream>
#include <vector>
#include <algorithm> // Для std::swap
#include <cstdlib>   // Для rand()
#include <ctime>     // Для time()
#define N 1000       
// Константа для розміру масиву

using namespace std;

// Глобальні змінні для підрахунку кількості порівнянь та обмінів
int comparisons = 0;  // Лічильник порівнянь
int exchanges = 0;    // Лічильник обмінів

// Функція для скидання лічильників порівнянь і обмінів
void resetCounters() {
    comparisons = 0;
    exchanges = 0;
}

// Функція для сортування бульбашкою (Bubble Sort)
// Працює шляхом багаторазового обміну сусідніх елементів, якщо вони в неправильному порядку
void bubbleSort(vector<int>& arr) {
    int n = arr.size();  // Отримуємо розмір масиву
    for (int i = 0; i < n - 1; i++) {  // Зовнішній цикл: проходить по всьому масиву
        for (int j = 0; j < n - i - 1; j++) {  // Внутрішній цикл: порівнює сусідні елементи
            comparisons++;  // Кожне порівняння збільшує лічильник
            if (arr[j] > arr[j + 1]) {  // Якщо елемент зліва більше за сусідній справа
                swap(arr[j], arr[j + 1]);  // Міняємо їх місцями
                exchanges++;  // Збільшуємо лічильник обмінів
            }
        }
    }
}

// Функція швидкого сортування (QuickSort) за методом Хоара
// Рекурсивно ділить масив на дві частини та сортує їх окремо
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {  // Базовий випадок для рекурсії
        comparisons++;  // Кожен раз, коли робимо порівняння для поділу
        int pivot = arr[high];  // Вибираємо опорний елемент (останній елемент масиву)
        int i = (low - 1);  // Індекс для меншого елемента

        // Цикл, що знаходить правильну позицію для опорного елемента
        for (int j = low; j <= high - 1; j++) {
            comparisons++;  // Порівняння поточного елемента з опорним
            if (arr[j] < pivot) {  // Якщо поточний елемент менший за опорний
                i++;  // Рухаємо індекс менших елементів
                swap(arr[i], arr[j]);  // Обмінюємо елементи
                exchanges++;  // Лічильник обмінів збільшується
            }
        }
        swap(arr[i + 1], arr[high]);  // Обмін опорного елемента на правильну позицію
        exchanges++;  // Лічильник обмінів збільшується
        int pi = i + 1;  // Індекс, на який поміщений опорний елемент

        // Рекурсивно сортуємо елементи до та після опорного
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Функція сортування Шелла (Shell Sort)
// Працює шляхом поступового зменшення відстані (gap) між елементами для сортування
void shellSort(vector<int>& arr) {
    int n = arr.size();  // Отримуємо розмір масиву
    for (int gap = n / 2; gap > 0; gap /= 2) {  // Цикл зменшує відстань між елементами
        for (int i = gap; i < n; i++) {  // Цикл перебирає всі елементи на певній відстані
            int temp = arr[i];  // Зберігаємо поточний елемент
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {  // Внутрішній цикл для порівняння і обміну
                comparisons++;  // Кожне порівняння збільшує лічильник
                arr[j] = arr[j - gap];  // Зсув елементів
                exchanges++;  // Лічильник обмінів збільшується
            }
            arr[j] = temp;  // Вставляємо поточний елемент на правильне місце
        }
    }
}

// Функція для заповнення масиву найкращим випадком (вже відсортований масив)
void fillBestCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {  // Заповнюємо масив елементами від 0 до n-1
        arr[i] = i;
    }
}

// Функція для заповнення масиву найгіршим випадком (відсортований у зворотньому порядку)
void fillWorstCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {  // Заповнюємо масив елементами від n до 1
        arr[i] = arr.size() - i;
    }
}

// Функція для заповнення масиву випадковими значеннями
void fillRandomCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {  // Заповнюємо масив випадковими числами від 0 до N
        arr[i] = rand() % N;
    }
}

// Функція для виведення результатів (кількість порівнянь і обмінів)
void printResults(const string& caseName, const string& methodName) {
    cout << methodName << " - " << caseName << ": Comparisons = " << comparisons << ", Exchanges = " << exchanges << endl;
}

int main() {
    srand(time(0));  // Ініціалізуємо генератор випадкових чисел

    vector<int> arr(N);  // Оголошуємо масив розміром N

    // Найкращий випадок для Bubble Sort
    fillBestCase(arr);  // Заповнюємо масив у зростаючому порядку
    resetCounters();  // Скидаємо лічильники
    bubbleSort(arr);  // Сортуємо за допомогою бульбашки
    printResults("Best Case", "Bubble Sort");  // Виводимо результати

    // Середній випадок для Bubble Sort
    fillRandomCase(arr);  // Заповнюємо масив випадковими числами
    resetCounters();  // Скидаємо лічильники
    bubbleSort(arr);  // Сортуємо за допомогою бульбашки
    printResults("Average Case", "Bubble Sort");  // Виводимо результати

    // Найгірший випадок для Bubble Sort
    fillWorstCase(arr);  // Заповнюємо масив у спадному порядку
    resetCounters();  // Скидаємо лічильники
    bubbleSort(arr);  // Сортуємо за допомогою бульбашки
    printResults("Worst Case", "Bubble Sort");  // Виводимо результати

   

    return 0;
}
