#ifndef LIST_H_MCVI
#define LIST_H_MCVI

#define PRINT_MAX_DIGITS

#include <stdbool.h>

typedef struct list list;

list* listConstruct(unsigned);
void listDestruct(list**);
list* listCopy(list*);

// Element access
double listAt(list*, unsigned);
double listFront(list*);
double listBack(list*);
double* listData(list*);
list* listSlice(list*, unsigned, unsigned);

// Math
double listMax(list*);
double listMin(list*);
double listSum(list*);
double listAverage(list*);

// Capacity
bool listEmpty(list*);
unsigned listSize(list*);

// Modifiers
void listSet(list*, unsigned, double);
void listPushBack(list*, double);
void listPushFront(list*, double);
void listInsert(list*, unsigned, double);
void listErase(list*, unsigned);
void listClear(list*);
double listPopBack(list*);
double listPopFront(list*);
void listReverse(list*);

// Content
bool listContains(list*, double);
unsigned listCount(list*, double);
int listIndexOf(list*, double);
bool listEquals(list*, list*);

// Algorithms
void listSort(list*);
void listShuffle(list*);

// Information
void listPrint(list*);

#endif
