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


struct Course {
    string code;
    Time start, end;
    vector<string> instructors;
};


struct Time {
    int hour, minute;
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
    //podTest()
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
    
    oss << "16.9 Ounces";
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


void podTest() {
    cout << "[" << setw(10) << "Ito" << "]" << endl;
    cout << "[" << left << setw(10) << "Ito" << "]" << endl;
    cout << "[" << left << setfill('-') << setw(10) << "Ito" << "]" << endl;
}


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


void getlineMixedWithCin() {
    istringstream iss("16.9 Ounces\n Pack of 12");
    double amount; string unit;

    iss >> amount;
    iss.ignore();
    getline(iss, unit);

    cout << "amount: " << amount << endl;
    cout << "unit: " << unit << endl;
}


void modern() {
    string str = "Hello World!";
    for (size_t i = 0; i < str.size(); i++) {
        cout << str[i] << endl;
    }
}


string chopBothEnds(const string& str) {
    string result = "";
    for (size_t i = 1; i < str.size() - 1; i++) {
        result += str[i];
    }
    return result;
}


// g++ -std=c++17 .\lec2.cpp -o lec2
void pairAndTuple() {
    auto prices = make_pair(3.4, 5);
    auto values = make_tuple(3, 4, "hi");

    prices.first = prices.second;
    get<0>(values) = get<1>(values);

    auto [a, b] = prices;
    const auto& [x, y, z] = values;

    cout << "a: " << a << ", b: " << b << endl;
    cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
}


void autoStrcutBinding() {
    auto coupon1 = Discount{0.9, 30, "New Years"};
    Discount coupon2 = Discount{0.75, 7, "Valentine’s Day"};
    coupon1.discountFactor = 0.8;
    coupon2.expirationDate = coupon1.expirationDate;
    auto [factor, date, name] = coupon1;

    cout << "factor: " << factor << ", date: " << date << ", name: " << name << endl;
}


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
    int v1 = static_cast<int>(3.4);   // explict cast.
    double v2 = 6;                       // promotion.

    const int val1 = 3;                  // promotion.
    int *val2 = const_cast<int*> (&val1);   // explict cast.

    cout << "v1: " << v1 << ", v2: " << v2 << endl;
    cout << "val1: " << val1 << ", val2: " << *val2 << endl;
}