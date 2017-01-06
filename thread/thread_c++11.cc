/*********************************************************************
 * Thread C++11
 * @Filename: thread_c++11.cc
 * @Create:         Jack Lee@2017.01.04
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2017.01.06
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2017 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#include <iostream>
#include <thread>
#include <string>
#include <vector>


class thread_guard {
public:
    thread_guard() noexcept = default;
    thread_guard(thread_guard&) = delete;
    thread_guard(const thread_guard&) = delete;
    thread_guard(thread_guard&& t_g) noexcept { t_.swap(t_g()); }
    thread_guard(std::thread&) = delete;
    thread_guard(const std::thread&) = delete;
    thread_guard(std::thread&& t) noexcept { t_.swap(t); }

    ~thread_guard() {
        if (t_.joinable()) {
            t_.join();
        }
    }

    std::thread& operator()() { return t_; }
    thread_guard& operator=(const thread_guard&) = delete;
    thread_guard& operator=(thread_guard&& t_g) noexcept {
        if (t_.joinable()) {
            t_.join();
        }
        t_.swap(t_g());
        return *this;
    }

private:
    std::thread t_;
};


void child(std::string const& s) {
    std::cout << s << " from child thread ID " << std::hex << std::this_thread::get_id() << std::endl;
}


// g++ -std=c++11 -pthread main.cc -o main
// g++ -std=gnu++11 -pthread main.cc -o main
int main(int argc, char* argv[]) {
    std::string common_string = "Hello World!!!";
    unsigned int core_number = std::thread::hardware_concurrency();
    unsigned int thread_number = core_number < 4 ? core_number : core_number-1;

    std::cout << "Hardware core number is " << core_number << ", thread number is " << thread_number << std::endl;

    std::vector<thread_guard> thread_guard_vec;

    std::cout << common_string << " from main  thread ID " << std::hex << std::this_thread::get_id() << std::endl;

    for (int i = 0; i < thread_number; i++) {
        thread_guard_vec.push_back(thread_guard(std::thread(child, std::ref(common_string))));
    }
}

