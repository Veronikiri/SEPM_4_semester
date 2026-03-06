#include <iostream>

void merge(int *array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;   
    int *left_array = new int[n1];
    int *right_array = new int[n2];
    
    for (int i = 0; i < n1; i++) {left_array[i] = array[left + i];}
    for (int i = 0; i < n2; i++) {right_array[i] = array[mid + 1 + i];}
    
    int i = 0;
    int j = 0;
    int k = left;
    
    while (i < n1 && j < n2) {
        if (left_array[i] <= right_array[j]) {array[k] = left_array[i];
            i = i + 1;}
            else {
            array[k] = right_array[j];
            j = j + 1;
        }
        k = k + 1;
    }
    
    while (i < n1) {
        array[k] = left_array[i];
        i = i + 1;
        k = k + 1;
    }
    
    while (j < n2) {
        array[k] = right_array[j];
        j = j + 1;
        k = k + 1;
    }
    
    delete[] left_array;
    delete[] right_array;
}

void merge_sort_recursive(int *array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(array, left, mid);
        merge_sort_recursive(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void my_sort(int n, int *array) {
    if (n > 1) {
        merge_sort_recursive(array, 0, n - 1);
    }
}
