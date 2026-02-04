#include "sorts.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 100
#define ARRAY_SIZE 200
#define MAX_VALUE 1000

static void fill_random(int *a, int n) {
  for (int i = 0; i < n; i++) {
    a[i] = rand() % MAX_VALUE;
  }
}

static bool is_sorted(const int *a, int n) {
  for (int i = 1; i < n; i++) {
    if (a[i - 1] > a[i]) {
      return false;
    }
  }
  return true;
}

static bool test_algorithm(void (*sort_fn)(int *, int), const char *name) {
  int *a = malloc(sizeof(int) * ARRAY_SIZE);
  int *b = malloc(sizeof(int) * ARRAY_SIZE);

  if (!a || !b) {
    fprintf(stderr, "malloc failed in test_algorithm\n");
    free(a);
    free(b);
    return false;
  }

  for (int t = 0; t < NUM_TESTS; t++) {
    fill_random(a, ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++) {
      b[i] = a[i];
    }

    sort_fn(a, ARRAY_SIZE);

    if (!is_sorted(a, ARRAY_SIZE)) {
      fprintf(stderr, "[%s] FAILED: array not sorted (test %d)\n", name, t);
      free(a);
      free(b);
      return false;
    }
  }

  printf("[OK] %s passed %d tests \n", name, NUM_TESTS);
  free(a);
  free(b);
  return true;
}

int main() {
  srand((unsigned)time(NULL));

  bool ok = true;

  ok &= test_algorithm(bubble_sort_pure, "Bubble Sort");
  ok &= test_algorithm(quick_sort_pure, "Quick Sort");
  ok &= test_algorithm(insertion_sort_pure, "Insertion Sort");
  ok &= test_algorithm(merge_sort_pure, "Merge Sort");
  ok &= test_algorithm(heap_sort_pure, "Heap Sort");

  if (!ok) {
    printf("Some tests FAILED.\n");
    return 1;
  }

  printf("All tests PASSED.\n");
  return 0;
}
