# list
Opaque C struct for a dynamic list

## Public methods



### **Constructing/Destructing**

### list* listConstruct(unsigned)
Constructs a list from a specified number of doubles and returns the pointer.

```
list* l = listConstruct(10); // Constructs a list with memory allocated for 10 doubles
```

### void listDestruct(list**)
Destructs a list and frees all dynamically allocated memory.

```
listDestruct(&l);
```

### list* listCopy(list*)
Returns a copy of the provided list.

```
list* l2 = listCopy(l);
```



### **Element Access**

### double listAt(list*, unsigned)
Returns the double at the index specified.

```
double d = listAt(l, 0); // Returns the double at the first index in l
```

### double listFront(list*)
Returns the front of the provided list.

```
double d = listFront(l);
```

### double listBack(list*)
Returns the last double in the provided list.

```
double d = listBack(l);
```

### void listData(list*, double**)
Copies the list into a double array.

```
double* arr;
listData(l, &arr);
// Do something with arr
free(arr); // Remember to free any memory
```

### list* listSlice(list*, unsigned, unsigned)
Returns a list containing a slice of the provided list.

```
list* lSlice = listSlice(l, 1, 3); // Returns a list containing all elements in indices [1, 3] of l
```



### **Math**

### double listMax(list*)
Returns the maximum number in a list.

```
double max = listMax(l);
```

### double listMin(list*)
Returns the minimum number in a list.

```
double min = listMin(l);
```

### double listSum(list*)
Returns the sum of all elements in the list.

```
double sum = listSum(l);
```

### double listAverage(list*)
Returns the average of all elemements in the list.

```
double ave = listAverage(l);
```



### **Capacity**

### bool listEmpty(list*)
Returns true if the list is empty, false if there are elements in the list.

```
if (listEmpty(l)) {
    // Do something
}
```

### unsigned listSize(list*)
Returns the number of elements in a list.

```
unsigned i = listSize(l);
```



### **Modifiers**

### void listSet(list*, unsigned, double)
Sets an element at an index to a provided value.

```
listSet(l, 0, 1.4); // Sets the first element of l to 1.4
```

### void listPushBack(list*, double)
Pushes an element onto the back of the list.

```
listPushBack(l, 1.5);
```

### void listPushFront(list*, double)
Pushes an element onto the front of the list.

```
listPushFront(l, 1.5); // 1.5 is now the first element of l
```

### void listInsert(list*, unsigned, double)
Inserts an element into a list at an index.

```
listInsert(l, 2, 2.0); // Inserts 2.0 into index 2 in l
```

### void listErase(list*, unsigned)
Erases an element at an index.

```
listErase(l, 2); // Erases the element at index 2 in l
```

### void listClear(list*)
Erases all elements in a list and releases all memory. Not a destructor.

```
listClear(l);
```

### double listPopBack(list*)
Pops an element off the back of the list and returns it.

```
double d = listPopBack(l);
```

### double listPopFront(list*)
Pops an element off of the front of the list and returns it.

```
double d = listPopFront(l);
```

### void listReverse(list*)
Reverses a list.

```
listReverse(l);
```



### **Content**

### bool listContains(list*, double)
Returns true if a list contains an element.

```
if (listContains(l, 1.2)) {
    // Do something...
}
```

### unsigned listCount(list*, double)
Returns the count of a number in the list.

```
unsigned i = listCount(l, 1.2); // Gets how many occurrences of 1.2 are in l
```

### int listIndexOf(list*, double)
Returns the index of an element in a list or -1 if it cannot be found.

```
int i = listIndexOf(l, 1.2);
if (i == -1) {
    // Do something...
}
```

### bool listEquals(list*, list*)
Tests for equality between two lists.

```
list* l2 = listCopy(l);
listPushBack(l2, 1.0);

if (listEquals(l, l2)) { // Returns false
    // Do something...
}
```



### **Algorithms**

### void listSort(list*)
Sorts a list.

```
listSort(l);
```

### void listShuffle(list*)
Shuffles a list.

```
listShuffle(l);
```



### **Information**

### void listPrint(list*)
Prints a list's elements in one line.

```
listPrint(l);
```