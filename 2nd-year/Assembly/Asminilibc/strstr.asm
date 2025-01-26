BITS 64

section	.text
    global strstr

strstr:
	MOV	RCX, 0
    MOV R8, 0
    CMP BYTE [RSI], 0x00
    JE .end

.loop:
    CMP BYTE [RDI + RCX], 0x00
    JE .neine
    MOV R9B, BYTE [RSI]
    CMP BYTE [RDI + RCX], R9B
    JE .starting_compare
    INC RCX
    JMP .loop

.starting_compare:
    CMP BYTE [RSI + R8], 0x00
    JE .end
    LEA R9, BYTE [RDI + RCX]
    MOV R9B, BYTE [R9 + R8]
    CMP BYTE [RSI + R8], R9B
    JNE .continue
    INC R8
    JMP .starting_compare

.continue:
    INC RCX
    JMP .loop

.neine:
    MOV RAX, 0
    RET

.end:
    LEA RAX, [RDI + RCX]
    RET