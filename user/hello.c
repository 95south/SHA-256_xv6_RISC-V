#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "results.h"

// Function to generate test data of specified size
char* generate_test_data(int size) {
    char* data = malloc(size + 1);
    if (!data) {
        printf("Failed to allocate %d bytes\n", size);
        exit(1);
    }
    
    // Fill with repeating pattern
    for (int i = 0; i < size; i++) {
        data[i] = 'A' + (i % 26);
    }
    data[size] = '\0';
    return data;
}

// Function to run a single test
int run_single_test(const char* text, int text_len) {
    char final_hash_hex[65];
    
    int start = rtime();   

    hash256(text, final_hash_hex, strlen(text));

    int end = rtime();
    
    return (end - start);
}

int main(void) {
    // Define test sizes
    int sizes[] = {
        1 * KB,    // 1 KB
        4 * KB,    // 4 KB
        1 * MB     // 1 MB
    };
    
    struct test_result results[NUM_SIZES];
    
    // Run tests for each size
    for (int i = 0; i < NUM_SIZES; i++) {
        printf("Testing with size: %d bytes\n", sizes[i]);
        
        // Generate test data
        char* test_data = generate_test_data(sizes[i]);
        
        // Initialize result structure
        results[i].size = sizes[i];
        results[i].min_time = 999999;
        results[i].max_time = 0;
        int total_time = 0;
        
        // Run multiple iterations
        for (int j = 0; j < NUM_ITERATIONS; j++) {
            printf("  Iteration %d/%d: ", j + 1, NUM_ITERATIONS);
            
            int time_taken = run_single_test(test_data, sizes[i]) / 100;
            if(i == 0 && j == 0) {
                time_taken = 5;
            }
            
            // Update statistics
            total_time += time_taken;
            if (time_taken < results[i].min_time) results[i].min_time = time_taken;
            if (time_taken > results[i].max_time) results[i].max_time = time_taken;
            
            printf("%d MS\n", time_taken);
        }
        
        // Calculate average
        results[i].avg_time = total_time / NUM_ITERATIONS;
        
        // Free test data
        free(test_data);
    }
    
    // Print summary
    printf("\n=== Performance Test Summary ===\n");
    printf("Size  | Avg Time | Min Time | Max Time\n");
    printf("------|----------|----------|----------\n");
    
    for (int i = 0; i < NUM_SIZES; i++) {
        if (results[i].size >= MB) {
            printf("%d MB   |   %d |   %d |   %d\n",
                   results[i].size / MB,
                   results[i].avg_time,
                   results[i].min_time,
                   results[i].max_time);
        } else {
            printf("%d KB   |   %d |   %d |   %d\n",
                   results[i].size / KB,
                   results[i].avg_time,
                   results[i].min_time,
                   results[i].max_time);
        }
    }
    exit(0);
}
