BITS 64
SECTION .text

GLOBAL strcspn
strcspn:
    MOV RCX, 0
    MOV RAX, 0

.loop
    MOV R8, 0
    MOV AL, BYTE [RDI + RCX]
    CMP AL, 0x00
    JE .end
    JMP .loop_sec

.loop_sec:
    MOV DL, BYTE [RSI + R8]
    CMP DL, 0x00
    JE .next_inc
    CMP AL, DL
    JE .end
    INC R8
    JMP .loop_sec

.next_inc:
    INC RCX
    JMP .loop

.end:
    MOV RAX, RCX
    RET
