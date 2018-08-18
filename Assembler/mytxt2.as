; file ps.as
.entry LENGTH
.extern W
LOOP: bne L1(#-2048,r1)
 prn #2047
 jsr L3
L1: dec K
.entry LOOP
MAIN: mov r7 ,LENGTH
 bne W(r4,r5)
 cmp r1, r4
 jmp LOOP(K,W)
END: rts
STR: .string "mIkO"
LENGTH: .data 400,-8192,8191
K: .data 888
.extern L3 
