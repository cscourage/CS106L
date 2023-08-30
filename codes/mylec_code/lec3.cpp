#include <vector>
#include <cstdlib>     // for rand
#include <iostream>    // for cout
#include <algorithm>   // for generate, sort, copy
#include <iterator>    // for ostream_iterator
#include <string>
#include <map>
#include <sstream>
#include <set>

using std::vector;    using std::string;    using std::set;    using std::map;
using std::cout;    using std::endl;    using std::cin;

const int kNumInts = 20;
const int ELEM_TO_FIND = 5;

void doBubbleSort(vector<int>& v) {
    for (size_t i = 0; i < v.size() - 1; i++) {
        for (size_t j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j+1]) {
                int temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}


void printVec(const vector<string>& v) {
    cout << "{";
    for (auto elem : v) {
        cout << elem << " ";
    }
    cout << "}" << endl;
}


string getLine() {
    string response;
    std::getline(cin, response);
    return response;
}


int numOccurrences(set<int>& cont, int elemToCount) {
    int counter = 0;
    set<int>::iterator iter;
    for (iter = cont.begin(); iter != cont.end(); iter++) {
        if (*iter == elemToCount) {
            counter++;
        }
    }
    return counter;
}


void mapIterator(map<int, int> m) {
    map<int, int>::iterator i = m.begin();
    map<int, int>::iterator end = m.end();
    while (i != end) {
        cout << (*i).first << " " << (*i).second << endl;
        ++i;
    }
}


void printVec(const vector<int>& vec) {
    for (auto elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}


// int main() {
//     vector<int> vec(kNumInts);
//     // Generate N random numbers
//     for (size_t i = 0; i < vec.size(); i++) {
//         vec[i] = rand();
//     }
//     // Sort the N numbers
//     doBubbleSort(vec);
//     // Print out N numbers
//     for (size_t i = 0; i < vec.size(); i++) {
//         cout << vec[i] << endl;
//     }
// }


// int main() {
//     vector<int> vec(kNumInts);
//     std::generate(vec.begin(), vec.end(), rand);
//     std::sort(vec.begin(), vec.end());
//     std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, "\n"));
// }


// int main() {
//     vector<string> names;
//     names.push_back("Anna");
//     names.push_back("Avery");
//     printVec(names);

//     // names.at(2) will inhint you errors but names[2] will not.
//     cout << names[2] << endl;
//     cout << "I arrive here!" << endl;
//     return 0;
// }


// int main() {
//     std::map<string, int> frequencyMap;

//     cout << "Enter words." << endl;
//     while (true) {
//         cout << "> ";
//         string response = getLine();
//         if (response.empty()) {
//             break;
//         }
//         std::istringstream stream(response);
//         string word;
//         while (stream >> word) {
//             //frequencyMap[word]; // automatically create an entry and default initialize it.
//             //frequencyMap.at(word);     // throw an error.
//             frequencyMap[word]++;
//         }
//     }

//     cout << "Enter words to look up." << endl;
//     while (true) {
//         cout << "> ";
//         string response = getLine();
//         if (response.empty()) {
//             break;
//         }
//         if (frequencyMap.count(response)) {
//             cout << frequencyMap[response] << " entries found." << endl;
//         } else {
//             cout << "None." << endl;
//         }
//     }

//     return  0;
// }


int main() {
    // sorting a vector
    vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6};
    printVec(vec);
    std::sort(vec.begin(), vec.end());
    printVec(vec);

    // finding an element from a set
    set<int> elems{3, 1, 4, 1, 5, 9, 2, 6, 7};
    //notice the following oneline code will cause errors because 
    //std::set is already an ordered container.
    //std::sort(elems.begin(), elems.end());
    auto testit = std::find(elems.begin(), elems.end(), ELEM_TO_FIND);
    if (testit == elems.end()) {
        cout << "Not found! :(" << endl;
    } else {
        cout << "Found: " << *testit << endl;
    }

    set<int>::iterator iter = elems.lower_bound(4);  //find smallest element >= key.
    set<int>::iterator end = elems.upper_bound(6);  //find smallest element > key.
    cout << "start: " << *iter << ", end: " << *end << endl;

    for (; iter != end; ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}