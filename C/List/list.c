#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef REDUCE_MEMORY_THRESHOLD
#define REDUCE_MEMORY_THRESHOLD 0.25
#endif

typedef struct list {
  double* data;
  unsigned size;
  unsigned len;
} list;


// ===========================
// Private function prototypes

// Algorithms
static void listMerge(list*, unsigned, unsigned, unsigned);
static void listMergeSort(list*, unsigned, unsigned);

// Memory
static double listMemoryUsed(list*);
static void listDoubleMemory(list*);
static void listHalveMemory(list*);
static void listClearMemory(list*);


// ==============================
// Public function implementation

list* listConstruct(unsigned length) {
  list* l = malloc(sizeof(list));
  l->size = length;
  l->len = 0;
  l->data = malloc(sizeof(double) * length);
  
  return l;
}

void listDestruct(list** lPtr) {
  if (lPtr) {
    if (*lPtr) {
      free((**lPtr).data);
      (**lPtr).data = NULL;
    }
    free(*lPtr);
    *lPtr = NULL;
  }
}

list* listCopy(list* l) {
  unsigned i;
  list* newL = listConstruct(l->size);

  for (i = 0; i < l->len; i++) {
    newL->data[i] = l->data[i];
  }
  
  return newL;
}

// Element access
double listAt(list* l, unsigned index) {
  assert(index < l->len);
  return l->data[index];
}

double listFront(list* l) {
  assert(l->len > 0);
  return l->data[0];
}

double listBack(list *l) {
  assert(l->len > 0);
  return l->data[l->len - 1];
}

void listData(list* l, double** arr) {
  unsigned i;
  *arr = malloc(sizeof(double) * l->len);

  for (i = 0; i < l->len; i++) {
    (*arr)[i] = l->data[i];
  }
}

list* listSlice(list* l, unsigned start, unsigned end) {
  assert(end >= start);
  assert(start >= 0);
  assert(end < l->len);
  unsigned i;
  list* slice = listConstruct(end - start + 1);

  for (i = start; i <= end; i++) {
    slice->data[i - start] = l->data[i];
  }

  return slice;
}

// Math
double listMax(list* l) {
  assert(l->len > 0);
  unsigned i;
  double max = l->data[0];

  for (i = 1; i < l->len; i++) {
    if (l->data[i] > max) max = l->data[i];
  }

  return max;
}

double listMin(list* l) {
  assert(l->len > 0);
  unsigned i;
  double min = l->data[0];

  for (i = 1; i < l->len; i++) {
    if (l->data[i] < min) min = l->data[i];
  }

  return min;
}

double listSum(list* l) {
  assert(l->len > 0);
  unsigned i;
  double sum;

  for (i = 0; i < l->len; i++) {
    sum += l->data[i];
  }

  return sum;
}

double listAverage(list* l) {
  return listSum(l) / (double)listSize(l);
}

// Capacity
bool listEmpty(list* l) {
  return l->len == 0;
}

unsigned listSize(list* l) {
  return l->len;
}

// Modifiers
void listSet(list* l, unsigned index, double d) {
  assert(index < l->len);
  l->data[index] = d;
}

void listPushBack(list* l, double d) {
  if (l->len == l->size) {
    listDoubleMemory(l);
  }

  l->data[l->len] = d;
  l->len++;
}

void listPushFront(list* l, double d) {
  unsigned i;

  if (l->len == l->size) {
    listDoubleMemory(l);
  }

  for (i = l->len; i > 0; i--) {
    l->data[i] = l->data[i - 1];
  }

  l->data[0] = d;
  l->len++;
}

void listInsert(list* l, unsigned index, double d) {
  assert(index <= l->len);
  unsigned i;

  if (l->len == l->size) {
    listDoubleMemory(l);
  }

  for (i = l->len; i > index; i--) {
    l->data[i] = l->data[i - 1];
  }

  l->data[index] = d;
  l->len++;
}

void listErase(list* l, unsigned index) {
  assert(index < l->len);
  unsigned i;

  for (i = index; i < l->len - 2; i++) {
    l->data[i] = l->data[i + 1];
  }

  if (listMemoryUsed(l) <= REDUCE_MEMORY_THRESHOLD) listHalveMemory(l);

  l->len--;
}

void listClear(list* l) {
  l->len = 0;
}

double listPopBack(list* l) {
  assert(l->len > 0);
  l->len--;

  if (listMemoryUsed(l) <= REDUCE_MEMORY_THRESHOLD) listHalveMemory(l);
  
  return l->data[l->len];
}

double listPopFront(list* l) {
  assert(l->len > 0);
  unsigned i;
  double d = l->data[0];

  for (i = 0; i < l->len - 2; i++) {
    l->data[i] = l->data[i + 1];
  }

  l->len--;
  if (listMemoryUsed(l) <= REDUCE_MEMORY_THRESHOLD) listHalveMemory(l);
  
  return d;
}

void listReverse(list* l) {
  unsigned i;
  for (i = 0; i < l->len / 2; i++) {
    double d = l->data[l->len - 1];
    l->data[l->len - i] = l->data[i];
    l->data[i] = d;
  }
}

// Content
bool listContains(list* l, double d) {
  unsigned i;

  for (i = 0; i < l->len; i++) {
    if (l->data[i] == d) return true;
  }
  
  return false;
}

unsigned listCount(list* l, double d) {
  unsigned i;
  unsigned count = 0;

  for (i = 0; i < l->len; i++) {
    if (l->data[i] == d) count++;
  }
  
  return count;
}

int listIndexOf(list* l, double d) {
  unsigned i;

  for (i = 0; i < l->len; i++) {
    if (l->data[i] == d) return i;
  }

  return -1;
}

bool listEquals(list* l1, list* l2) {
  if (l1->len != l2->len) return false;

  unsigned i;
  for (i = 0; i < l1->len; i++) {
    if (l1->data[i] != l2->data[i]) return false;
  }
  
  return true;
}

// Algorithms
void listSort(list* l) {
  listMergeSort(l, 0, l->len - 1);
}

void listShuffle(list* l) {
  unsigned i;
  for (i = 0; i < l->len - 1; i++) {
    unsigned j = i + rand() / (RAND_MAX / (l->len - i) + 1);
    double d = l->data[j];
    l->data[j] = l->data[i];
    l->data[i] = d;
  }
}

// Information
void listPrint(list* l) {
  unsigned i;

  for (i = 0; i < l->len; i++) {
    if (l->data[i] == (int)l->data[i]) {
      printf("%i ", (int)l->data[i]);
    }
    else {
      printf("%f ", l->data[i]);
    }
  }
  
  printf("\n");
}


// ===============================
// Private function implementation

// Algorithms
static void listMerge(list* l, unsigned left, unsigned mid, unsigned right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  double L[n1], R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = l->data[left + i];
  }
  
  for (i = 0; i < n2; i++) {
    R[i] = l->data[mid + 1 + i];
  }

  i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      l->data[k] = L[i];
      i++;
    }
    else {
      l->data[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    l->data[k] = L[i];
    i++, k++;
  }

  while (j < n2) {
    l->data[k] = R[j];
    j++, k++;
  }
  
}

static void listMergeSort(list* l, unsigned left, unsigned right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    listMergeSort(l, left, mid);
    listMergeSort(l, mid + 1, right);

    listMerge(l, left, mid, right);
  }
}

// Memory
static double listMemoryUsed(list *l) {
  return (double)l->len / (double)l->size;
}

static void listDoubleMemory(list* l) {
  if (l->size > 0) l->size *= 2;
  else l->size = 1;
  
  l->data = realloc(l->data, sizeof(double) * l->size);
}

static void listHalveMemory(list* l) {
  assert((double)l->len / (double)l->size <= 0.50);

  double newSize = (double)l->len / 2.0;
  if (newSize - (unsigned int)newSize > 0.50f) newSize += 1.0;
  l->size = (unsigned int)newSize;
  l->data = realloc(l->data, newSize);
}


static void listClearMemory(list* l) {
    free(l->data);
    l->len = 0;
    l->size = 0;
}