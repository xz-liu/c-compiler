.model flat,stdcall 
	
option casemap :none
 
includelib kernel32.lib
includelib masm32.lib
includelib msvcrt.lib

printf PROTO C:ptr sbyte,:vararg
scanf PROTO C:ptr sbyte,:vararg

ExitProcess PROTO STDCALL:DWORD
StdOut		PROTO STDCALL:DWORD
StdIn       PROTO :DWORD,:DWORD

test_struct$ STRUCT
a$ DWORD  ?
b$ DWORD  ?
c$ DWORD  ?
test_struct$ ENDS
.data
$$read_char BYTE '%c',0
i$_1 DWORD  ?
$return_value_0 DWORD  ?
i$_2 DWORD ?
str$_3 DWORD ?
CONST_42 DWORD 0
$Temp_82_5 DWORD  ?
cur$_4 DWORD  ?
$Temp_83_7 DWORD  ?
$Temp_1_8 DWORD  ?
$Temp_2_9 DWORD  ?
$Temp_84_11 DWORD  ?
i$_13 DWORD ?
$Temp_85_16 DWORD  ?
cnt$_15 DWORD  ?
$Temp_86_17 DWORD  ?
$Temp_5_18 DWORD  ?
$Temp_6_19 DWORD  ?
CONST_97 BYTE '-'
$Temp_87_20 DWORD  ?
$Temp_88_22 DWORD  ?
$Temp_8_23 DWORD  ?
CONST_110 BYTE '0'
$Temp_89_24 DWORD  ?
$Temp_10_26 DWORD  ?
cs$_14 BYTE 20 DUP(?)
$Temp_90_28 DWORD  ?
CONST_127 DWORD 10
$Temp_12_29 DWORD  ?
$Temp_91_30 DWORD  ?
$Temp_13_31 DWORD  ?
$Temp_92_32 BYTE  ?
$Temp_93_33 DWORD  ?
$Temp_94_34 DWORD  ?
$Temp_95_35 DWORD  ?
$Temp_14_36 DWORD  ?
$Temp_96_38 DWORD  ?
$Temp_97_42 DWORD  ?
minus$_41 DWORD  ?
$Temp_98_44 DWORD  ?
result$_43 DWORD  ?
$Temp_17_45 DWORD  ?
ch$_46 DWORD  ?
CONST_178 DWORD 1
$Temp_99_47 DWORD  ?
$Temp_18_48 DWORD  ?
$Temp_100_49 DWORD  ?
$Temp_19_50 DWORD  ?
CONST_197 BYTE '9'
$Temp_101_51 DWORD  ?
$Temp_20_52 DWORD  ?
$Temp_21_53 DWORD  ?
$Temp_22_54 DWORD  ?
$Temp_102_55 DWORD  ?
$Temp_23_56 DWORD  ?
$Temp_103_57 DWORD  ?
$Temp_104_58 DWORD  ?
$Temp_24_59 DWORD  ?
$Temp_25_60 DWORD  ?
$Temp_105_61 DWORD  ?
$Temp_26_62 DWORD  ?
$Temp_106_63 DWORD  ?
$Temp_27_64 DWORD  ?
$Temp_28_65 DWORD  ?
$Temp_107_66 DWORD  ?
$Temp_29_67 DWORD  ?
$Temp_108_68 DWORD  ?
$Temp_30_69 DWORD  ?
$Temp_109_70 DWORD  ?
$Temp_31_71 DWORD  ?
$Temp_110_72 DWORD  ?
$Temp_32_73 DWORD  ?
$return_value_40 DWORD  ?
a$_75 DWORD ?
b$_76 DWORD ?
$Temp_33_77 DWORD  ?
$return_value_74 DWORD  ?
a$_79 DWORD ?
b$_80 DWORD ?
$Temp_34_81 DWORD  ?
$return_value_78 DWORD  ?
$Temp_111_87 DWORD  ?
cur$_86 DWORD  ?
$Temp_112_88 DWORD  ?
CONST_75 DWORD 20
$Temp_35_89 DWORD  ?
$Temp_36_90 DWORD  ?
str$_85 BYTE 20 DUP(?)
$Temp_113_92 DWORD  ?
$Temp_38_93 DWORD  ?
$Temp_114_94 BYTE  ?
$Temp_115_96 DWORD  ?
CONST_373 DWORD 3
$Temp_116_100 DWORD  ?
a$_99 DWORD  ?
CONST_377 DWORD 5
$Temp_117_102 DWORD  ?
b$_101 DWORD  ?
CONST_384 DWORD 2
$Temp_118_105 DWORD  ?
c$_104 DWORD  ?
$Temp_119_107 DWORD  ?
x$_106 DWORD  ?
CONST_393 DWORD 3.500000
$Temp_120_109 DWORD  ?
f$_108 DWORD  ?
CONST_397 DWORD 3.200000
$Temp_121_111 DWORD  ?
s$_110 DWORD  ?
$Temp_41_116 DWORD  ?
xx$_117 DWORD  ?
$Temp_42_118 DWORD  ?
yy$_119 DWORD  ?
cc$_120 BYTE 4 DUP(?)
$Temp_122_122 BYTE  ?
$Temp_123_123 DWORD  ?
i$_103 DWORD  ?
$Temp_124_124 DWORD  ?
$Temp_44_125 DWORD  ?
$Temp_45_126 DWORD  ?
CONST_470 BYTE '_'
$Temp_48_129 DWORD  ?
hm2$_114 DWORD 10 DUP(?)
CONST_489 DWORD 100
$Temp_125_132 DWORD  ?
hm3$_115 DWORD 10 DUP(?)
CONST_496 DWORD 2000
$Temp_126_134 DWORD  ?
hm$_113 DWORD 10 DUP(?)
$Temp_55_138 DWORD  ?
ts$_112 test_struct$  <>
CONST_526 DWORD 345678
$Temp_59_142 DWORD  ?
$Temp_127_143 DWORD  ?
CONST_530 BYTE '5'
$Temp_128_144 DWORD  ?
CONST_535 BYTE ' '
$Temp_129_146 DWORD  ?
CONST_540 DWORD 234
$Temp_130_148 DWORD  ?
$Temp_131_150 DWORD  ?
$Temp_63_151 DWORD  ?
$Temp_64_152 DWORD  ?
$Temp_65_153 DWORD  ?
$Temp_132_154 DWORD  ?
$Temp_133_155 DWORD  ?
$Temp_66_156 DWORD  ?
$Temp_67_157 DWORD  ?
y$_158 DWORD  ?
$Temp_134_159 DWORD  ?
$Temp_135_160 DWORD  ?
$Temp_136_161 DWORD  ?
$Temp_137_164 DWORD  ?
$Temp_138_167 DWORD  ?
$Temp_139_170 DWORD  ?
$Temp_140_174 DWORD  ?
CONST_651 BYTE "fesipfjesronueigrewpofjegrebneojrefwifef  faweffw        freswager",0

.stack 100
.code
getchar$ PROC
invoke scanf, offset $$read_char, offset i$_1
mov eax,i$_1
mov $return_value_0,eax
ret
getchar$ ENDP
putchar$ PROC
invoke StdOut, addr i$_2
ret
putchar$ ENDP
print_str$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_82_5,eax
mov eax,$Temp_82_5
mov cur$_4,eax
jmp LABEL_3
LABEL_0:nop
xor eax,eax
mov esi,cur$_4
mov ebx,[str$_3]
mov al,byte ptr [ebx+1*esi]
mov $Temp_83_7,eax
mov eax,$Temp_83_7
sub eax,CONST_42

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
xor eax,1
			mov $Temp_1_8,eax
mov eax,$Temp_1_8
and eax,eax
jnz LABEL_3
mov eax,$Temp_1_8
and eax,eax
jz LABEL_2
LABEL_1:nop
mov eax,cur$_4
mov $Temp_2_9,eax
inc cur$_4
jmp LABEL_0
LABEL_3:nop
xor eax,eax
mov esi,cur$_4
mov ebx,[str$_3]
mov al,byte ptr [ebx+1*esi]
mov $Temp_84_11,eax
mov eax,$Temp_84_11
mov i$_2,eax
call putchar$
jmp LABEL_1
LABEL_2:nop
ret
print_str$ ENDP
print_int$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_85_16,eax
mov eax,$Temp_85_16
mov cnt$_15,eax
xor eax,eax
mov eax,i$_13
mov $Temp_86_17,eax
mov eax,$Temp_86_17
sub eax,CONST_42
shr eax,31
mov $Temp_5_18,eax
mov eax,$Temp_5_18
and eax,eax
jz LABEL_4
mov eax,i$_13
neg eax
mov $Temp_6_19,eax
mov eax,$Temp_6_19
mov i$_13,eax
xor eax,eax
mov al,CONST_97
mov $Temp_87_20,eax
mov eax,$Temp_87_20
mov i$_2,eax
call putchar$
jmp LABEL_5
LABEL_4:nop
LABEL_5:nop
xor eax,eax
mov eax,i$_13
mov $Temp_88_22,eax
mov eax,$Temp_88_22
sub eax,CONST_42

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_8_23,eax
mov eax,$Temp_8_23
and eax,eax
jz LABEL_6
xor eax,eax
mov al,CONST_110
mov $Temp_89_24,eax
mov eax,$Temp_89_24
mov i$_2,eax
call putchar$
jmp LABEL_7
LABEL_6:nop
LABEL_7:nop
LABEL_8:nop
mov eax,i$_13
and eax,eax
jz LABEL_9
mov eax,cnt$_15
mov $Temp_10_26,eax
inc cnt$_15
xor eax,eax
mov eax,i$_13
mov $Temp_90_28,eax

mov eax,$Temp_90_28
cdq
mov ecx,CONST_127
idiv ecx
mov $Temp_12_29,edx
xor eax,eax
mov al,CONST_110
mov $Temp_91_30,eax
mov eax,$Temp_12_29
add eax,$Temp_91_30
mov $Temp_13_31,eax
xor eax,eax
mov eax,$Temp_13_31
mov $Temp_92_32,al
mov al,$Temp_92_32
mov esi,$Temp_10_26
mov byte ptr cs$_14[1*esi],al
xor eax,eax
mov eax,CONST_127
mov $Temp_93_33,eax
mov eax,i$_13
cdq
idiv $Temp_93_33
mov $Temp_94_34,eax
mov eax,$Temp_94_34
mov i$_13,eax
jmp LABEL_8
LABEL_9:nop
LABEL_10:nop
xor eax,eax
mov eax,cnt$_15
mov $Temp_95_35,eax
mov eax,$Temp_95_35
sub eax,CONST_42
shr eax,31
xor eax,1
mov $Temp_14_36,eax
mov eax,$Temp_14_36
and eax,eax
jz LABEL_11
dec cnt$_15
xor eax,eax
mov esi,cnt$_15
mov al,byte ptr cs$_14[1*esi]
mov $Temp_96_38,eax
mov eax,$Temp_96_38
mov i$_2,eax
call putchar$
jmp LABEL_10
LABEL_11:nop
ret
print_int$ ENDP
read_int$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_97_42,eax
mov eax,$Temp_97_42
mov minus$_41,eax
xor eax,eax
mov eax,CONST_42
mov $Temp_98_44,eax
mov eax,$Temp_98_44
mov result$_43,eax
call getchar$
mov eax,$return_value_0
mov $Temp_17_45,eax
mov eax,$Temp_17_45
mov ch$_46,eax
LABEL_12:nop
mov eax,CONST_178
and eax,eax
jz LABEL_13
xor eax,eax
mov al,CONST_97
mov $Temp_99_47,eax
mov eax,ch$_46
sub eax,$Temp_99_47

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_18_48,eax
mov eax,$Temp_18_48
and eax,eax
jz LABEL_14
jmp LABEL_13
jmp LABEL_15
LABEL_14:nop
LABEL_15:nop
xor eax,eax
mov al,CONST_110
mov $Temp_100_49,eax
mov eax,ch$_46
sub eax,$Temp_100_49
shr eax,31
xor eax,1
mov $Temp_19_50,eax
xor eax,eax
mov al,CONST_197
mov $Temp_101_51,eax
mov eax,$Temp_101_51
sub eax,ch$_46
shr eax,31
xor eax,1
mov $Temp_20_52,eax
mov eax,$Temp_20_52
mov ebx,$Temp_19_50

test eax,eax
pushfd
pop ecx
test ebx,ebx		
pushfd
pop edx
or ecx,edx
and ecx,0040h  ;ZF == 0x0040
shr ecx,6
xor ecx,1
			mov $Temp_21_53,ecx
mov eax,$Temp_21_53
and eax,eax
jz LABEL_16
jmp LABEL_13
jmp LABEL_17
LABEL_16:nop
LABEL_17:nop
call getchar$
mov eax,$return_value_0
mov $Temp_22_54,eax
mov eax,$Temp_22_54
mov ch$_46,eax
jmp LABEL_12
LABEL_13:nop
xor eax,eax
mov al,CONST_97
mov $Temp_102_55,eax
mov eax,ch$_46
sub eax,$Temp_102_55

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_23_56,eax
mov eax,$Temp_23_56
and eax,eax
jz LABEL_18
xor eax,eax
mov eax,CONST_178
mov $Temp_103_57,eax
mov eax,$Temp_103_57
mov minus$_41,eax
jmp LABEL_19
LABEL_18:nop
xor eax,eax
mov al,CONST_110
mov $Temp_104_58,eax
mov eax,ch$_46
sub eax,$Temp_104_58
mov $Temp_24_59,eax
mov eax,$Temp_24_59
mov result$_43,eax
LABEL_19:nop
LABEL_20:nop
mov eax,CONST_178
and eax,eax
jz LABEL_21
call getchar$
mov eax,$return_value_0
mov $Temp_25_60,eax
mov eax,$Temp_25_60
mov ch$_46,eax
xor eax,eax
mov al,CONST_110
mov $Temp_105_61,eax
mov eax,ch$_46
sub eax,$Temp_105_61
shr eax,31
mov $Temp_26_62,eax
xor eax,eax
mov al,CONST_197
mov $Temp_106_63,eax
mov eax,$Temp_106_63
sub eax,ch$_46
shr eax,31
mov $Temp_27_64,eax
mov eax,$Temp_27_64
or eax,$Temp_26_62

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
xor eax,1
			mov $Temp_28_65,eax
mov eax,$Temp_28_65
and eax,eax
jz LABEL_22
jmp LABEL_21
jmp LABEL_23
LABEL_22:nop
LABEL_23:nop
xor eax,eax
mov eax,result$_43
mov $Temp_107_66,eax
mov eax,$Temp_107_66
imul eax,CONST_127
mov $Temp_29_67,eax
xor eax,eax
mov al,CONST_110
mov $Temp_108_68,eax
mov eax,ch$_46
sub eax,$Temp_108_68
mov $Temp_30_69,eax
xor eax,eax
mov eax,$Temp_30_69
mov $Temp_109_70,eax
mov eax,$Temp_29_67
add eax,$Temp_109_70
mov $Temp_31_71,eax
xor eax,eax
mov eax,$Temp_31_71
mov $Temp_110_72,eax
mov eax,$Temp_110_72
mov result$_43,eax
jmp LABEL_20
LABEL_21:nop
mov eax,minus$_41
and eax,eax
jz LABEL_24
mov eax,result$_43
neg eax
mov $Temp_32_73,eax
mov eax,$Temp_32_73
mov $return_value_40,eax
ret
jmp LABEL_25
LABEL_24:nop
mov eax,result$_43
mov $return_value_40,eax
ret
LABEL_25:nop
read_int$ ENDP
add_two_num$ PROC
mov eax,a$_75
add eax,b$_76
mov $Temp_33_77,eax
mov eax,$Temp_33_77
mov $return_value_74,eax
ret
add_two_num$ ENDP
sub_two_num$ PROC
mov eax,a$_79
sub eax,b$_80
mov $Temp_34_81,eax
mov eax,$Temp_34_81
mov $return_value_78,eax
ret
sub_two_num$ ENDP
print_own_str$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_111_87,eax
mov eax,$Temp_111_87
mov cur$_86,eax
jmp LABEL_29
LABEL_26:nop
xor eax,eax
mov eax,cur$_86
mov $Temp_112_88,eax
mov eax,$Temp_112_88
sub eax,CONST_75
shr eax,31
mov $Temp_35_89,eax
mov eax,$Temp_35_89
and eax,eax
jnz LABEL_29
mov eax,$Temp_35_89
and eax,eax
jz LABEL_28
LABEL_27:nop
mov eax,cur$_86
mov $Temp_36_90,eax
inc cur$_86
jmp LABEL_26
LABEL_29:nop
xor eax,eax
mov al,CONST_110
mov $Temp_113_92,eax
mov eax,$Temp_113_92
add eax,cur$_86
mov $Temp_38_93,eax
xor eax,eax
mov eax,$Temp_38_93
mov $Temp_114_94,al
mov al,$Temp_114_94
mov esi,cur$_86
mov byte ptr str$_85[1*esi],al
xor eax,eax
mov esi,cur$_86
mov al,byte ptr str$_85[1*esi]
mov $Temp_115_96,eax
mov eax,$Temp_115_96
mov i$_2,eax
call putchar$
jmp LABEL_27
LABEL_28:nop
ret
print_own_str$ ENDP
main PROC
xor eax,eax
mov eax,CONST_373
mov $Temp_116_100,eax
mov eax,$Temp_116_100
mov a$_99,eax
xor eax,eax
mov eax,CONST_377
mov $Temp_117_102,eax
mov eax,$Temp_117_102
mov b$_101,eax
xor eax,eax
mov eax,CONST_384
mov $Temp_118_105,eax
mov eax,$Temp_118_105
mov c$_104,eax
xor eax,eax
mov eax,CONST_42
mov $Temp_119_107,eax
mov eax,$Temp_119_107
mov x$_106,eax
fild CONST_393
fst $Temp_120_109
mov eax,$Temp_120_109
mov f$_108,eax
fild CONST_397
fst $Temp_121_111
mov eax,$Temp_121_111
mov s$_110,eax
mov eax,a$_99
mov a$_75,eax
mov eax,b$_101
mov b$_76,eax
call add_two_num$
mov eax,$return_value_74
mov $Temp_41_116,eax
mov eax,$Temp_41_116
mov xx$_117,eax
mov eax,a$_99
mov a$_79,eax
mov eax,b$_101
mov b$_80,eax
call sub_two_num$
mov eax,$return_value_78
mov $Temp_42_118,eax
mov eax,$Temp_42_118
mov yy$_119,eax
xor eax,eax
mov eax,CONST_42
mov $Temp_122_122,al
mov al,$Temp_122_122
mov esi,CONST_373
mov byte ptr cc$_120[1*esi],al
xor eax,eax
mov eax,CONST_42
mov $Temp_123_123,eax
mov eax,$Temp_123_123
mov i$_103,eax
jmp LABEL_33
LABEL_30:nop
xor eax,eax
mov eax,i$_103
mov $Temp_124_124,eax
mov eax,$Temp_124_124
sub eax,CONST_373
shr eax,31
mov $Temp_44_125,eax
mov eax,$Temp_44_125
and eax,eax
jnz LABEL_33
mov eax,$Temp_44_125
and eax,eax
jz LABEL_32
LABEL_31:nop
mov eax,i$_103
mov $Temp_45_126,eax
inc i$_103
jmp LABEL_30
LABEL_33:nop
mov al,CONST_470
mov esi,i$_103
mov byte ptr cc$_120[1*esi],al
jmp LABEL_31
LABEL_32:nop
mov eax,offset cc$_120
mov str$_3,eax
call print_str$
call read_int$
mov eax,$return_value_40
mov $Temp_48_129,eax
mov eax,$Temp_48_129
mov i$_13,eax
call print_int$
xor eax,eax
mov eax,CONST_489
mov $Temp_125_132,eax
mov eax,$Temp_125_132
mov esi,b$_101
mov dword ptr hm2$_114[4*esi],eax
xor eax,eax
mov eax,CONST_496
mov $Temp_126_134,eax
mov eax,$Temp_126_134
mov esi,c$_104
mov dword ptr hm3$_115[4*esi],eax
mov esi,b$_101
mov eax,dword ptr hm2$_114[4*esi]
mov esi,c$_104
add eax,dword ptr hm3$_115[4*esi]
mov $Temp_55_138,eax
mov eax,$Temp_55_138
mov esi,a$_99
mov dword ptr hm$_113[4*esi],eax
mov eax,CONST_526
neg eax
mov $Temp_59_142,eax
xor eax,eax
mov eax,$Temp_59_142
mov $Temp_127_143,eax
mov eax,$Temp_127_143
mov ts$_112.c$,eax
mov eax,ts$_112.c$
mov ts$_112.b$,eax
mov eax,ts$_112.b$
mov ts$_112.a$,eax
xor eax,eax
mov al,CONST_530
mov $Temp_128_144,eax
mov eax,$Temp_128_144
mov i$_2,eax
call putchar$
xor eax,eax
mov al,CONST_535
mov $Temp_129_146,eax
mov eax,$Temp_129_146
mov i$_2,eax
call putchar$
xor eax,eax
mov eax,CONST_540
mov $Temp_130_148,eax
mov eax,$Temp_130_148
mov i$_13,eax
call print_int$
fld f$_108
fld s$_110
fadd
fst $Temp_131_150
mov eax,$Temp_131_150
mov f$_108,eax
mov eax,b$_101
sub eax,a$_99
shr eax,31
mov $Temp_63_151,eax
mov eax,$Temp_63_151
and eax,eax
jz LABEL_34
mov eax,a$_99
sub eax,b$_101
mov $Temp_64_152,eax
mov eax,$Temp_64_152
mov c$_104,eax
jmp LABEL_35
LABEL_34:nop
mov eax,b$_101
sub eax,a$_99
mov $Temp_65_153,eax
mov eax,$Temp_65_153
mov c$_104,eax
LABEL_35:nop
xor eax,eax
mov eax,CONST_42
mov $Temp_132_154,eax
mov eax,$Temp_132_154
mov i$_103,eax
jmp LABEL_39
LABEL_36:nop
xor eax,eax
mov eax,i$_103
mov $Temp_133_155,eax
mov eax,$Temp_133_155
sub eax,CONST_373
shr eax,31
mov $Temp_66_156,eax
mov eax,$Temp_66_156
and eax,eax
jnz LABEL_39
mov eax,$Temp_66_156
and eax,eax
jz LABEL_38
LABEL_37:nop
mov eax,i$_103
mov $Temp_67_157,eax
inc i$_103
jmp LABEL_36
LABEL_39:nop
mov eax,x$_106
mov y$_158,eax
xor eax,eax
mov eax,CONST_75
mov $Temp_134_159,eax
mov eax,x$_106
add eax,$Temp_134_159
mov $Temp_135_160,eax
mov eax,$Temp_135_160
mov x$_106,eax
xor eax,eax
mov al,CONST_97
mov $Temp_136_161,eax
mov eax,$Temp_136_161
mov i$_2,eax
call putchar$
mov eax,y$_158
mov i$_13,eax
call print_int$
jmp LABEL_37
LABEL_38:nop
xor eax,eax
mov al,CONST_535
mov $Temp_137_164,eax
mov eax,$Temp_137_164
mov i$_2,eax
call putchar$
mov eax,x$_106
mov i$_13,eax
call print_int$
xor eax,eax
mov al,CONST_535
mov $Temp_138_167,eax
mov eax,$Temp_138_167
mov i$_2,eax
call putchar$
mov eax,xx$_117
mov i$_13,eax
call print_int$
xor eax,eax
mov al,CONST_535
mov $Temp_139_170,eax
mov eax,$Temp_139_170
mov i$_2,eax
call putchar$
mov esi,a$_99
mov eax,dword ptr hm$_113[4*esi]
mov i$_13,eax
call print_int$
xor eax,eax
mov al,CONST_535
mov $Temp_140_174,eax
mov eax,$Temp_140_174
mov i$_2,eax
call putchar$
mov eax,ts$_112.a$
mov i$_13,eax
call print_int$
call print_own_str$
mov eax,offset CONST_651
mov str$_3,eax
call print_str$
ret
main ENDP

END main
		