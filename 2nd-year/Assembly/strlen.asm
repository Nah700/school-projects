BITS 64
SECTION .text
GLOBAL strlen
strlen:
        PUSH RBP
        MOV RBP, RSP
;{
    ; init variable
    MOV RAX, 0
loop:
    CMP BYTE [RDI + RAX], 0; compare RDI + RAX à 0 RAX est l'index de la chaine et RDI est le pointeur de la chaine CMP permet de comparer
    JE end ; si c'est égale à 0, on sort de la loop
;    if (str[len] == 0)
;        goto end
;    len++
     INC RAX; incrémente RAX
     JMP loop
;    goto loop;
end:
;    return len
;}
        MOV RSP, RBP
        POP RBP
        RET