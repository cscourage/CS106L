/** The lec2.cpp is for lecture streams and types.
 *  @author:cscourage
 *  @url:https://github.com/cscourage/CS106L
*/

#include <iostream>  // for cin,cout
#include <sstream>   // for stringstream
#include <iomanip>   // for manipulators
#include <utility>   // for pair/tuple
#include <vector>    // for vector
using std::ostringstream, std::istringstream, std::istream, std::ostream;
using std::cout, std::cin, std::endl, std::flush, std::string;
using std::left, std::setw, std::setfill;
using std::make_pair, std::make_tuple, std::get;
using std::vector;


struct Discount {
    double discountFactor;
    int expirationDate;
    string nameOfDiscount;
};

struct Time {
    int hour, minute;
};

struct Course {
    string code;
    Time start, end;
    vector<string> instructors;
};



void odemo();
void idemo();
int stringToInteger(const string& str);
void stringToIntegerTest();
void printStateBits(const istream& iss);
void bufferedExperiment(ostream &oss);
int mindlessWork();
void podTest();
void badWelcomeProgram();
int getInteger(const string& prompt);
void getlineMixedWithCin();
void modern();
string chopBothEnds(const string& str);
void pairAndTuple();
void autoStrcutBinding();
void referencesDemo();
void conversionDemo();


int main() {
    //odemo();
    //idemo();
    //stringToIntegerTest();
    //bufferedExperiment(cout);
    //podTest();
    //badWelcomeProgram();
    //getlineMixedWithCin();
    //modern();
    //cout << chopBothEnds("") << endl; // a bug.
    //pairAndTuple();
    //autoStrcutBinding();
    //referencesDemo();
    //conversionDemo();
    // the above are Uniform initialization
    vector<int> vec{3, 1, 4, 1, 5, 9};
    Course now {"CS106L", {13, 30}, {14, 30}, {"Wang", "Zeng"} };
    
    return 0;
}


void odemo() {
    ostringstream oss("Ito-En Green Tea", ostringstream::ate);
    cout << oss.str() << endl;
    
    oss << 16.9 << " Ounce ";
    cout << oss.str() << endl;
}


void idemo() {
    istringstream iss("16.9 Ounces");

    int amount;
    string unit;

    iss >> amount;
    iss >> unit;

    cout << amount << " || " << unit << endl;
}


int stringToInteger(const string& str) {
    istringstream iss(str);

    int result; char remain;
    if (!(iss >> result) || iss >> remain) {
        throw std::domain_error("error!");
    }

    return result;
}


void stringToIntegerTest() {
    while (true) {
        cout << "Type in an integer: ";
        string s;
        if (!getline(cin, s)) throw std::domain_error("getline failed");
        cout << "You type in: " << s << "\n";
        int result = stringToInteger(s);
        cout << "As an integer, this is: " << result << "\n";
    }
}


void printStateBits(const istream& iss) {
    cout << "State bits: ";
    
    cout << (iss.good() ? "G" : "-");
    cout << (iss.fail() ? "F" : "-");
    cout << (iss.eof() ? "E" : "-");
    cout << (iss.bad() ? "B" : "-");
    cout << '\n';
}


// 这一段代码的效果不是特别显著，至少在我的电脑上跑没有展现出buffered的效果.
void bufferedExperiment(ostream &oss) {
    oss << "CS";
    mindlessWork();
    oss << "106";
    mindlessWork();
    oss << flush;
    mindlessWork();
    oss << "L";
    mindlessWork();
    oss << endl;
}


int mindlessWork() {
    double sum = 0;
    for (int i = 0; i < 400000000; i++) {
        sum += i / 999959;
    }
    return sum;
}


// manipulators示例
void podTest() {
    cout << "[" << setw(10) << "Ito" << "]" << endl;
    cout << "[" << left << setw(10) << "Ito" << "]" << endl;
    cout << "[" << left << setfill('-') << setw(10) << "Ito" << "]" << endl;
}


// 注释之前是badwelcome，注释之后已经是good了.
void badWelcomeProgram() {
    string name, response;
    int age;

    cout << "What's your name? ";
    //cin >> name;
    getline(cin, name);

    //cout << "What's your age? ";
    //cin >> age;
    age = getInteger("What's your age? ");
    
    cout << "Hello " << name << " (age " << age << ")" << "\n";

    cout << "Do you want to try again? ";
    //cin >> response;
    getline(cin, response);

    cout << "You said: " << response << endl;
}


int getInteger(const string& prompt) {
    while (true) {
        cout << prompt;
        string line; int result; char trash;
        // 使用getline是为了将用户的输入准确无误的放到line中，而不会截断，同时方便错误检查.
        if (!getline(cin, line)) {
            throw std::domain_error("something error.");
        }
        istringstream iss(line);
        if (iss >> result && !(iss >> trash)) {
            return result;
        }
        cout << "error, again." << endl;
    }
}


// 这个代码主要是展示getline和 >> 混用时会发生情况
// lecture的ppt上有错误，不加ignore应该是" Ounces"而不是"".
void getlineMixedWithCin() {
    istringstream iss("16.9 Ounces\n Pack of 12");
    double amount; string unit;

    iss >> amount;
    iss.ignore();
    getline(iss, unit);

    cout << "amount: " << amount << endl;
    cout << "unit: " << unit << endl;
}


// 这里注意for循环时要将i的类型定为size_t，因为str.size()返回的是size_t类型，
// 如果i为int，则会变成有符号数和无符号数比较，由csapp知道这个有时是会有些问题的
void modern() {
    string str = "Hello World!";
    for (size_t i = 0; i < str.size(); i++) {
        cout << str[i] << endl;
    }
}


// 这里主要是说当str为空时，str.size() - 1会变成无符号最大值，同时c++中string[]不会做越界检查.
string chopBothEnds(const string& str) {
    string result = "";
    for (size_t i = 1; i < str.size() - 1; i++) {
        result += str[i];
    }
    return result;
}


// auto是c++11之后引入的新特性.
// use in iterators, templates, lambdas but not return types(as it is not clear).
auto calculateSum(const vector<string>& v) {
    auto mul = 2.4;   // double
    auto name = "Avery";   // c-string
    auto betterName1 = string{"Avery"};  // c++-string
    const auto& betterName2 = string{"Avery"};   //const string&
    auto copy = v;   // vector<string>, because auto discards const and references.
    auto& ref = mul;  // double&
    auto func = [](auto i){return i * 2;};  // lambda function.

    return betterName1;
}


// g++ -std=c++17 .\lec2.cpp -o lec2
void pairAndTuple() {
    // make_pair/tuple (C++11) automatically deduces the type!
    auto prices = make_pair(3.4, 5);  // pair<double, int>
    auto values = make_tuple(3, 4, "hi");  //tuple<int, int, const char*>

    prices.first = prices.second;    // prices = {5.0, 5}
    get<0>(values) = get<1>(values);  // values = {4, 4, "hi"}

    // structured binding (C++17) – extract each component
    auto [a, b] = prices;
    const auto& [x, y, z] = values;

    cout << "a: " << a << ", b: " << b << endl;
    cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
}


void autoStrcutBinding() {
    auto coupon1 = Discount{0.9, 30, "New Years"};
    Discount coupon2 = {0.75, 7, "Valentine’s Day"};
    coupon1.discountFactor = 0.8;
    coupon2.expirationDate = coupon1.expirationDate;
    auto [factor, date, name] = coupon1;

    cout << "factor: " << factor << ", date: " << date << ", name: " << name << endl;
}


// lecture的ppt中的这段代码输出最后一行有问题，以下面这段程序跑出的结果为准.
void referencesDemo() {
    string tea = "Ito-En";
    string copy = tea;
    string& ref = tea;

    // note: the string operator [] returns a reference to a char in string
    tea[1] = 'a';
    cout << "tea: " << tea << endl;
    copy[2] = 'b';
    cout << "tea: " << tea << endl;
    ref[3] = 'c';
    cout << "tea: " << tea << endl;

    char letterCopy = tea[4];
    char& letterRef = tea[5];
    
    letterCopy = 'd';
    cout << "tea: " << tea << endl;
    letterRef = 'e';
    cout << "tea: " << tea << endl;
    ref = copy;
    cout << "tea: " << tea << endl;
}


void conversionDemo() {
    int v1 = static_cast<int>(3.4);   // explict cast. ppt上写错了，以这里的为主.
    double v2 = 6;                       // promotion.

    const int val1 = 3;                  // promotion.
    int *val2 = const_cast<int*> (&val1);   // explict cast.

    cout << "v1: " << v1 << ", v2: " << v2 << endl;
    cout << "val1: " << val1 << ", val2: " << *val2 << endl;
}