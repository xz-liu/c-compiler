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

my_inner_struct$ STRUCT
in$ DWORD  ?
my_inner_struct$ ENDS
my_struct$ STRUCT
a$ DWORD  ?
b$ DWORD  ?
c$ DWORD  ?
my_struct$ ENDS
.data
$$read_char BYTE '%c',0
i$_1 DWORD  ?
$return_value_0 DWORD  ?
i$_2 DWORD ?
str$_3 DWORD ?
CONST_42 DWORD 0
$Temp_100_5 DWORD  ?
cur$_4 DWORD  ?
$Temp_101_7 DWORD  ?
$Temp_1_8 DWORD  ?
$Temp_2_9 DWORD  ?
$Temp_102_11 DWORD  ?
str$_14 DWORD ?
n$_15 DWORD ?
$Temp_103_17 DWORD  ?
i$_16 DWORD  ?
$Temp_104_18 DWORD  ?
CONST_86 DWORD 1
$Temp_5_19 DWORD  ?
$Temp_105_20 DWORD  ?
$Temp_6_21 DWORD  ?
$Temp_7_22 DWORD  ?
$Temp_106_24 DWORD  ?
CONST_102 DWORD 10
$Temp_8_25 DWORD  ?
CONST_107 BYTE ' '
$Temp_107_26 DWORD  ?
$Temp_9_27 DWORD  ?
$Temp_10_28 DWORD  ?
$Temp_108_30 BYTE  ?
$Temp_109_32 BYTE  ?
$return_value_13 DWORD  ?
i$_33 DWORD ?
$Temp_110_36 DWORD  ?
cnt$_35 DWORD  ?
$Temp_111_37 DWORD  ?
$Temp_13_38 DWORD  ?
$Temp_14_39 DWORD  ?
CONST_166 BYTE '-'
$Temp_112_40 DWORD  ?
$Temp_113_42 DWORD  ?
$Temp_16_43 DWORD  ?
CONST_179 BYTE '0'
$Temp_114_44 DWORD  ?
$Temp_18_46 DWORD  ?
cs$_34 BYTE 20 DUP(?)
$Temp_115_48 DWORD  ?
$Temp_20_49 DWORD  ?
$Temp_116_50 DWORD  ?
$Temp_21_51 DWORD  ?
$Temp_117_52 BYTE  ?
$Temp_118_53 DWORD  ?
$Temp_119_54 DWORD  ?
$Temp_120_55 DWORD  ?
$Temp_22_56 DWORD  ?
$Temp_121_58 DWORD  ?
$Temp_122_62 DWORD  ?
minus$_61 DWORD  ?
$Temp_123_64 DWORD  ?
result$_63 DWORD  ?
$Temp_25_65 DWORD  ?
ch$_66 DWORD  ?
$Temp_124_67 DWORD  ?
$Temp_26_68 DWORD  ?
$Temp_125_69 DWORD  ?
$Temp_27_70 DWORD  ?
CONST_266 BYTE '9'
$Temp_126_71 DWORD  ?
$Temp_28_72 DWORD  ?
$Temp_29_73 DWORD  ?
$Temp_30_74 DWORD  ?
$Temp_127_75 DWORD  ?
$Temp_31_76 DWORD  ?
$Temp_128_77 DWORD  ?
$Temp_129_78 DWORD  ?
$Temp_32_79 DWORD  ?
$Temp_33_80 DWORD  ?
$Temp_130_81 DWORD  ?
$Temp_34_82 DWORD  ?
$Temp_131_83 DWORD  ?
$Temp_35_84 DWORD  ?
$Temp_36_85 DWORD  ?
$Temp_132_86 DWORD  ?
$Temp_37_87 DWORD  ?
$Temp_133_88 DWORD  ?
$Temp_38_89 DWORD  ?
$Temp_134_90 DWORD  ?
$Temp_39_91 DWORD  ?
$Temp_135_92 DWORD  ?
$Temp_40_93 DWORD  ?
$return_value_60 DWORD  ?
arr$_94 DWORD ?
n$_95 DWORD ?
$Temp_136_98 DWORD  ?
i$_96 DWORD  ?
$Temp_137_99 DWORD  ?
$Temp_41_100 DWORD  ?
$Temp_138_101 DWORD  ?
$Temp_42_102 DWORD  ?
$Temp_43_103 DWORD  ?
$Temp_139_104 DWORD  ?
j$_97 DWORD  ?
$Temp_44_105 DWORD  ?
$Temp_140_106 DWORD  ?
$Temp_45_107 DWORD  ?
$Temp_141_108 DWORD  ?
$Temp_46_109 DWORD  ?
$Temp_47_110 DWORD  ?
$Temp_142_112 DWORD  ?
$Temp_49_113 DWORD  ?
$Temp_51_115 DWORD  ?
tmp$_117 DWORD  ?
$Temp_143_119 DWORD  ?
$Temp_54_120 DWORD  ?
$Temp_144_122 DWORD  ?
$Temp_56_123 DWORD  ?
arr$_125 DWORD ?
size$_126 DWORD ?
$Temp_145_128 DWORD  ?
i$_127 DWORD  ?
$Temp_58_129 DWORD  ?
$Temp_59_130 DWORD  ?
$Temp_146_133 DWORD  ?
arr$_136 DWORD ?
n$_137 DWORD ?
$Temp_147_140 DWORD  ?
sum$_139 DWORD  ?
$Temp_148_141 DWORD  ?
i$_138 DWORD  ?
$Temp_63_142 DWORD  ?
$Temp_149_144 DWORD  ?
$return_value_135 DWORD  ?
CONST_576 BYTE "Input size:",0
$Temp_66_156 DWORD  ?
sz$_150 DWORD  ?
$Temp_150_158 DWORD  ?
CONST_598 BYTE "Input ",0
CONST_608 BYTE " integers:",0
$Temp_151_163 DWORD  ?
i$_157 DWORD  ?
$Temp_71_164 DWORD  ?
$Temp_72_165 DWORD  ?
arr$_151 DWORD 1000 DUP(?)
$Temp_74_167 DWORD  ?
CONST_644 BYTE "Array after sort():",0
$Temp_152_171 DWORD  ?
CONST_661 BYTE "Array sum:",0
$Temp_80_174 DWORD  ?
$Temp_153_176 DWORD  ?
CONST_687 BYTE "Test struct",0
my$_154 my_struct$  <>
$Temp_86_181 DWORD  ?
$Temp_88_183 DWORD  ?
$Temp_90_185 DWORD  ?
$Temp_154_188 DWORD  ?
$Temp_155_192 DWORD  ?
$Temp_156_196 DWORD  ?
$Temp_157_198 DWORD  ?
$return_value_149 DWORD  ?

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
mov $Temp_100_5,eax
mov eax,$Temp_100_5
mov cur$_4,eax
jmp LABEL_3
LABEL_0:nop
xor eax,eax
mov esi,cur$_4
mov ebx,[str$_3]
mov al,byte ptr [ebx+1*esi]
mov $Temp_101_7,eax
mov eax,$Temp_101_7
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
mov $Temp_102_11,eax
mov eax,$Temp_102_11
mov i$_2,eax
call putchar$
jmp LABEL_1
LABEL_2:nop
ret
print_str$ ENDP
read_str$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_103_17,eax
mov eax,$Temp_103_17
mov i$_16,eax
LABEL_4:nop
xor eax,eax
mov eax,n$_15
mov $Temp_104_18,eax
mov eax,$Temp_104_18
sub eax,CONST_86
mov $Temp_5_19,eax
xor eax,eax
mov eax,i$_16
mov $Temp_105_20,eax
mov eax,$Temp_105_20
sub eax,$Temp_5_19
shr eax,31
mov $Temp_6_21,eax
mov eax,$Temp_6_21
and eax,eax
jz LABEL_5
call getchar$
mov eax,$return_value_0
mov $Temp_7_22,eax
mov eax,$Temp_7_22
mov n$_15,eax
xor eax,eax
mov eax,n$_15
mov $Temp_106_24,eax
mov eax,CONST_102
sub eax,$Temp_106_24
mov $Temp_8_25,eax
mov eax,$Temp_8_25
and eax,eax
jnz LABEL_7
jmp LABEL_6
LABEL_7:nop
xor eax,eax
mov al,CONST_107
mov $Temp_107_26,eax
mov eax,$Temp_107_26
sub eax,n$_15
mov $Temp_9_27,eax
mov eax,$Temp_9_27
and eax,eax
jnz LABEL_8
jmp LABEL_6
LABEL_8:nop
mov eax,i$_16
mov $Temp_10_28,eax
inc i$_16
xor eax,eax
mov eax,n$_15
mov $Temp_108_30,al
mov al,$Temp_108_30
mov esi,$Temp_10_28
mov ebx,[str$_14]
mov byte ptr [ebx+1*esi],al
LABEL_6:nop
jmp LABEL_4
LABEL_5:nop
xor eax,eax
mov eax,CONST_42
mov $Temp_109_32,al
mov al,$Temp_109_32
mov esi,i$_16
mov ebx,[str$_14]
mov byte ptr [ebx+1*esi],al
mov eax,i$_16
mov $return_value_13,eax
ret
read_str$ ENDP
print_int$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_110_36,eax
mov eax,$Temp_110_36
mov cnt$_35,eax
xor eax,eax
mov eax,i$_33
mov $Temp_111_37,eax
mov eax,$Temp_111_37
sub eax,CONST_42
shr eax,31
mov $Temp_13_38,eax
mov eax,$Temp_13_38
and eax,eax
jz LABEL_9
mov eax,i$_33
neg eax
mov $Temp_14_39,eax
mov eax,$Temp_14_39
mov i$_33,eax
xor eax,eax
mov al,CONST_166
mov $Temp_112_40,eax
mov eax,$Temp_112_40
mov i$_2,eax
call putchar$
jmp LABEL_10
LABEL_9:nop
LABEL_10:nop
xor eax,eax
mov eax,i$_33
mov $Temp_113_42,eax
mov eax,$Temp_113_42
sub eax,CONST_42

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_16_43,eax
mov eax,$Temp_16_43
and eax,eax
jz LABEL_11
xor eax,eax
mov al,CONST_179
mov $Temp_114_44,eax
mov eax,$Temp_114_44
mov i$_2,eax
call putchar$
jmp LABEL_12
LABEL_11:nop
LABEL_12:nop
LABEL_13:nop
mov eax,i$_33
and eax,eax
jz LABEL_14
mov eax,cnt$_35
mov $Temp_18_46,eax
inc cnt$_35
xor eax,eax
mov eax,i$_33
mov $Temp_115_48,eax

mov eax,$Temp_115_48
cdq
mov ecx,CONST_102
idiv ecx
mov $Temp_20_49,edx
xor eax,eax
mov al,CONST_179
mov $Temp_116_50,eax
mov eax,$Temp_20_49
add eax,$Temp_116_50
mov $Temp_21_51,eax
xor eax,eax
mov eax,$Temp_21_51
mov $Temp_117_52,al
mov al,$Temp_117_52
mov esi,$Temp_18_46
mov byte ptr cs$_34[1*esi],al
xor eax,eax
mov eax,CONST_102
mov $Temp_118_53,eax
mov eax,i$_33
cdq
idiv $Temp_118_53
mov $Temp_119_54,eax
mov eax,$Temp_119_54
mov i$_33,eax
jmp LABEL_13
LABEL_14:nop
LABEL_15:nop
xor eax,eax
mov eax,cnt$_35
mov $Temp_120_55,eax
mov eax,$Temp_120_55
sub eax,CONST_42
shr eax,31
xor eax,1
mov $Temp_22_56,eax
mov eax,$Temp_22_56
and eax,eax
jz LABEL_16
dec cnt$_35
xor eax,eax
mov esi,cnt$_35
mov al,byte ptr cs$_34[1*esi]
mov $Temp_121_58,eax
mov eax,$Temp_121_58
mov i$_2,eax
call putchar$
jmp LABEL_15
LABEL_16:nop
ret
print_int$ ENDP
read_int$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_122_62,eax
mov eax,$Temp_122_62
mov minus$_61,eax
xor eax,eax
mov eax,CONST_42
mov $Temp_123_64,eax
mov eax,$Temp_123_64
mov result$_63,eax
call getchar$
mov eax,$return_value_0
mov $Temp_25_65,eax
mov eax,$Temp_25_65
mov ch$_66,eax
LABEL_17:nop
mov eax,CONST_86
and eax,eax
jz LABEL_18
xor eax,eax
mov al,CONST_166
mov $Temp_124_67,eax
mov eax,ch$_66
sub eax,$Temp_124_67

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_26_68,eax
mov eax,$Temp_26_68
and eax,eax
jz LABEL_19
jmp LABEL_18
jmp LABEL_20
LABEL_19:nop
LABEL_20:nop
xor eax,eax
mov al,CONST_179
mov $Temp_125_69,eax
mov eax,ch$_66
sub eax,$Temp_125_69
shr eax,31
xor eax,1
mov $Temp_27_70,eax
xor eax,eax
mov al,CONST_266
mov $Temp_126_71,eax
mov eax,$Temp_126_71
sub eax,ch$_66
shr eax,31
xor eax,1
mov $Temp_28_72,eax
mov eax,$Temp_28_72
mov ebx,$Temp_27_70

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
			mov $Temp_29_73,ecx
mov eax,$Temp_29_73
and eax,eax
jz LABEL_21
jmp LABEL_18
jmp LABEL_22
LABEL_21:nop
LABEL_22:nop
call getchar$
mov eax,$return_value_0
mov $Temp_30_74,eax
mov eax,$Temp_30_74
mov ch$_66,eax
jmp LABEL_17
LABEL_18:nop
xor eax,eax
mov al,CONST_166
mov $Temp_127_75,eax
mov eax,ch$_66
sub eax,$Temp_127_75

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_31_76,eax
mov eax,$Temp_31_76
and eax,eax
jz LABEL_23
xor eax,eax
mov eax,CONST_86
mov $Temp_128_77,eax
mov eax,$Temp_128_77
mov minus$_61,eax
jmp LABEL_24
LABEL_23:nop
xor eax,eax
mov al,CONST_179
mov $Temp_129_78,eax
mov eax,ch$_66
sub eax,$Temp_129_78
mov $Temp_32_79,eax
mov eax,$Temp_32_79
mov result$_63,eax
LABEL_24:nop
LABEL_25:nop
mov eax,CONST_86
and eax,eax
jz LABEL_26
call getchar$
mov eax,$return_value_0
mov $Temp_33_80,eax
mov eax,$Temp_33_80
mov ch$_66,eax
xor eax,eax
mov al,CONST_179
mov $Temp_130_81,eax
mov eax,ch$_66
sub eax,$Temp_130_81
shr eax,31
mov $Temp_34_82,eax
xor eax,eax
mov al,CONST_266
mov $Temp_131_83,eax
mov eax,$Temp_131_83
sub eax,ch$_66
shr eax,31
mov $Temp_35_84,eax
mov eax,$Temp_35_84
or eax,$Temp_34_82

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
xor eax,1
			mov $Temp_36_85,eax
mov eax,$Temp_36_85
and eax,eax
jz LABEL_27
jmp LABEL_26
jmp LABEL_28
LABEL_27:nop
LABEL_28:nop
xor eax,eax
mov eax,result$_63
mov $Temp_132_86,eax
mov eax,$Temp_132_86
imul eax,CONST_102
mov $Temp_37_87,eax
xor eax,eax
mov al,CONST_179
mov $Temp_133_88,eax
mov eax,ch$_66
sub eax,$Temp_133_88
mov $Temp_38_89,eax
xor eax,eax
mov eax,$Temp_38_89
mov $Temp_134_90,eax
mov eax,$Temp_37_87
add eax,$Temp_134_90
mov $Temp_39_91,eax
xor eax,eax
mov eax,$Temp_39_91
mov $Temp_135_92,eax
mov eax,$Temp_135_92
mov result$_63,eax
jmp LABEL_25
LABEL_26:nop
mov eax,minus$_61
and eax,eax
jz LABEL_29
mov eax,result$_63
neg eax
mov $Temp_40_93,eax
mov eax,$Temp_40_93
mov $return_value_60,eax
ret
jmp LABEL_30
LABEL_29:nop
mov eax,result$_63
mov $return_value_60,eax
ret
LABEL_30:nop
read_int$ ENDP
bubbleSort$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_136_98,eax
mov eax,$Temp_136_98
mov i$_96,eax
jmp LABEL_34
LABEL_31:nop
xor eax,eax
mov eax,n$_95
mov $Temp_137_99,eax
mov eax,$Temp_137_99
sub eax,CONST_86
mov $Temp_41_100,eax
xor eax,eax
mov eax,i$_96
mov $Temp_138_101,eax
mov eax,$Temp_138_101
sub eax,$Temp_41_100
shr eax,31
mov $Temp_42_102,eax
mov eax,$Temp_42_102
and eax,eax
jnz LABEL_34
mov eax,$Temp_42_102
and eax,eax
jz LABEL_33
LABEL_32:nop
mov eax,i$_96
mov $Temp_43_103,eax
inc i$_96
jmp LABEL_31
LABEL_34:nop
xor eax,eax
mov eax,CONST_42
mov $Temp_139_104,eax
mov eax,$Temp_139_104
mov j$_97,eax
jmp LABEL_38
LABEL_35:nop
mov eax,n$_95
sub eax,i$_96
mov $Temp_44_105,eax
xor eax,eax
mov eax,$Temp_44_105
mov $Temp_140_106,eax
mov eax,$Temp_140_106
sub eax,CONST_86
mov $Temp_45_107,eax
xor eax,eax
mov eax,j$_97
mov $Temp_141_108,eax
mov eax,$Temp_141_108
sub eax,$Temp_45_107
shr eax,31
mov $Temp_46_109,eax
mov eax,$Temp_46_109
and eax,eax
jnz LABEL_38
mov eax,$Temp_46_109
and eax,eax
jz LABEL_37
LABEL_36:nop
mov eax,j$_97
mov $Temp_47_110,eax
inc j$_97
jmp LABEL_35
LABEL_38:nop
xor eax,eax
mov eax,j$_97
mov $Temp_142_112,eax
mov eax,$Temp_142_112
add eax,CONST_86
mov $Temp_49_113,eax
mov esi,$Temp_49_113
mov ebx,[arr$_94]
mov eax,dword ptr [ebx+4*esi]
mov esi,j$_97
mov ebx,[arr$_94]
sub eax,dword ptr [ebx+4*esi]
shr eax,31
mov $Temp_51_115,eax
mov eax,$Temp_51_115
and eax,eax
jz LABEL_39
mov esi,j$_97
mov ebx,[arr$_94]
mov eax,dword ptr [ebx+4*esi]
mov tmp$_117,eax
xor eax,eax
mov eax,j$_97
mov $Temp_143_119,eax
mov eax,$Temp_143_119
add eax,CONST_86
mov $Temp_54_120,eax
mov esi,$Temp_54_120
mov ebx,[arr$_94]
mov eax,dword ptr [ebx+4*esi]
mov esi,j$_97
mov ebx,[arr$_94]
mov dword ptr [ebx+4*esi],eax
xor eax,eax
mov eax,j$_97
mov $Temp_144_122,eax
mov eax,$Temp_144_122
add eax,CONST_86
mov $Temp_56_123,eax
mov eax,tmp$_117
mov esi,$Temp_56_123
mov ebx,[arr$_94]
mov dword ptr [ebx+4*esi],eax
jmp LABEL_40
LABEL_39:nop
LABEL_40:nop
jmp LABEL_36
LABEL_37:nop
jmp LABEL_32
LABEL_33:nop
ret
bubbleSort$ ENDP
printArray$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_145_128,eax
mov eax,$Temp_145_128
mov i$_127,eax
jmp LABEL_44
LABEL_41:nop
mov eax,i$_127
sub eax,size$_126
shr eax,31
mov $Temp_58_129,eax
mov eax,$Temp_58_129
and eax,eax
jnz LABEL_44
mov eax,$Temp_58_129
and eax,eax
jz LABEL_43
LABEL_42:nop
mov eax,i$_127
mov $Temp_59_130,eax
inc i$_127
jmp LABEL_41
LABEL_44:nop
mov esi,i$_127
mov ebx,[arr$_125]
mov eax,dword ptr [ebx+4*esi]
mov i$_33,eax
call print_int$
xor eax,eax
mov al,CONST_107
mov $Temp_146_133,eax
mov eax,$Temp_146_133
mov i$_2,eax
call putchar$
jmp LABEL_42
LABEL_43:nop
ret
printArray$ ENDP
get_sum$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_147_140,eax
mov eax,$Temp_147_140
mov sum$_139,eax
xor eax,eax
mov eax,CONST_42
mov $Temp_148_141,eax
mov eax,$Temp_148_141
mov i$_138,eax
jmp LABEL_48
LABEL_45:nop
mov eax,i$_138
sub eax,n$_137
shr eax,31
mov $Temp_63_142,eax
mov eax,$Temp_63_142
and eax,eax
jnz LABEL_48
mov eax,$Temp_63_142
and eax,eax
jz LABEL_47
LABEL_46:nop
inc i$_138
jmp LABEL_45
LABEL_48:nop
mov eax,sum$_139
mov esi,i$_138
mov ebx,[arr$_136]
add eax,dword ptr [ebx+4*esi]
mov $Temp_149_144,eax
mov eax,$Temp_149_144
mov sum$_139,eax
jmp LABEL_46
LABEL_47:nop
mov eax,sum$_139
mov $return_value_135,eax
ret
get_sum$ ENDP
main PROC
mov eax,offset CONST_576
mov str$_3,eax
call print_str$
LABEL_49:nop
call read_int$
mov eax,$return_value_60
mov $Temp_66_156,eax
mov eax,$Temp_66_156
mov sz$_150,eax
mov eax,sz$_150
and eax,eax
jz LABEL_50
xor eax,eax
mov eax,CONST_102
mov $Temp_150_158,eax
mov eax,$Temp_150_158
mov i$_2,eax
call putchar$
mov eax,offset CONST_598
mov str$_3,eax
call print_str$
mov eax,sz$_150
mov i$_33,eax
call print_int$
mov eax,offset CONST_608
mov str$_3,eax
call print_str$
xor eax,eax
mov eax,CONST_42
mov $Temp_151_163,eax
mov eax,$Temp_151_163
mov i$_157,eax
jmp LABEL_54
LABEL_51:nop
mov eax,i$_157
sub eax,sz$_150
shr eax,31
mov $Temp_71_164,eax
mov eax,$Temp_71_164
and eax,eax
jnz LABEL_54
mov eax,$Temp_71_164
and eax,eax
jz LABEL_53
LABEL_52:nop
mov eax,i$_157
mov $Temp_72_165,eax
inc i$_157
jmp LABEL_51
LABEL_54:nop
call read_int$
mov eax,$return_value_60
mov $Temp_74_167,eax
mov eax,$Temp_74_167
mov esi,i$_157
mov dword ptr arr$_151[4*esi],eax
jmp LABEL_52
LABEL_53:nop
mov eax,offset arr$_151
mov arr$_94,eax
mov eax,sz$_150
mov n$_95,eax
call bubbleSort$
mov eax,offset CONST_644
mov str$_3,eax
call print_str$
mov eax,offset arr$_151
mov arr$_125,eax
mov eax,sz$_150
mov size$_126,eax
call printArray$
xor eax,eax
mov eax,CONST_102
mov $Temp_152_171,eax
mov eax,$Temp_152_171
mov i$_2,eax
call putchar$
mov eax,offset CONST_661
mov str$_3,eax
call print_str$
mov eax,offset arr$_151
mov arr$_136,eax
mov eax,sz$_150
mov n$_137,eax
call get_sum$
mov eax,$return_value_135
mov $Temp_80_174,eax
mov eax,$Temp_80_174
mov i$_33,eax
call print_int$
xor eax,eax
mov eax,CONST_102
mov $Temp_153_176,eax
mov eax,$Temp_153_176
mov i$_2,eax
call putchar$
mov eax,offset CONST_576
mov str$_3,eax
call print_str$
jmp LABEL_49
LABEL_50:nop
mov eax,offset CONST_687
mov str$_3,eax
call print_str$
call read_int$
mov eax,$return_value_60
mov $Temp_86_181,eax
mov eax,$Temp_86_181
mov my$_154.a$,eax
call read_int$
mov eax,$return_value_60
mov $Temp_88_183,eax
mov eax,$Temp_88_183
mov my$_154.b$,eax
call read_int$
mov eax,$return_value_60
mov $Temp_90_185,eax
mov eax,$Temp_90_185
mov my$_154.c$,eax
mov eax,my$_154.a$
mov i$_33,eax
call print_int$
xor eax,eax
mov eax,CONST_102
mov $Temp_154_188,eax
mov eax,$Temp_154_188
mov i$_2,eax
call putchar$
mov eax,my$_154.b$
mov i$_33,eax
call print_int$
xor eax,eax
mov eax,CONST_102
mov $Temp_155_192,eax
mov eax,$Temp_155_192
mov i$_2,eax
call putchar$
mov eax,my$_154.c$
mov i$_33,eax
call print_int$
xor eax,eax
mov eax,CONST_102
mov $Temp_156_196,eax
mov eax,$Temp_156_196
mov i$_2,eax
call putchar$
xor eax,eax
mov eax,CONST_42
mov $Temp_157_198,eax
mov eax,CONST_42
mov $return_value_149,eax
ret
main ENDP

END main
		