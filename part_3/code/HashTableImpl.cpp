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

int main() {
    HashTableImpl h(10);
    char* c = "apple";
    char* d = "orange";
    h.insert(3, c);
    h.insert(5, d);
    cout << h.lookup(3) << " " << h.lookup(5) << "\n";
    return 0;

}

