# **SHA-256 IMPLEMENTATION IN XV6**  
This project explores the implementation of the SHA-256 cryptographic hash function in the xv6 operating system, targeting the RISC-V architecture. It evaluates the ease of implementation, performance, and security implications of integrating SHA-256 into three environments: kernel space, user space, and system calls. The project involves custom modifications to xv6 and extensive benchmarking to assess trade-offs.  
‎ 
## **FEATURES**  

### Multi-Environment Implementation  
- **Kernel Space**: Added custom `sha256.c` for optimized hashing.  
- **User Space**: Modified user space to include SHA-256 hashing functionality.  
- **System Calls**: Integrated a custom `hash256` system call for user-kernel interaction.  

### Comprehensive Benchmarking  
- Compared performance in kernel space, user space, and via system calls.  
- Analyzed hash computation times for strings and large files.  

### Security Considerations  
- Kernel space ensures secure and efficient hashing.  
- User space offers ease of development with controlled risks.  
- System calls provide controlled access to kernel functionality while balancing security.    
‎ 
## **TECHNICAL DETAILS**  

### Implementation Highlights  
- **Kernel Space**: Encapsulated logic for message padding, scheduling, and compression loop in `sha256.c`.  
- **User Space**: Demonstrated functionality with a custom `hello.c` program using the `hash256` system call.  
- **System Call**: Implemented `sys_hash256` to compute hashes securely and efficiently.  

### Performance Benchmarking  
- **Kernel Space**: Fastest due to optimized algorithms and no context switching.  
- **User Space**: Moderate performance with some overhead.  
- **System Call**: Slowest due to user-kernel boundary crossings.  

### Development Environment  
- **Tools**: GCC cross-compiler, QEMU, and GDB for RISC-V.  
- **Setup**: Customized xv6 kernel and user space.    
‎ 
## **CODE STRUCTURE**  

### Key Files  
- **`sha256.c` & `sha256.h`**: Core SHA-256 logic for kernel and user space.  
- **`hello.c`**: Demonstrates SHA-256 hashing via system call in user space.  
- **`sysproc.c`**: Implements the `sys_hash256` system call.  
- **Makefiles**: Updated for kernel and user builds to include SHA-256 functionality.    
‎ 
To run the code in VS Code, run the command `wsl --install` in terminal then `make` and after that `make qemu`. Than run the program
For more help view the report attached.‎  

‎‎   



xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

### **ACKNOWLEDGMENTS**

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Marcelo Arroyo, Silas Boyd-Wickizer, Anton Burtsev,
carlclone, Ian Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed,
Asami Doi,Wenyang Duan, eyalz800, Nelson Elhage, Saar Ettinger, Alice
Ferrazzi, Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron,
Shivam Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang,
Matúš Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
Kolontsov, Austin Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu,
Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark
Morrissey, mtasm, Joel Nider, Hayato Ohhashi, OptimisticSide,
phosphagos, Harry Porter, Greg Price, RayAndrew, Jude Rich, segfault,
Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire,
Taojie, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Alissa Tung,
Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez,
Keiichi Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653,
Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.

### **ERROR REPORTS**

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

### **BUILDING AND RUNNING XV6**

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".
