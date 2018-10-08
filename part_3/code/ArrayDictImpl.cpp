#include "IDictionary.h"
#include <list>
#include <iostream>

using namespace std;

struct item {
    int key;
    char *value;
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

int main() {
    ArrayDictImpl h(10);
    char *c = "apple";
    char *d = "orange";
    h.insert(3, c);
    h.insert(5, d);
    cout << h.lookup(3) << " " << h.lookup(5) << "\n";
    return 0;

}



