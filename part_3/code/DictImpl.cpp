/**
 * Created by: Shriram R.
 * Roll No: 06-02-01-10-51-18-1-15763
 */


#include "IDictionary.h"
#include <list>
#include <iostream>

using namespace std;

struct item {
    int key;
    char *value;
};

char null[] = "";

// Hash table implementation
class HashTableImpl : public IDictionary {

private:

    list<item> *table; // pointer to array of list of items
    int cap;

public:

    HashTableImpl(int capacity) {
        table = new list<item>[capacity];
        cap = capacity;
    }

    void insert(int key, char *value) {
        struct item i = {key, value};
        table[key % cap].push_back(i); // Add to the end of the list
    }

    char *lookup(int key) {
        for (struct item i: table[key % cap]) { // Iterate over each item in the list
            if (i.key == key) {
                return i.value;
            }
        }
        return null;
    }

};

// Unsorted array implementation
class ArrayDictImpl : public IDictionary {

private:

    struct item *table;
    int cap;
    int curr;

public:

    ArrayDictImpl(int capacity) {
        table = new struct item[capacity];
        cap = capacity;
        curr = 0;
    }

    void insert(int key, char *value) {
        if (curr == cap) {
            throw out_of_range(string("Dictionary is full!")); // Throw error if capacity would be exceeded
        }
        struct item i = {key, value};
        table[curr] = i;
        curr++;
    }

    char *lookup(int key) {
        for (int i=0; i<curr; i++) { // Iterate over current items in the array
            if (table[i].key == key) {
                return table[i].value;
            }
        }
        return null;
    }

};

// Sorted array implementation
class BSearchDictImpl : public IDictionary {

private:

    struct item *table;
    int cap;
    int curr;

public:

    BSearchDictImpl(int capacity) {
        table = new struct item[capacity];
        cap = capacity;
        curr = 0;
    }

    void insert(int key, char *value) {
        if (curr == cap) {
            throw out_of_range(string("Dictionary is full!")); // Throw error if capacity would be exceeded
        }
        struct item i = {key, value};
        table[curr] = i;
        curr++;
    }

    char *lookup(int key) { // Perform binary search
        int left, right, mid;
        left = 0;
        right = curr - 1;
        while (left <= right) {
            mid = (left + right) / 2;
            if (table[mid].key == key) {
                return table[mid].value;
            } else if (table[mid].key > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return null;
    }

    void sort() { // Use quicksort to sort the elements of the array
        qsort(table, curr, sizeof(item), compare);
    }

    static int compare(const void *a, const void *b) { // Comparator for quick sort
        return (*(item *) a).key - (*(item *) b).key;
    }

};