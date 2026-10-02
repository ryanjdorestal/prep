// CSCI 375 Project 1: Producer and Consumer with a bounded buffer.

//libraries 
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

// The number of threads is fixed at 2
const int num_threads = 2;

// circular buffer of ints 
int bufferSize = 0;
int* buffer = nullptr;

// next slot to fill (Producer)
int in = 0;

// next slot to empty (Consumer)
int out = 0;  

// shared counter of items  in the buffer.
// the threads changing it is the data race 
int count = 0;

void* producer(void* param) {
    const int counterLimit = *(int*)param;

    for (int counter = 0; counter < counterLimit; counter++) {
       
        const int next_produced = std::rand() % 100;

        if (count == bufferSize) {
            std::printf("Producer: buffer is full (%d of %d slots used), waiting on consumer\n",
                        bufferSize, bufferSize);
        }
        while (count == bufferSize)
           ; 

        buffer[in] = next_produced;
        std::printf("[P #%d] produced %d -> slot %d\n", counter + 1, next_produced, in);

        in = (in + 1) % bufferSize;

        count++;
    }
    return nullptr;
}

void* consumer(void* param) {
    const int counterLimit = *(int*)param;

    for (int counter = 0; counter < counterLimit; ++counter) {
        while (count == 0)
            ;  // nothing to consume, so do nothing 

        const int next_consumed = buffer[out];
        std::printf("\t\t\t\tConsumer: took %2d from slot %d\n", next_consumed, out);


        out = (out + 1) % bufferSize;

        count--;
    }
    return nullptr;
}



//testing the producer and consumer threads
int main(int argc, char* argv[]) {
    int counterLimit = 0;
    if (argc != 3) {
        std::fprintf(stderr, "Usage: %s <buffer_size> <counter_limit>\n", argv[0]);
        return EXIT_FAILURE;
    }
    bufferSize = atoi(argv[1]);
    counterLimit = atoi(argv[2]);
    if (bufferSize <= 0 || counterLimit <= 0) { fprintf(stderr, "Both numbers must be positive\n"); return -1; }

    buffer = new int[bufferSize];
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::printf("Buffer size: %d, counter limit: %d\n\n", bufferSize, counterLimit);

    pthread_t threads[num_threads];
    if (pthread_create(&threads[0], nullptr, producer, &counterLimit) != 0) {
        std::fprintf(stderr, "Failed to create the producer thread.\n");
        return EXIT_FAILURE;
    }
    if (pthread_create(&threads[1], nullptr, consumer, &counterLimit) != 0) {
        std::fprintf(stderr, "Failed to create the consumer thread.\n");
        return EXIT_FAILURE;
    }

    for (pthread_t thread : threads) {
        pthread_join(thread, nullptr);
    }

    std::printf("\nBoth threads joined: %d items have been produced and consumed.\n", counterLimit);

    delete[] buffer;
    return EXIT_SUCCESS;
}