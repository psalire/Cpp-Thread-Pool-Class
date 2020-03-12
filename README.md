
# C++ Thread Pool Class

Class to create a thread pool in C++.

## How to use

### General usage

```
void ftn(TYPE i) {
    /* Do something */
}

/* Initialize ThreadPool instance with 10 threads and function ftn */
ThreadPool<TYPE> tp(10, ftn);

/* Start all threads */
tp.start()

/* Push data to queue for threadpool to process */
tp.push_to_queue(0);
tp.push_to_queue(1);
tp.push_to_queue(2);
...

/* Join all threads in thread pool */
tp.join_pool();
```

### Example usage

See ```main_test.cc``` for example usage.
