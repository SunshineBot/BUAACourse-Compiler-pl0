
add       $fp, $sp, $0
addi      $t9, $0, 3
sw        $t9, -0($sp)
j         semiProgLabel1
proca:    
j         semiProgLabel2
procb:    
j         semiProgLabel3
procc:    
j         semiProgLabel4
procd:    
j         semiProgLabel5
semiProgLabel5:
addi      $v0, $0, 11
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 99
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
lw        $t0, -12($fp)
lw        $t7, -56($t0)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $t7, $0, 27
add       $t8, $t7, $0
add       $t9, $t8, $0
lw        $t0, -12($fp)
sw        $t9, -56($t0)
jr        $ra
semiProgLabel4:
addi      $v0, $0, 11
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 99
syscall   
addi      $a0, $0, 99
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
lw        $t0, -8($fp)
lw        $t7, -56($t0)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
jr        $ra
semiProgLabel3:
addi      $v0, $0, 11
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 99
syscall   
addi      $a0, $0, 98
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
lw        $t0, -4($fp)
lw        $t7, -56($t0)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
jr        $ra
semiProgLabel2:
addi      $v0, $0, 11
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 99
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
lw        $t7, -56($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
jr        $ra
helloworld:
j         semiProgLabel6
semiProgLabel6:
addi      $v0, $0, 11
addi      $a0, $0, 104
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 44
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 115
syscall   
addi      $a0, $0, 99
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 33
syscall   
jr        $ra
addition: 
j         semiProgLabel7
semiProgLabel7:
lw        $t7, -56($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
lw        $t7, -60($sp)
add       $t8, $t7, $0
add       $t9, $t9, $t8
sw        $t9, -68($sp)
lw        $t7, -68($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
lw        $t1, -64($sp)
sw        $t9, -0($t1)
jr        $ra
alladdition:
j         semiProgLabel8
semiProgLabel8:
lw        $t7, -56($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s0, $t9, 0
lw        $t7, -60($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s1, $t9, 0
sub       $t4, $s0, $s1
bltz      $t4, elseLabel9
lw        $t7, -56($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -68($sp)
lw        $t7, -60($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -56($sp)
lw        $t7, -68($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -60($sp)
j         endifLabel9
elseLabel9:
endifLabel9:
addi      $t7, $0, 0
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -64($sp)
lw        $t7, -56($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s0, $t9, 0
lw        $t7, -60($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s1, $t9, 0
forLabel10:
sub       $t4, $s0, $s1
bgtz      $t4, endforLabel10
sw        $s0, -68($sp)
sw        $s1, -72($sp)
lw        $t7, -64($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
lw        $t7, -68($sp)
add       $t8, $t7, $0
add       $t9, $t9, $t8
sw        $t9, -64($sp)
lw        $s0, -68($sp)
lw        $s1, -72($sp)
addi      $s0, $s0, 1
j         forLabel10
endforLabel10:
lw        $t7, -64($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $t9, 0
jr        $ra
getfive:  
j         semiProgLabel11
semiProgLabel11:
addi      $t7, $0, 5
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $t9, 0
jr        $ra
geti:     
j         semiProgLabel12
semiProgLabel12:
lw        $t0, -4($fp)
lw        $t7, -4($t0)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $t9, 0
jr        $ra
semiProgLabel1:
addi      $t7, $0, 3
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -4($sp)
lw        $t7, -4($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $v0, $0, 11
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
sw        $t8, -40($sp)
sw        $t9, -44($sp)
addi      $t7, $0, 3
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -112($sp)
addi      $t7, $0, 5
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -116($sp)
lw        $t0, -0($fp)
sw        $t0, -48($sp)
sw        $sp, -52($sp)
sw        $v0, -56($sp)
sw        $t8, -60($sp)
sw        $t9, -64($sp)
sw        $s0, -68($sp)
sw        $s1, -72($sp)
sw        $s2, -76($sp)
sw        $s3, -80($sp)
sw        $s4, -84($sp)
sw        $s5, -88($sp)
sw        $s6, -92($sp)
sw        $s7, -96($sp)
sw        $ra, -100($sp)
sw        $fp, -104($sp)
sw        $sp, -108($sp)
subi      $fp, $fp, 48
subi      $sp, $sp, 56
jal       alladdition
addi      $t7, $v0, 0
lw        $v0, -0($sp)
lw        $t8, -4($sp)
lw        $t9, -8($sp)
lw        $s0, -12($sp)
lw        $s1, -16($sp)
lw        $s2, -20($sp)
lw        $s3, -24($sp)
lw        $s4, -28($sp)
lw        $s5, -32($sp)
lw        $s6, -36($sp)
lw        $s7, -40($sp)
lw        $ra, -44($sp)
lw        $fp, -48($sp)
lw        $sp, -52($sp)
lw        $t9, -52($sp)
lw        $t8, -48($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $t7, $0, 3
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -112($sp)
addi      $t7, $0, 7
add       $t8, $t7, $0
add       $t9, $t8, $0
sw        $t9, -116($sp)
lw        $t7, -12($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
subi      $t9, $sp, 12
sw        $t9, -120($sp)
lw        $t0, -0($fp)
sw        $t0, -48($sp)
sw        $sp, -52($sp)
sw        $v0, -56($sp)
sw        $t8, -60($sp)
sw        $t9, -64($sp)
sw        $s0, -68($sp)
sw        $s1, -72($sp)
sw        $s2, -76($sp)
sw        $s3, -80($sp)
sw        $s4, -84($sp)
sw        $s5, -88($sp)
sw        $s6, -92($sp)
sw        $s7, -96($sp)
sw        $ra, -100($sp)
sw        $fp, -104($sp)
sw        $sp, -108($sp)
subi      $fp, $fp, 48
subi      $sp, $sp, 56
jal       addition
lw        $v0, -0($sp)
lw        $t8, -4($sp)
lw        $t9, -8($sp)
lw        $s0, -12($sp)
lw        $s1, -16($sp)
lw        $s2, -20($sp)
lw        $s3, -24($sp)
lw        $s4, -28($sp)
lw        $s5, -32($sp)
lw        $s6, -36($sp)
lw        $s7, -40($sp)
lw        $ra, -44($sp)
lw        $fp, -48($sp)
lw        $sp, -52($sp)
addi      $v0, $0, 11
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 102
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 51
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 55
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
lw        $t7, -12($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
lw        $t0, -0($fp)
sw        $t0, -56($sp)
sw        $sp, -60($sp)
sw        $v0, -64($sp)
sw        $t8, -68($sp)
sw        $t9, -72($sp)
sw        $s0, -76($sp)
sw        $s1, -80($sp)
sw        $s2, -84($sp)
sw        $s3, -88($sp)
sw        $s4, -92($sp)
sw        $s5, -96($sp)
sw        $s6, -100($sp)
sw        $s7, -104($sp)
sw        $ra, -108($sp)
sw        $fp, -112($sp)
sw        $sp, -116($sp)
subi      $fp, $fp, 56
subi      $sp, $sp, 64
jal       helloworld
lw        $v0, -0($sp)
lw        $t8, -4($sp)
lw        $t9, -8($sp)
lw        $s0, -12($sp)
lw        $s1, -16($sp)
lw        $s2, -20($sp)
lw        $s3, -24($sp)
lw        $s4, -28($sp)
lw        $s5, -32($sp)
lw        $s6, -36($sp)
lw        $s7, -40($sp)
lw        $ra, -44($sp)
lw        $fp, -48($sp)
lw        $sp, -52($sp)
addi      $v0, $0, 11
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 115
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 121
syscall   
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 117
syscall   
addi      $a0, $0, 109
syscall   
addi      $a0, $0, 98
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
addi      $v0, $0, 5
syscall   
sw        $v0, -16($sp)
addi      $v0, $0, 11
addi      $a0, $0, 121
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 117
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 104
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 118
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 121
syscall   
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
lw        $t7, -16($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $v0, $0, 11
addi      $a0, $0, 44
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 104
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 115
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 115
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 102
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 118
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 58
syscall   
addi      $a0, $0, 32
syscall   
sw        $t8, -56($sp)
sw        $t9, -60($sp)
lw        $t0, -0($fp)
sw        $t0, -64($sp)
sw        $sp, -68($sp)
sw        $v0, -72($sp)
sw        $t8, -76($sp)
sw        $t9, -80($sp)
sw        $s0, -84($sp)
sw        $s1, -88($sp)
sw        $s2, -92($sp)
sw        $s3, -96($sp)
sw        $s4, -100($sp)
sw        $s5, -104($sp)
sw        $s6, -108($sp)
sw        $s7, -112($sp)
sw        $ra, -116($sp)
sw        $fp, -120($sp)
sw        $sp, -124($sp)
subi      $fp, $fp, 64
subi      $sp, $sp, 72
jal       getfive
addi      $t7, $v0, 0
lw        $v0, -0($sp)
lw        $t8, -4($sp)
lw        $t9, -8($sp)
lw        $s0, -12($sp)
lw        $s1, -16($sp)
lw        $s2, -20($sp)
lw        $s3, -24($sp)
lw        $s4, -28($sp)
lw        $s5, -32($sp)
lw        $s6, -36($sp)
lw        $s7, -40($sp)
lw        $ra, -44($sp)
lw        $fp, -48($sp)
lw        $sp, -52($sp)
lw        $t9, -52($sp)
lw        $t8, -48($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $v0, $0, 11
addi      $a0, $0, 46
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 119
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 122
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 121
syscall   
addi      $a0, $0, 58
syscall   
addi      $t7, $0, 0
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s0, $t9, 0
addi      $t7, $0, 4
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s1, $t9, 0
forLabel13:
sub       $t4, $s0, $s1
bgtz      $t4, endforLabel13
sw        $s0, -4($sp)
sw        $s1, -48($sp)
lw        $t7, -4($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s7, $t9, 0
lw        $t7, -4($sp)
add       $t8, $t7, $0
sub       $t9, $0, $t8
addi      $t3, $0, 4
mul       $s7, $s7, $t3
addi      $s7, $s7, 24
sub       $t2, $sp, $s7
sw        $t9, 0($t2)
addi      $v0, $0, 11
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 117
syscall   
addi      $a0, $0, 109
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 114
syscall   
addi      $a0, $0, 91
syscall   
lw        $t7, -4($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $v0, $0, 11
addi      $a0, $0, 93
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 61
syscall   
addi      $a0, $0, 32
syscall   
lw        $t7, -4($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $v0, $0, 11
addi      $a0, $0, 44
syscall   
addi      $a0, $0, 32
syscall   
lw        $s0, -4($sp)
lw        $s1, -48($sp)
addi      $s0, $s0, 1
j         forLabel13
endforLabel13:
addi      $v0, $0, 11
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 94
syscall   
addi      $a0, $0, 51
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
whileLabel14:
lw        $t7, -4($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s0, $t9, 0
addi      $t7, $0, 0
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $s1, $t9, 0
sub       $t4, $s0, $s1
bltz      $t4, endWhileLabel14
sw        $s0, -48($sp)
sw        $s1, -52($sp)
addi      $v0, $0, 11
addi      $a0, $0, 32
syscall   
lw        $t7, -4($sp)
add       $t8, $t7, $0
lw        $t7, -4($sp)
mul       $t8, $t8, $t7
lw        $t7, -4($sp)
mul       $t8, $t8, $t7
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
lw        $t7, -4($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $t7, $0, 1
add       $t8, $t7, $0
sub       $t9, $t9, $t8
sw        $t9, -4($sp)
lw        $s1, -52($sp)
lw        $s0, -48($sp)
j         whileLabel14
endWhileLabel14:
addi      $v0, $0, 11
addi      $a0, $0, 44
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 108
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 111
syscall   
addi      $a0, $0, 102
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 49
syscall   
addi      $a0, $0, 48
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 97
syscall   
addi      $a0, $0, 110
syscall   
addi      $a0, $0, 100
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 53
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 58
syscall   
lw        $t7, -12($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $v0, $0, 11
addi      $a0, $0, 46
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 112
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 61
syscall   
addi      $a0, $0, 32
syscall   
lw        $t7, -0($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
addi      $v0, $0, 11
addi      $a0, $0, 46
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 103
syscall   
addi      $a0, $0, 101
syscall   
addi      $a0, $0, 116
syscall   
addi      $a0, $0, 105
syscall   
addi      $a0, $0, 32
syscall   
addi      $a0, $0, 61
syscall   
addi      $a0, $0, 32
syscall   
sw        $t8, -48($sp)
sw        $t9, -52($sp)
lw        $t0, -0($fp)
sw        $t0, -56($sp)
sw        $sp, -60($sp)
sw        $v0, -64($sp)
sw        $t8, -68($sp)
sw        $t9, -72($sp)
sw        $s0, -76($sp)
sw        $s1, -80($sp)
sw        $s2, -84($sp)
sw        $s3, -88($sp)
sw        $s4, -92($sp)
sw        $s5, -96($sp)
sw        $s6, -100($sp)
sw        $s7, -104($sp)
sw        $ra, -108($sp)
sw        $fp, -112($sp)
sw        $sp, -116($sp)
subi      $fp, $fp, 56
subi      $sp, $sp, 64
jal       geti
addi      $t7, $v0, 0
lw        $v0, -0($sp)
lw        $t8, -4($sp)
lw        $t9, -8($sp)
lw        $s0, -12($sp)
lw        $s1, -16($sp)
lw        $s2, -20($sp)
lw        $s3, -24($sp)
lw        $s4, -28($sp)
lw        $s5, -32($sp)
lw        $s6, -36($sp)
lw        $s7, -40($sp)
lw        $ra, -44($sp)
lw        $fp, -48($sp)
lw        $sp, -52($sp)
lw        $t9, -52($sp)
lw        $t8, -48($sp)
add       $t8, $t7, $0
add       $t9, $t8, $0
addi      $v0, $0, 1
addi      $a0, $t9, 0
syscall   
