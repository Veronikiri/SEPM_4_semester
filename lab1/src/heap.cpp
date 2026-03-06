#include <iostream>

void swap(int *array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void heapify(int n, int *array, int i) {
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && array[left] > array[largest]) {
        largest = left;
    }
    
    if (right < n && array[right] > array[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(array, i, largest);
        heapify(n, array, largest);
    }
}

void my_sort(int n, int *array) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(n, array, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        swap(array, 0, i); 
        heapify(i, array, 0);
    }
}
