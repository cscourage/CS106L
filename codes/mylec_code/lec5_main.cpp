#include "lec5_MyVector.h"
#include <vector>
#include <chrono>

using std::string;
MyVector<string> findAllWords(size_t size);


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    MyVector<string> names1 = findAllWords(1433223);
    MyVector<string> names2;
    names2 = findAllWords(1433223);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Time took: " << elapsed.count() << endl;

    return 0;
}

MyVector<string> findAllWords(size_t size) {
    MyVector<string> names(size, "Ito");
    return names;
}