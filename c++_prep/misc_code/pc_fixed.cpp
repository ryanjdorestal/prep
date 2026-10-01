// CSCI 375 Project 1: Producer and Consumer with a bounded buffer.
// Terminal run: clang++ -std=c++17 -Wall -Wextra -O2 producer_consumer.cpp -o producer_consumer

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

// This is the fix: Theres one flag per slot,
//and the producer only sets it, the consumer only clears it.
//volatile used for re-check for wait
volatile bool* slot_full = nullptr;

void* producer(void* param) {
    const int counterLimit = *(int*)param;

    for (int counter = 0; counter < counterLimit; counter++) {
       
        const int next_produced = std::rand() % 100;

        if (slot_full[in]) {
            std::printf("Producer: buffer is full (%d of %d slots used), waiting on consumer\n",
                        bufferSize, bufferSize);
        }
        while (slot_full[in])
           ; 

        buffer[in] = next_produced;
        std::printf("[P #%d] produced %d -> slot %d\n", counter + 1, next_produced, in);

        // Mark the slot full only after the value is written and printed, so
        // the consumer can never read it early and the log stays in order.
        slot_full[in] = true;

        in = (in + 1) % bufferSize;
    }
    return nullptr;
}

void* consumer(void* param) {
    const int counterLimit = *(int*)param;

    for (int counter = 0; counter < counterLimit; ++counter) {
        while (!slot_full[out])
            ;  // do nothing -- nothing to consume

        const int next_consumed = buffer[out];
        std::printf("\t\t\t\tConsumer: took %2d from slot %d\n", next_consumed, out);

        // Mark the slot empty only after the value is read, so the producer
        // can never overwrite an item that hasn't been consumed.
        slot_full[out] = false;

        out = (out + 1) % bufferSize;
    }
    return nullptr;
}



    
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
    slot_full = new volatile bool[bufferSize]();  // () starts every slot as empty
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
    delete[] slot_full;
    return EXIT_SUCCESS;
}