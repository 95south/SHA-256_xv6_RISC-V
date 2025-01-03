#define KB (1024)
#define MB 10 * (1024 * KB)
#define NUM_ITERATIONS 10  // Number of times to run each test for averaging
#define NUM_SIZES 3    

// Structure to hold test results
struct test_result {
    int size;
    int avg_time;
    int min_time;
    int max_time;
};