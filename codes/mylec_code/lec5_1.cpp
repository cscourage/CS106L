#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;    using std::endl;

class Drink {
public:
    Drink() = default;
    Drink(std::string flavor) : _flavor(flavor) {}

    virtual void make() = 0;
    virtual ~Drink() = default;
private:
    std::string _flavor;
};

class Tea : public Drink {
public:
    Tea() = default;
    Tea(std::string flavor) : Drink(flavor) {}
    ~Tea() = default;

    void make() {
        cout << "Made tea from the Tea class!" << endl;
    }
};

int main() {
    Tea t("red");
    t.make();

    int a = static_cast<int>(3.5);
    cout << a << endl;

    

    return 0;
}

// int main() {
//     std::vector<int> source = {1, 2, 3, 4, 5};
//     std::vector<int> destination(5);

//     std::copy_backward(source.begin(), source.end(), destination.end());

//     std::cout << "Source Vector: ";
//     for (const auto& element : source) {
//         std::cout << element << " ";
//     }

//     std::cout << "\nDestination Vector: ";
//     for (const auto& element : destination) {
//         std::cout << element << " ";
//     }

//     return 0;
// }