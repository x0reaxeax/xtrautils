#ifndef _X0DEBUG_H
#define _X0DEBUG_H

#define I_NOP               0x90
#define I_TRAP              0xcc
#define I_RET               0xc3

#define I_POP_RBP           0x5d

#define ELF_ENTRY_OFFSET    0x18

#ifndef STDIN_FILENO
#define STDIN_FILENO        0
#define STDOUT_FILENO       1
#define STDERR_FILENO       2
#endif /* STDIN_FILENO */

#define ASM_NAKED           __attribute__ ((__naked__))

#define ASM_BYTES(byte, quant)          \
    do { __asm__ volatile (             \
        ".rept %c0; .byte %c1; .endr;"  \
        :: "i" (quant), "i" (byte)      \
    ); } while(0);

#define ASM_BYTE(byte)                  \
    ASM_BYTES(byte, 1)

#define ASM_NOP(quant)                  \
    ASM_BYTES(I_NOP, quant)

#define ASM_TRAP                        \
    do {                                \
        __asm__ volatile ("int3;");     \
    } while (0);

#ifndef DBG_BREAKPOINT
#define DBG_BREAKPOINT      ASM_TRAP
#endif /* DBG_BREAKPOINT */

#define ASM_INTEL_SYNTAX                \
    do {                                \
        __asm__ volatile (              \
            ".intel_syntax noprefix;"   \
        );                              \
    } while(0);
    
#define ASM_ATT_SYNTAX                  \
    do {                                \
        __asm__ volatile (              \
            ".att_syntax;"              \
        );                              \
    } while(0);

int ASM_NAKED __dbg_arg_preload (void *rdi, void *rsi, void *rdx,
                                 void *rcx, void *r8,  void *r9)
{
    __asm__ volatile ("ret;");
}

int ASM_NAKED __dbg_print(unsigned int fd, const char *buf, unsigned long len)
{
    ASM_INTEL_SYNTAX;
    __asm__ volatile (
        "push 1;"
        "pop rax;"
        "syscall;"
        "ret;"
        ::: "rax"
    );
    ASM_ATT_SYNTAX;
}

#endif
