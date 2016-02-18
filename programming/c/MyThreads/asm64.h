#ifndef MY_64_BIT_ASSEMBLERCODE
#define MY_64_BIT_ASSEMBLERCODE

#define SAVE_REGS()     asm volatile (        \
                        "   PUSH %rax   \n\t" \
                        "   PUSH %rcx   \n\t" \
                        "   PUSH %rdx   \n\t" \
                        "   PUSH %rbx   \n\t" \
                        "   PUSH %rsp   \n\t" \
                        "   PUSH %rbp   \n\t" \
                        "   PUSH %rsi   \n\t" \
                        "   PUSH %rdi   \n\t" \
                        "   PUSH %r8    \n\t" \
                        "   PUSH %r9    \n\t" \
                        "   PUSH %r10   \n\t" \
                        "   PUSH %r11   \n\t" \
                        "   PUSH %r12   \n\t" \
                        "   PUSH %r13   \n\t" \
                        "   PUSH %r14   \n\t" \
                        "   PUSH %r15   \n\t" \
                        "   PUSHFQ   ")

#define RESTORE_REGS()  asm volatile (        \
                        "   POPFQ       \n\t" \
                        "   POP %r15    \n\t" \
                        "   POP %r14    \n\t" \
                        "   POP %r13    \n\t" \
                        "   POP %r12    \n\t" \
                        "   POP %r11    \n\t" \
                        "   POP %r10    \n\t" \
                        "   POP %r9     \n\t" \
                        "   POP %r8     \n\t" \
                        "   POP %rdi    \n\t" \
                        "   POP %rsi    \n\t" \
                        "   POP %rbp    \n\t" \
                        "   POP %rsp    \n\t" \
                        "   POP %rbx    \n\t" \
                        "   POP %rdx    \n\t" \
                        "   POP %rcx    \n\t" \
                        "   POP %rax   ")

#define SAVE_SP(VAR)    asm volatile ("  MOVQ %rsp, "#VAR"");
#define RESTORE_SP(VAR) asm volatile ("  MOVQ "#VAR", %rsp");

#endif

