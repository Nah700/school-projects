BITS 64
SECTION .text

GLOBAL strpbrk
strpbrk:
    MOV RCX, 0
    MOV RAX, 0

.loop
    MOV R8, 0
    MOV AL, BYTE [RDI + RCX]
    CMP AL, 0x00
    JE .return_y_a_r
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

.return_y_a_r:
    MOV RAX, 0
    RET

.end:
    LEA RAX, [RDI + RCX]
    RET
