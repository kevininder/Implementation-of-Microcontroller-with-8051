# Use CPL to blink
ORG 0H
BACK: CPL P1.2
ACALL DELAY
SJMP BACK

# Alternative way
ORG 0H
AGAIN: SETB P1.2
ACALL DELAY
CLR P1.2
ACALL DELAY
SJMP AGAIN

ORG 300H
DELAY: MOV R5, #0FFH
AGAIN: DJNZ R5, AGAIN
RET
END