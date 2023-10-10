/** The lec4.cpp is for lecture templates, stl functions and algorithms.
 *  @author:cscourage
 *  @url:https://github.com/cscourage/CS106L
*/

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>   // for ostream_iterator.
#include <utility>   // for pair/tuple
using namespace std;


struct Course {
    string name;
    double rating;
};


//pair<T, T> my_minmax(const T& a, const T& b). just in case the type is a large collection.
//so T = vector<int> would be okay here.
template<typename T>
pair<T, T> my_minmax(T a, T b) {
    return a < b ? make_pair(a, b) : make_pair(b, a);
}


template<typename T>
void printMinAndMax(T min, T max) {
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << endl;
}


/** 1. iterator to erasure point always invalidated.
 *  2. vector: all iterators after erasure point invalidated.
 *  3. deque: all iterators invalidated (unless erasure point was front or back).
 *  4. list/set/map: all other iterators are still valid.
*/
template<typename T>
void eraseContainerDemo(T& container) {
    auto iter = container.begin();
    auto temp = --container.end();
    advance(iter, 4);
    container.erase(iter);

    for (auto elem : container) {
        cout << elem << " ";
    }
    cout << endl;

    auto val = *iter;
    cout << "after erasing, val is: " << val << endl;
    auto ttemp = *temp;
    cout << "after erasing, *temp is: " << ttemp << endl;
}


template<typename T, typename U>
void erase_all(T& container, U val) {
    for (auto iter = container.begin(); iter != container.end(); ) {
        if (*iter == val) {
            iter = container.erase(iter);
        } else {
            ++iter;
        }
    }

    for (auto elem : container) {
        cout << elem << " ";
    }
    cout << endl;
}


template<typename T, typename U>
void mapErase(T& mymap, U key) {
    for (auto iter = mymap.begin(); iter != mymap.end(); ) {
        if (iter->first == key) {
            iter = mymap.erase(iter);
        } else {
            ++iter;
        }
    }

    for (auto elem : mymap) {
        cout << elem.first << " " << elem.second << endl;
    }
}


// the above two will be slow, cause after erasing all following items will be forwarded.
// let's try another efficient way.
// 因为vector使用erase固有的性能缺陷，所以这里不使用erase了，而是使用类似双指针的解法来优化性能.
// similar to the std::remove_if.
template<typename T, typename U>
void erase_all_efficient(T& container, U val) {
    auto first = container.begin();
    auto last = container.end();
    first = std::find(first, last, val);
    if (first != last) {
        for (auto i = first; ++i != last; ) {
            if (*i != val) {
                *first++ = std::move(*i);
            }
        }
    }
    auto newlast = first;

    for (auto iter = container.begin(); iter != newlast; ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}


template<typename InputIt1, typename InputIt2>
pair<InputIt1, InputIt2> mymismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    while (first1 != last1 && *first1 == *first2) {
        ++first1; ++first2;
    }

    return {first1, first2};
}


// concept-lifting 2.
// a predicate is a function which takes in some number of arguments and returns a boolean.
// The following seems like a higher-order function.
template<typename InputIterator, typename UniPred>
int countOccurences(InputIterator begin, InputIterator end, UniPred predicate) {
    int count = 0;
    for (auto iter = begin; iter != end; ++iter) {
        if (predicate(*iter)) {
            ++count;
        }
    }
    return count;
}


void printCourses(const vector<Course>& courses) {
    for (auto elem : courses) {
        cout << elem.name << " " << elem.rating << endl;
    }
}


int main() {
    //auto [min, max] = my_minmax(9, 5);
    //my_minmax("Anna", "Avery");   // this will deduce that is a c-string, i.e. char*
    //not the string in c++. so remeber that type deduction can't read your mind. So we
    //should explictly assign it. For example, my_minmax<string>("Anna", "Avery").
    //printMinAndMax(min, max);

    list<int> l{3, 1, 4, 1, 5, 2, 6};
    deque<int> d{3, 1, 4, 1, 5, 2, 6};
    vector<int> v{3, 1, 4, 1, 5, 2, 6};
    map<int, int> m{{14, 30}, {15, 20}, {16, 10}, {17, 50}};
    // cout << "the following is list: " << endl;
    // eraseContainerDemo(l);
    // cout << "the following is deque: " << endl;
    // eraseContainerDemo(d);
    // cout << "the following is vector: " << endl;
    // eraseContainerDemo(v);
    // erase_all_efficient(l, 1);
    // erase_all_efficient(d, 1);
    // erase_all_efficient(v, 1);
    // mapErase(m, 15);

    // container.erase和std::remove一起连用，因为std::remove不是container的成员函数，它
    // 把指定的元素discard之后不能将container的大小缩小，所以还需要调用erase.
    v.erase(remove(v.begin(), v.end(), 1), v.end());
    for (auto elem : v) {
        cout << elem << " ";
    }
    cout << endl;

    // vector<int> v1{1, 2, 3, 4};
    // vector<int> v2{1, 2, 4, 6};
    // vector<int> v3{1, 2, 3, 4};
    // vector<int> v4{1, 2, 3};

    // auto [f1, f2] = mymismatch(v1.begin(), v1.end(), v2.begin()); // {false, 3, 4}
    // cout << "f1: " << *f1 << ", f2: " << *f2 << endl;

    // int limit = 5;
    // int num_times_called = 0;
    // // lambda function.
    // // in the capture group you can pass both values and references.
    // auto isLessThanLimit = [limit, &num_times_called](auto val) -> bool {
    //     ++num_times_called;
    //     return val < limit;
    // };
    // cout << countOccurences(v.begin(), v.end(), isLessThanLimit) << endl;
    // cout << "call the predicate " << num_times_called << " times." << endl;

    // 上面的countOccurences还有一种解决方案，就是使用std::bind()，
    // it takes a functor and returns a functor. For example, there yoo can use
    // "std::bind(islessThanLimit, _1, limit)"来解决.

    // the following data is only invented by me.
    vector<Course> courses{{"cs61a", 2352}, {"cs61b", 2248}, {"cs61c", 792}, {"MIT6.NULL", 100},
        {"cs106L", 65}, {"cs70", 238}};
    
    size_t size = courses.size();
    auto compareRating = [](const auto& c1, const auto& c2) {
        return c1.rating < c2.rating;
    };

    // sort(courses.begin(), courses.end(), compareRating);
    // Course median = courses[size / 2];

    // cout << "the course is " << median.name << ", and its rating is " << median.rating << endl;

    // 其实就是找到第k小元素，此算法利用了快速排序的思想，不过是部分排序
    // ppt这里有点问题，nth_element返回值应该是void.
    nth_element(courses.begin(), courses.begin() + size / 2, courses.end(), compareRating);
    cout << "the median is " << courses[size / 2].name << " and its rating is " << courses[size / 2].rating << endl;

    string dep = "cs";
    auto isDep = [dep](const auto& course) {
        return course.name.size() >= dep.size() && course.name.substr(0, dep.size()) == dep;
    };
    // auto iter = stable_partition(courses.begin(), courses.end(), isDep);

    // printCourses(courses);
    // cout << "the iter point to " << (*iter).name << ", its rating is " << (*iter).rating << endl;

    vector<Course> csCourses;
    // use back_inserter to dynamically add elements and don't need to verify the length from before.
    copy_if(courses.begin(), courses.end(), back_inserter(csCourses), isDep);
    printCourses(csCourses);


    return 0;
}