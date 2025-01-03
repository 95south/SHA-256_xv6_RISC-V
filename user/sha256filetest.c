#define CHUNK_SIZE 3000
#include "sha256.h"

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

#include "user/user.h"
#include "results.h"

int main(int argc, char *argv[]) {

    // Check if input is provided
    if (argc < 2) {
        printf("%s\n", "Error: No input file provided.\n");
        exit(1);
    }

    char final_hash_hex[65];
    const char *file_path = argv[1];
    printf("Opening file: %s\n", file_path);
    fileHash256(file_path, final_hash_hex);

    printf("%s\n", final_hash_hex);
    
    exit(0);

}