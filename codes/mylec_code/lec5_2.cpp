/** The lec5.cpp is for lecture special members, move semantics and RAII -- smart point.
 *  @author:cscourage
 *  @url:https://github.com/cscourage/CS106L
*/

#include <iostream>
#include <utility>
#include <memory>

// this code may break the "rule of five", but it is used for demo.
class MyClass {
public:
    MyClass() { std::cout << "Default constructor" << std::endl; }
    MyClass(const MyClass&) { std::cout << "Copy constructor" << std::endl; }
    MyClass(MyClass&&) { std::cout << "Move constructor" << std::endl; }
};

int main() {
    MyClass a;
    // notice even though we later not use the a any more, but it still apply copy constructor
    // not move constructor, but the compiler don't do that. If you want to apply move
    // constructor, you should explictly specify it.
    //MyClass b = a;   // copy constructot.
    MyClass b = std::move(a);    // move constructor.

    // C++ has two main built-in smart pointers
    // C++ also has built-in smart pointer creators!
    // std::unique_ptr<MyClass> node = std::make_unique<MyClass>() or 
    // std::unique_ptr<MyClass> node = std::unique_ptr<MyClass>(new MyClass)
    // we still prefer the wrapper functions - make_shared has some performance benefits, etc.
    std::unique_ptr<MyClass> node1 = std::make_unique<MyClass>();
    std::shared_ptr<MyClass> node2 = std::make_shared<MyClass>();
    
    return 0;
}
