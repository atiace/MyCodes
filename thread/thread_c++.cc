/*********************************************************************
 * Thread C++
 * @Filename: thread_c++.cc
 * @Create:         Jack Lee@2017.01.06
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2017.01.10
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2017 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#include <iostream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


class thread_guard {
public:
    thread_guard() {}

    ~thread_guard() {
        for (int i = 0; i < id_.size(); i++) {
            if (validity_[i]) {
                pthread_join(id_[i], NULL);
            }
        }
    }

    bool create_thread(void*(*start_routine)(void*), void* arg) {
        pthread_t id;
        int ret = pthread_create(&id, NULL, start_routine, arg);
        if (ret) {
            return false;
        }
        id_.push_back(id);
        validity_.push_back(true);
        return true;
    }

private:
    std::vector<pthread_t> id_;
    std::vector<bool> validity_;
};


void* child(void* arg) {
    const std::string* s = (const std::string*)arg;
    std::cout << *s << " from child (Process ID, Thread ID)(0x" << std::hex << getpid() << ", 0x" << std::hex << pthread_self() << ")" << std::endl;
    return NULL;
}


// g++ -pthread thread_c++.cc -o thread_c++
int main(int argc, char* argv[]) {
    std::string common_string = "Hello World!!!";
    unsigned int core_number = sysconf(_SC_NPROCESSORS_ONLN);
    unsigned int thread_number = core_number < 4 ? core_number : core_number-1;

    std::cout << "Hardware core number is " << core_number << ", thread number is " << thread_number << std::endl;

    std::cout << common_string << " from main  (Process ID, Thread ID)(0x" << std::hex << getpid() << ", 0x" << std::hex << pthread_self() << ")" << std::endl;

    thread_guard t_g;

    for (int i = 0; i < thread_number; i++) {
        t_g.create_thread(child, &common_string);
    }
}

