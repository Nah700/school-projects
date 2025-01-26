BITS 64
SECTION .text
GLOBAL memset
memset:
    MOV RCX, 0
    MOV RAX, RDI    ; on fait une copie de RDI

loop:
    CMP RDX, RCX    ; on vérifie si l'inex ou nous sommes est égal au nombre d'index qu'on doit changer
    JE .end         ; si RCX == RDX, on sort de la boucle
    MOV BYTE [RDI + RCX], SIL  ; on remplace la valeur
    INC RCX
    JMP loop

.end:
    RET