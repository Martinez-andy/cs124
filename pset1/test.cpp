#include <iostream>
#include <algorithm>
#include <stdio.h>

int* bubbleSort(const int arr[], int size);
void printArr(int arr[], int size);
int* twistedBubble(const int arr[], int size);

int main() {
    const int size = 12;
    int arr[size] = {-3, 3, 7, 0, 2, 12, 1, 14, 5, 8, 9, 0};

    int* normal = bubbleSort(arr, size);

    int* twisted = twistedBubble(arr, size);

    printArr(normal, size);
    printArr(twisted, size);

    return 0;
}

int* bubbleSort(const int arr[], int size) {
    int* sortedArr = new int[size];
    std::copy(arr, arr + size, sortedArr);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (sortedArr[j + 1] < sortedArr[j]) {
                int temp = sortedArr[j];
                sortedArr[j] = sortedArr[j + 1];
                sortedArr[j + 1] = temp;
            }
        }
    }
    return sortedArr;
}

int* twistedBubble(const int arr[], int size) {
    int* sortedArr = new int[size];
    std::copy(arr, arr + size, sortedArr);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (sortedArr[i] < sortedArr[j]) {
                int temp = sortedArr[i];
                sortedArr[i] = sortedArr[j];
                sortedArr[j] = temp;
            }
        }
    }
    return sortedArr;
}

void printArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%i, ", arr[i]);
    }
    printf("\n");
    return;
}