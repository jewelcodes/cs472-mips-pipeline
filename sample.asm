; This is the disassembly of the sample instructions provided, disassembled by
; my own disassembler that I wrote for project 1 (with the added sb, lb, and
; nop instructions).
;
; This wasn't necessary for project 3 but I figured it'd be easier to implement
; a pipeline if I actually knew what the instructions were, so I could guess
; what the expected output might look like.
;
; I only put it here for completion's sake.
 
  9A040   sb $2, 0($8)
  9A044   lb $10, -4($8)
  9A048   add $3, $4, $3
  9A04C   add $7, $9, $6
  9A050   add $9, $9, $2
  9A054   lb $24, 0($8)
  9A058   lb $17, 16($10)
  9A05C   sub $8, $3, $2
  9A060   nop
  9A064   nop
  9A068   nop
  9A06C   nop
