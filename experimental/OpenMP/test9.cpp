#include <iostream>
#include <omp.h>

int main() {
    int max_threads = omp_get_max_threads();

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        #pragma omp single
        {
            std::cout << "Max number of threads: " << max_threads << std::endl;
        }
        #pragma omp critical
        {
            std::cout << "Hello from thread " << thread_id << std::endl;
        }
    }

    return 0;
}

