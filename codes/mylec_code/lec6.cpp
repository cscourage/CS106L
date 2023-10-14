/** The lec6.cpp is for lecture multithreading.
 *  @author:cscourage
 *  @url:https://github.com/cscourage/CS106L
*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
/**because when installing mingw we set thread not to be posix. so in Windows we can not
 * use std::thread and std::mutex. The solution is add some header file which pulled from
 * github and place it into path:D:\mingw64\lib\gcc\x86_64-w64-mingw32\8.1.0\include\c++.
 */
// 这里的mingw.thread.h需自行在网上搜索找到对应的github仓库并将其导入到相应路径以解决问题
#include <mingw.thread.h>
#include <mingw.mutex.h>

using std::cout;    using std::endl;
using std::string;  using std::vector;

const size_t kNumThreads = 10;
std::mutex mtx;

void greet(int id) {
    std::lock_guard<std::mutex> lg(mtx);    // RAII.
    cout << "Hello there: My name is " << id << endl;
}


int main() {
    cout << "Greetings from my threads..." << endl;

    // std::thread thread1(greet, 1);
    // std::thread thread2(greet, 2);

    // thread1.join();
    // thread2.join();

    vector<std::thread> threads;
    for (size_t i = 0; i < kNumThreads; ++i) {
        threads.push_back(std::thread(greet, i));
        //can not add thread[i].join(), it will make it serial.
    }

    // 注意如果这里加上一个cout，因为这里没有互斥锁资源，所以也有race condition.
    //cout << "Hello from main threads" << endl;

    //note there needs to use & in order to prevent copying which results new creation.
    //这里是按顺序回收.
    for (std::thread& t : threads) {
        t.join();
    }

    cout << "All greetings done!" << endl;

    return 0;
}