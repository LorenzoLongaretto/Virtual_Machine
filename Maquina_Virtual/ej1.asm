	MOV AX,%001; leo decimal
MOV DX,10
MOV CX,2
SYS 1 ; leo los dos parametros
PUSH [10] 
PUSH [11];
CALL POT
ADD SP,2
MOV [10],AX
MOV AX,%001
MOV CX,1
SYS 2
STOP

POT: PUSH BP 
MOV BP,SP 
PUSH BX
PUSH CX
CMP [BP+2],0 
JNZ SEGUIR ;caso recursivo si es distinto de cero
MOV AX,1 ;caso base si es cero
JMP FIN

;preparar siguiente llamado recursivo
SEGUIR: MOV BX, [BP+3]
MOV CX,[BP+2]
SUB CX,1
PUSH BX
PUSH CX
CALL POT
MUL AX, BX

FIN: POP CX
POP BX
MOV SP, BP
POP BP
RET