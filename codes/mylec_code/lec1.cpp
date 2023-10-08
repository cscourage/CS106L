#include <iostream>
#include <vector>
#include <numeric>

using std::cout, std::endl;
using std::vector;

// hello world的示例在这里就不呈现了.


void demo1() {
    vector<int> vec = {1, 2, 3};
    int sum = 0;
    for (auto val : vec) {
        sum += val;
    }
    cout << "Demo1: sum is " << sum << endl;
}

void demo2() {
    vector<int> vec = {1, 2, 3};
    int sum = 0;
    for (const auto& val : vec) {
        sum += val;
    }
    cout << "Demo2: sum is " << sum << endl;
}

void demo3() {
    vector<int> vec = {1, 2, 3};
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    cout << "Demo3: sum is " << sum << endl;
}


int main() {
    demo1();
    demo2();
    demo3();
    return 0;
}