#include "IDictionary.h"
#include <list>
#include <iostream>
#include <cstdlib>

using namespace std;

struct item {
    int key;
    char *value;
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

int main() {
    BSearchDictImpl h(10);
    char *c = "apple";
    char *d = "orange";
    h.insert(5, c);
    h.insert(3, d);
    h.sort();
    cout << h.lookup(3) << " " << h.lookup(5) << "\n";
    return 0;

}





