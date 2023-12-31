/** The lec5.cpp is for namespace.
 *  @author:cscourage
 *  @url:https://github.com/cscourage/CS106L
*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;    using std::endl;


namespace Lecture {
int count(const vector<int>& v) {
    int ctr = 0;
    for (auto i : v) {
        if (i == 1) {
            ++ctr;
        }
    }
    return ctr;
}
}


int main() {
    vector<int> v{3, 1, 4, 1, 5, 9};
    int count = 0;
    for (auto i : v) {
        if (i == 1) {
            ++count;
        }
    }
    cout << "manual count: " << count << endl;

    // billion lines later...
    // 现实中就是在很久之后忘了或者接手别人的代码时不知道有没有定义过一些比较common的函数，
    // 用namespace的话就可以显示避免这类问题.

    cout << "lecture count: " << Lecture::count(v) << endl;

    cout << "algorithm count: " << std::count(v.begin(), v.end(), 1) << endl;

    return 0;
}