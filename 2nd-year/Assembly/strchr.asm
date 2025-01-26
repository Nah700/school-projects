BITS 64
SECTION .text
GLOBAL strchr
strchr:
        MOV RCX, 0      ; init loop counter to 0
        MOV RAX, 0      ; init return value to 0
loop:
        CMP BYTE [RDI + RCX], SIL       ; RDi la string, RCX le compteur, SIL le caractère, on compare le caractère de la string avec le caractère recherché
        JE found        ; si on le trouve on jump au label found
        CMP BYTE [RDI + RCX], 0x00         ; compare le caractère avec le caractère nul
        JE notfound     ; si on le trouve on jump au label notfound
        INC RCX         ; incrémente le compteur
        JMP loop        ; continuer la boucle

notfound:
        MOV RAX, 0
        RET
found:
        LEA RAX, [RDI, RCX]    ; on met dans RAX la valeur de RCX
        RET                    ; on retourne la valeur de RAX
