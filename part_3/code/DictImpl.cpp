#include "IDictionary.h"
#include <list>
#include <iostream>

using namespace std;

struct item {
    int key;
    char *value;
};

class HashTableImpl : public IDictionary {

private:

    list<item> *table;
    int cap;

public:

    HashTableImpl(int capacity) {
        table = new list<item>[capacity];
        cap = capacity;
    }

    void insert(int key, char *value) {
        struct item i = {key, value};
        table[key % cap].push_back(i);
    }

    char *lookup(int key) {
        for (struct item i: table[key % cap]) {
            if (i.key == key) {
                return i.value;
            }
        }
        return 0;
    }

};

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
        struct item i = {key, value};
        table[curr] = i;
        curr++;
    }

    char *lookup(int key) {
        for (int i=0; i<curr; i++) {
            if (table[i].key == key) {
                return table[i].value;
            }
        }
        return 0;
    }

};


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
        struct item i = {key, value};
        table[curr] = i;
        curr++;
    }

    char *lookup(int key) {
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
        return 0;
    }

    void sort() {
        qsort(table, curr, sizeof(item), compare);
    }

    static int compare(const void *a, const void *b) {
        return (*(item *) a).key - (*(item *) b).key;
    }

};