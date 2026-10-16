#include <iostream>
#include <cstdlib>
#include <omp.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <n> <threads>" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    int p = std::atoi(argv[2]);

    if (n <= 0 || p <= 0) {
        std::cout << "n and threads must be greater than zero." << std::endl;
        return 1;
    }

    int* A = new int[n];
    int* B = new int[n];
    int* C = new int[n];
    int* start_index = new int[p];
    int* end_index = new int[p];
 
    // A up counts while B down counts
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
        B[i] = n - i;
    }
    // recording the start time of the computation
    double start_time = omp_get_wtime();

    #pragma omp parallel num_threads(p)
    {
        int myid = omp_get_thread_num();
        int numthreads = omp_get_num_threads();
        // dividing the vector based on the thread ID
        int local_size = n / numthreads;

        int mystart = myid * local_size;
        int myend = mystart + local_size;

        // the last thread handles remainder
        if (myid == numthreads - 1) {
            myend = n;
        }

        // saving the range
        start_index[myid] = mystart;
        end_index[myid] = myend;

        for (int i = mystart; i < myend; i++) {
            C[i] = A[i] + B[i];
        }
    }

    double end_time = omp_get_wtime();
    std::cout << "Vector size ma boi: " << n << std::endl;
    std::cout << "Num of threads: " << p << std::endl;
   
    for (int i = 0; i < p; i++) {
        std::cout << "Thread id: " << i << " worked for indexes "
                  << start_index[i] << " to " << end_index[i] - 1
                  << std::endl;
    }

    bool correct = true;

    // verifying the output vector
    for (int i = 0; i < n; i++) {
        if (C[i] != n + 1) {
            correct = false;
        }
    }

    if (correct) {
        std::cout << "Correct output now every value in C is "
                  << n + 1 << "." << std::endl;
    } else {
        std::cout << "Output is wrong" << std::endl;
    }

    std::cout << "Running time: " << end_time - start_time
              << " s(seconds)" << std::endl;
    // releasing the array memory
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] start_index;
    delete[] end_index;

    return 0;
}
