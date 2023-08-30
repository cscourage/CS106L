/** Note: for simplicity, we've removed the iterator class, and instead
 * used a simple pointer. For the GapBuffer, the iterator class needs to be implemented!
 */

#include <iostream>
#include <algorithm>
#include <string>

using std::cout;    using std::endl;

template <typename T>
class MyVector {
public:
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = value_type*;
    using size_type = size_t;

    const size_type kInitialSize = 10;
    MyVector() noexcept;    // default construction.
    MyVector(size_type n, const value_type& val) noexcept;
    MyVector(const MyVector<T>& other) noexcept;    //copy construction
    MyVector<T>& operator=(const MyVector<T>& rhs) noexcept;   // copy assignment
    MyVector(MyVector<T>&& other) noexcept;     // move construction
    MyVector<T>& operator=(MyVector<T>&& rhs) noexcept;     // move assignment
    ~MyVector() noexcept;   // destruction.

    size_type size() const;
    bool empty() const;

    value_type& operator[](size_type index);
    const value_type& operator[](size_type index) const;
    value_type& at(size_type index);

    iterator insert(iterator pos, const value_type& elem);
    void push_back(const value_type& elem);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
private:
    void resize();
    value_type* elems;
    size_type logicalSize;
    size_type allocatedSize;
};


template <typename T>
MyVector<T>::MyVector() noexcept : 
    logicalSize(0), allocatedSize(kInitialSize) 
{
    cout << "Hello from the default constructor!" << endl;
    elems = new value_type[allocatedSize];
}

template <typename T>
MyVector<T>::MyVector(size_type n, const value_type& val) noexcept :
    logicalSize(0), allocatedSize(2*n)
{
    cout << "Hello from the fill construction!" << endl;
    elems = new value_type[allocatedSize];
    std::fill(begin(), end(), val);
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other) noexcept :
    logicalSize(other.logicalSize), allocatedSize(other.allocatedSize)
{
    cout << "Hello from the copy construction!" << endl;
    elems = new value_type[allocatedSize];
    std::copy(other.begin(), other.end(), begin());
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& rhs) noexcept {
    cout << "Hello from the copy assignment operator!" << endl;
    if (this != &rhs) {
        delete[] elems;
        logicalSize = rhs.logicalSize;
        allocatedSize = rhs.allocatedSize;
        elems = new value_type[allocatedSize];
        std::copy(rhs.begin(), rhs.end(), begin());
    }
    return *this;
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept :
    elems(std::move(other.elems)),
    logicalSize(std::move(other.logicalSize)),
    allocatedSize(std::move(other.allocatedSize))
{
    cout << "Hello from the move construction!" << endl;
    other.elems = nullptr;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& rhs) noexcept {
    cout << "Hello from the move assignment!" << endl;
    if (this != &rhs) {
        delete[] elems;
        logicalSize = std::move(rhs.logicalSize);
        allocatedSize = std::move(rhs.allocatedSize);
        elems = std::move(rhs.elems);
        rhs.elems = nullptr;
    }
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() noexcept {
    cout << "Hello from the destructor!" << endl;
    delete[] elems;
}

template <typename T>
typename MyVector<T>::size_type MyVector<T>::size() const {
    return logicalSize;
}

template <typename T>
bool MyVector<T>::empty() const {
    return size() == 0;
}

template <typename T>
typename MyVector<T>::value_type& MyVector<T>::operator[](size_type index) {
    return *(begin() + index);
}

template <typename T>
const typename MyVector<T>::value_type& MyVector<T>::operator[](size_type index) const {
    return *(begin() + index);
}

template <typename T>
typename MyVector<T>::value_type& MyVector<T>::at(size_type index) {
    if (index >= size) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    return elems;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::begin() const {
    return elems;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    return elems + size();
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::end() const {
    return elems + size();
}

template <typename T>
void MyVector<T>::resize() {
    iterator new_elems = new value_type[2*allocatedSize];
    std::copy(begin(), end(), new_elems);
    delete[] elems;
    allocatedSize *= 2;
    elems = new_elems;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(iterator pos, const value_type& elem) {
    size_type index = pos - begin();
    if (size() == allocatedSize) {
        resize();
    }
    pos = begin() + index;
    std::copy_backward(pos, end(), end() + 1);
    *pos = elem;
    ++logicalSize;
    return pos;
}

template <typename T>
void MyVector<T>::push_back(const value_type& elem) {
    insert(end(), elem);
}