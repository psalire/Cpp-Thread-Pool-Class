
#include "thread_pool.h"

void sleep_test(int i);
void fast_test(std::string s);

/* Construct thread pools globally for convenience */
ThreadPool<int> t_1(10, sleep_test);
ThreadPool<std::string> t_2(20, fast_test);

/* Sleep for 1-3 seconds */
void sleep_test([[maybe_unused]] int i) {
    int time = rand()%3+1;
    #ifdef PRINT_DEBUG
    t_1.safe_print("Sleeping for " + std::to_string(time) + " sec...");
    #endif
    std::this_thread::sleep_for(std::chrono::seconds(time));
}
/* Print a string */
void fast_test(std::string s) {
    #ifdef PRINT_DEBUG
    t_2.safe_print("Got: \"" + s + "\"", 0);
    #endif
}

/* Test 3 different thread pools */
int main() {
    std::cout << "Test 1...\n";
    /* Start thread pool */
    t_1.start();
    /* Push values to queue, wait 1-2 seconds between each push */
    /* Thread pool automatically starts processing as pushed to queue */
    for (int i = 0; i < 22; i++) {
        t_1.push_to_queue(i);
        #ifdef PRINT_DEBUG
        t_1.safe_print("Pushed val " + std::to_string(i), 0);
        #endif
        std::this_thread::sleep_for(std::chrono::seconds(rand()%2+1));
    }
    /* Join all threads in thread pool */
    t_1.join_pool();

    std::cout << "\n\n--------------------------------\n\n";

    /******************************************/
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Test 2...\n";
    /* Start thread pool */
    t_2.start();
    /* Push random strings to queue */
    /* Thread pool automatically starts processing as pushed to queue */
    for (int i = 0; i < 300; i++) {
        /* Generate random string */
        int rand_len = rand()%6+1;
        std::string s;
        for (int j = 0; j < rand_len; j++) {
            s += (char) (65 + (rand() % 58));
        }
        t_2.push_to_queue(s);
        #ifdef PRINT_DEBUG
        t_2.safe_print("Pushed val " + s, 0);
        #endif
    }
    /* Join all threads in thread pool */
    t_2.join_pool();
    std::cout << "\n\n--------------------------------\n\n";

    /******************************************/

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Test 3...\n";
    /* Test with lambda and start after queue is filled */
    ThreadPool<char> t_3(15, [&](char c) {
        #ifdef PRINT_DEBUG
        t_3.safe_print(std::to_string((char)c));
        #endif
    });
    /* Push random chars to queue */
    /* Thread pool automatically starts processing as pushed to queue */
    for (int i = 0; i < 300; i++) {
        /* Generate random char */
       t_3.push_to_queue((char) 33 + (rand()%93));
    }
    /* Start after pushing to queue */
    t_3.start();
    t_3.join_pool();

    return 0;
}
