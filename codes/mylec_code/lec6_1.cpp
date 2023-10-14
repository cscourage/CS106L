/** The lec6_1.cpp is for lecture meta programing.
 *  @author:cscourage
 *  @url:https://github.com/cscourage/CS106L
 *  有两个版本，一个是讲makefile的，一个是讲meta programing的，本cpp文件对应meta programing的视频版本.
*/

#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>

using std::vector;    using std::set;    using std::deque;
using std::string;
using std::cout;    using std::endl;


template <typename It>
size_t my_distance(It first, It last) {
    using category = typename std::iterator_traits<It>::iterator_category;

    // 因为set的iterator不是random access，所以需要进行分支.
    // 减法的时间复杂度为O(1)，而迭代的时间复杂度为O(n)，因为需要分支让这个generic的程序尽可能快，
    // 等到输入是与set相关的iterator时再缓慢迭代.

    // if constexpr会在编译时将if-else语句的代码直接替换成要执行的那部分代码，这样就避免了
    // set仍然编译失败的结果（即使我们知道if不会执行而是执行else）
    // 因为c++没有提供像python那样的type()来获取类型，因此这里用到了meta-function，其实历史上对于meta-function
    // 的发现是偶然的，同时因为它还比较有用，因此延续至今.
    if constexpr (std::is_same<category, std::random_access_iterator_tag>::value) {
        return last - first;
    } else {
        int count = 0;
        while (first != last) {
            ++first;
            ++count;
        }
        return count;
    }
}


int main() {
    set<string> names{"Anna", "Ethan", "Nikhil", "Avery"};
    auto anna_iter = std::find(names.begin(), names.end(), "Anna");
    auto avery_iter = std::find(names.begin(), names.end(), "Avery");

    cout << my_distance(anna_iter, avery_iter) << endl;

    return 0;
}