#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "sha256.h"

volatile static int started = 0;

// start() jumps here in supervisor mode on all CPUs.
void sha256_test();
void
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\n");
    printf("xv6 kernel is booting\n");
    printf("\n");
    kinit();         // physical page allocator
    kvminit();       // create kernel page table
    kvminithart();   // turn on paging
    procinit();      // process table
    trapinit();      // trap vectors
    trapinithart();  // install kernel trap vector
    plicinit();      // set up interrupt controller
    plicinithart();  // ask PLIC for device interrupts
    binit();         // buffer cache
    iinit();         // inode table
    fileinit();      // file table
    virtio_disk_init(); // emulated hard disk
    userinit();      // first user process

    sha256_test();

    __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
      ;
    __sync_synchronize();
    printf("hart %d starting\n", cpuid());
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }

  scheduler();        
}

void sha256_test() {
  const char *text = "Hello, World!";

    /* Char array to store the hexadecimal SHA-256 string. */
    /* Must be 65 characters big (or larger). */
    /* The last character will be the null-character. */
    char hex[SHA256_HEX_SIZE];

    /* Compute SHA-256 sum. */
    sha256_hex(text, strlen(text), hex);

    /* Print result. */
    printf("The SHA-256 sum of \"%s\" is:\n\n", text);
    printf("%s\n\n", hex);
}
