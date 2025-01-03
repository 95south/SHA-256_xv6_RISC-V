#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sha256.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"

#define CHUNK_SIZE 3000

uint64
sys_rtime(void) {
  return r_time();
}

uint64
sys_fileHash256(void) {
    uint64 out_addr;
    char file_path[MAXPATH];

    if (argstr(0, file_path, MAXPATH) < 0) {
        printf("Error: Invalid file path argument.\n");
        return -1;
    }

    argaddr(1, &out_addr);

    struct inode *ip = namei(file_path);
    if (ip == 0) {
        printf("Failed to find file: %s\n", file_path);
        return -3;
    }

    ilock(ip);
    if (ip->type != T_FILE) {
        iunlockput(ip);
        printf("Not a regular file.\n");
        return -4;
    }

    // Allocate kernel memory for the buffer
    char *kernel_buffer = kalloc();
    if (kernel_buffer == 0) {
        iunlockput(ip);
        printf("Failed to allocate buffer.\n");
        return -5;
    }

    // Read directly from inode instead of using fileread
    int bytes_read = 0;
    int total_read = 0;
    struct sha256 sha;
    sha256_init(&sha);

    while (total_read < ip->size) {
        bytes_read = readi(ip, 0, (uint64)kernel_buffer, total_read, PGSIZE);
        if (bytes_read <= 0) {
            break;
        }
        sha256_append(&sha, (unsigned char *)kernel_buffer, bytes_read);
        total_read += bytes_read;
    }

    iunlock(ip);
    iput(ip);  // Release the inode

    if (bytes_read < 0) {
        printf("Error reading file: %s\n", file_path);
        kfree(kernel_buffer);
        return -7;
    }

    // Free the kernel buffer
    kfree(kernel_buffer);

    char final_hash_hex[SHA256_HEX_SIZE + 1];
    sha256_finalize_hex(&sha, final_hash_hex);

    if (copyout(myproc()->pagetable, out_addr, (char *)final_hash_hex, SHA256_HEX_SIZE) < 0) {
        printf("Error copying hash to user space.\n");
        return -8;
    }

    return 0;
}

uint64
sys_hash256(void)
{
    uint64 out_addr;
    int len;
    char *input;
    char hash[SHA256_HEX_SIZE];
    uint64 offset = 0;

    // Fetch arguments
    argint(2, &len);
    argaddr(1, &out_addr);

    // Allocate space for input
    input = kalloc();
    if (!input)
        return -1;

    // Initialize SHA-256 context
    struct sha256 sha;
    sha256_init(&sha);

    #define CHUNK_SIZE 3000  // Safe chunk size for memory

    // Handle data in chunks
    while (offset < len) {
        // Calculate chunk size
        int chunk_len = (len - offset < CHUNK_SIZE) ? (len - offset) : CHUNK_SIZE;

        uint64 addr;
        argaddr(0, &addr);

        // Copy current chunk from user space
        if (copyin(myproc()->pagetable, input, addr + offset, chunk_len) < 0) {
            kfree(input);
            return -1;
        }

        // Append chunk to hash computation
        sha256_append(&sha, input, chunk_len);

        // Advance offset
        offset += chunk_len;
    }

    // Finalize the hash
    sha256_finalize_hex(&sha, hash);

    // Free the input buffer
    kfree(input);

    // Copy the resulting hash to user space
    if (copyout(myproc()->pagetable, out_addr, (char *)hash, SHA256_HEX_SIZE) < 0)
        return -1;

    return 0;
}


uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_childSysCallCount(void)
{
  return myproc()->childSySCall_count;
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
