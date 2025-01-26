BITS 64
SECTION .text
GLOBAL strncmp
strncmp:
    MOV RAX, 0
    MOV R8B, 0
    MOV RCX, 0
loop:
    MOV R8B, [RDI + RCX]
    CMP BYTE [RDI + RCX], 0x00    ; vérf si on arrive sur null
    JE .end
    CMP BYTE [RSI + RCX], 0x00    ; vérf si on arrive sur null
    JE .end
    CMP R8B, BYTE [RSI + RCX]  ; compare les deux caractères
    JNE .end ; si c'est pas le meme, on sort

    INC RCX

    CMP RDX, RCX
    JE .end_by_length
    JMP loop

.end_by_length:
    DEC RCX
    JMP .end

.end:
    MOVZX RAX, BYTE [RDI, RCX]
    MOVZX RBX, BYTE [RSI, RCX]
    SUB RAX, RBX
    RET