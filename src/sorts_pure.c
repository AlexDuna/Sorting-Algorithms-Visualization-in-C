#include "sorts.h"
#include <stdbool.h>
#include <stdlib.h>

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void bubble_sort_pure(int *array, int n) {
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++) {
    swapped = false;
    for (j = 0; j < n - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        swap(&array[j], &array[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

int partition_pure(int *array, int low, int high) {
  int pivot = array[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (array[j] < pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[high]);
  int pivotIndex = i + 1;

  return pivotIndex;
}

static void quick_sort_rec(int *array, int low, int high, int n) {
  if (low >= high)
    return;

  int pivotIndex = partition_pure(array, low, high);

  quick_sort_rec(array, low, pivotIndex - 1, n);
  quick_sort_rec(array, pivotIndex + 1, high, n);
}

void quick_sort_pure(int *array, int n) { quick_sort_rec(array, 0, n - 1, n); }

void insertion_sort_pure(int *array, int n) {
  for (int i = 1; i < n; i++) {
    int key = array[i];
    int j = i - 1;

    while (j >= 0 && array[j] > key) {
      array[j + 1] = array[j];
      j--;
    }

    array[j + 1] = key;
  }
}

static void merge_segments_pure(int *array, int left, int mid, int right,
                                int *temp) {
  int i = left;
  int j = mid + 1;
  int k = left;

  while (i <= mid && j <= right) {
    if (array[i] <= array[j]) {
      temp[k] = array[i];
      i++;
    } else {
      temp[k] = array[j];
      j++;
    }
    k++;
  }

  while (i <= mid) {
    temp[k] = array[i];
    i++;
    k++;
  }

  while (j <= right) {
    temp[k] = array[j];
    j++;
    k++;
  }

  for (int idx = left; idx <= right; idx++) {
    array[idx] = temp[idx];
  }
}

static void merge_sort_rec(int *array, int left, int right, int *temp, int n) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort_rec(array, left, mid, temp, n);
  merge_sort_rec(array, mid + 1, right, temp, n);

  merge_segments_pure(array, left, mid, right, temp);
}

void merge_sort_pure(int *array, int n) {
  int *temp = malloc(n * sizeof(int));
  if (!temp) {
    return;
  }

  merge_sort_rec(array, 0, n - 1, temp, n);

  free(temp);
}

static void heapify_pure(int *array, int n, int i) {
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
    int tmp = array[i];
    array[i] = array[largest];
    array[largest] = tmp;

    heapify_pure(array, n, largest);
  }
}

void heap_sort_pure(int *array, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify_pure(array, n, i);
  }

  for (int end = n - 1; end > 0; end--) {
    int tmp = array[0];
    array[0] = array[end];
    array[end] = tmp;
    heapify_pure(array, end, 0);
  }
}
