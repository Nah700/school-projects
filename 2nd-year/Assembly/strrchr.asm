BITS 64
SECTION .text
GLOBAL strrchr
strrchr:

    MOV RCX, 0
    MOV RAX, 0

loop:
    CMP BYTE [RDI + RCX], SIL       ; [RDI + RCX] -> str[i]
    JE found    ; if caractère trouvé:
    JMP is_end ; else carcatère non trouvé:
found:
    LEA RAX, [RDI, RCX] ; on met la valeur trouvé dans RAX;
    JMP is_end

is_end:
    CMP	BYTE [RDI + RCX], 0x00 ; verifie si on est à la fin
    JE .end
    INC RCX
    JMP loop

.end:
    RET






