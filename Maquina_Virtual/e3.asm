MOV DX, 0
MOV CX, 10
MOV AX, %000
SYS %3
MOV DX, 20 ;lees el 2do
MOV CX, 10
MOV AX, %000
SYS %3
MOV AX,0
call concatena
STOP


concatena:SLEN CX,[0] ;
SMOV [CX],[DX]
RET