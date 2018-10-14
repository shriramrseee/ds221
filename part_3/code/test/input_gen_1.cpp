#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    int n, c;
    cin >> c >> n;
    for (int i=0; i<n; i++) {
        cout << i*c + 10 << "\t" << "This is the " << i << "th element\n";
    }
    return 0;
}