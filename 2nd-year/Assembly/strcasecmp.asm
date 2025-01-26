BITS 64
SECTION .text
GLOBAL strcasecmp
strcasecmp:
    MOV RAX, 0
    MOV R8B, 0
    MOV R9B, 0
    MOV RCX, 0

loop:
    MOV R8B, BYTE [RDI, RCX]
    MOV R9B, BYTE [RSI, RCX]
    JMP upper_to_lower_one

upper_to_lower_one:
    CMP R8B, 65
    JG upper_to_lower_two
    CMP R8B, 65
    JL upper_to_lower_one_sec

upper_to_lower_two:
    CMP R8B, 90
    JL transform_lower_one
    CMP R8B, 90
    JG upper_to_lower_one_sec

transform_lower_one:
    ADD R8B, 32
    JMP upper_to_lower_one_sec

upper_to_lower_one_sec:
    CMP R9B, 65
    JG upper_to_lower_two_sec
    CMP R9B, 65
    JL compare

upper_to_lower_two_sec:
    CMP R9B, 90
    JL transform_lower_one_sec
    CMP R9B, 90
    JG compare

transform_lower_one_sec:
    ADD R9B, 32
    JMP compare

compare:
    CMP R8B, 0x00    ; vérf si on arrive sur null
    JE .end
    CMP R9B, 0x00    ; vérf si on arrive sur null
    JE .end
    CMP R8B, R9B  ; compare les deux caractères
    JNE .end ; si c'est pas le meme, on sort
    INC RCX
    JMP loop

.end:
    MOVZX RAX, BYTE [RDI, RCX]
    MOVZX RBX, BYTE [RSI, RCX]
    SUB RAX, RBX
    RET

