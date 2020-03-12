
#include "thread_pool.h"

void sleep_test(int i);
void fast_test(std::string s);
ThreadPool<int> t_1(10, sleep_test);
ThreadPool<std::string> t_2(20, fast_test);

/* Sleep for 1-3 seconds */
void sleep_test(int i) {
    int time = rand()%3+1;
    t_1.safe_print("Sleeping for " + std::to_string(time) + " sec...", 0);
    std::this_thread::sleep_for(std::chrono::seconds(time));
}
/* Print a string */
void fast_test(std::string s) {
    t_1.safe_print("Got: \"" + s + "\"", 0);
}

int main(int argc, char **argv) {
    /* Start thread pool */
    t_1.start();
    /* Push values to queue, wait 1-2 seconds between each push */
    /* Thread pool automatically starts processing as pushed to queue */
    for (int i = 0; i < 44; i++) {
        t_1.push_to_queue(i);
        t_1.safe_print("Pushed val " + std::to_string(i), 0);
        std::this_thread::sleep_for(std::chrono::seconds(rand()%2+1));
    }
    /* Join all threads in thread pool */
    t_1.join_pool();

    std::cout << "\n\n--------------------------------\n\n";

    /******************************************/
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
        t_2.safe_print("Pushed val " + s, 0);
    }
    /* Join all threads in thread pool */
    t_2.join_pool();

    return 0;
}
