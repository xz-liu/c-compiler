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
$Temp_63_5 DWORD  ?
cur$_4 DWORD  ?
$Temp_64_7 DWORD  ?
$Temp_1_8 DWORD  ?
$Temp_2_9 DWORD  ?
$Temp_65_11 DWORD  ?
i$_13 DWORD ?
$Temp_66_16 DWORD  ?
cnt$_15 DWORD  ?
$Temp_67_17 DWORD  ?
$Temp_5_18 DWORD  ?
$Temp_6_19 DWORD  ?
CONST_97 BYTE '-'
$Temp_68_20 DWORD  ?
$Temp_69_22 DWORD  ?
$Temp_8_23 DWORD  ?
CONST_110 BYTE '0'
$Temp_70_24 DWORD  ?
$Temp_10_26 DWORD  ?
cs$_14 BYTE 20 DUP(?)
$Temp_71_28 DWORD  ?
CONST_127 DWORD 10
$Temp_12_29 DWORD  ?
$Temp_72_30 DWORD  ?
$Temp_13_31 DWORD  ?
$Temp_73_32 BYTE  ?
$Temp_74_33 DWORD  ?
$Temp_75_34 DWORD  ?
$Temp_76_35 DWORD  ?
$Temp_14_36 DWORD  ?
$Temp_77_38 DWORD  ?
$Temp_78_42 DWORD  ?
minus$_41 DWORD  ?
$Temp_79_44 DWORD  ?
result$_43 DWORD  ?
$Temp_17_45 DWORD  ?
ch$_46 DWORD  ?
CONST_178 DWORD 1
$Temp_80_47 DWORD  ?
$Temp_18_48 DWORD  ?
$Temp_81_49 DWORD  ?
$Temp_19_50 DWORD  ?
CONST_197 BYTE '9'
$Temp_82_51 DWORD  ?
$Temp_20_52 DWORD  ?
$Temp_21_53 DWORD  ?
$Temp_22_54 DWORD  ?
$Temp_83_55 DWORD  ?
$Temp_23_56 DWORD  ?
$Temp_84_57 DWORD  ?
$Temp_85_58 DWORD  ?
$Temp_24_59 DWORD  ?
$Temp_25_60 DWORD  ?
$Temp_86_61 DWORD  ?
$Temp_26_62 DWORD  ?
$Temp_87_63 DWORD  ?
$Temp_27_64 DWORD  ?
$Temp_28_65 DWORD  ?
$Temp_88_66 DWORD  ?
$Temp_29_67 DWORD  ?
$Temp_89_68 DWORD  ?
$Temp_30_69 DWORD  ?
$Temp_90_70 DWORD  ?
$Temp_31_71 DWORD  ?
$Temp_91_72 DWORD  ?
$Temp_32_73 DWORD  ?
$return_value_40 DWORD  ?
arr$_74 DWORD ?
n$_75 DWORD ?
$Temp_92_78 DWORD  ?
i$_76 DWORD  ?
$Temp_93_79 DWORD  ?
$Temp_33_80 DWORD  ?
$Temp_94_81 DWORD  ?
$Temp_34_82 DWORD  ?
$Temp_35_83 DWORD  ?
$Temp_95_84 DWORD  ?
j$_77 DWORD  ?
$Temp_36_85 DWORD  ?
$Temp_96_86 DWORD  ?
$Temp_37_87 DWORD  ?
$Temp_97_88 DWORD  ?
$Temp_38_89 DWORD  ?
$Temp_39_90 DWORD  ?
$Temp_98_92 DWORD  ?
$Temp_41_93 DWORD  ?
$Temp_43_95 DWORD  ?
tmp$_97 DWORD  ?
$Temp_99_99 DWORD  ?
$Temp_46_100 DWORD  ?
$Temp_100_102 DWORD  ?
$Temp_48_103 DWORD  ?
arr$_105 DWORD ?
size$_106 DWORD ?
$Temp_101_108 DWORD  ?
i$_107 DWORD  ?
$Temp_50_109 DWORD  ?
$Temp_51_110 DWORD  ?
CONST_408 BYTE ' '
$Temp_102_113 DWORD  ?
$Temp_103_120 DWORD  ?
sz$_119 DWORD  ?
CONST_446 BYTE "Input 10 integers:",0
$Temp_104_124 DWORD  ?
i$_122 DWORD  ?
$Temp_56_125 DWORD  ?
$Temp_57_126 DWORD  ?
arr$_121 DWORD 10 DUP(?)
$Temp_59_128 DWORD  ?
CONST_482 BYTE "Array after sort():",0

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
mov $Temp_63_5,eax
mov eax,$Temp_63_5
mov cur$_4,eax
jmp LABEL_3
LABEL_0:nop
xor eax,eax
mov esi,cur$_4
mov ebx,[str$_3]
mov al,byte ptr [ebx+1*esi]
mov $Temp_64_7,eax
mov eax,$Temp_64_7
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
mov $Temp_65_11,eax
mov eax,$Temp_65_11
mov i$_2,eax
call putchar$
jmp LABEL_1
LABEL_2:nop
ret
print_str$ ENDP
print_int$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_66_16,eax
mov eax,$Temp_66_16
mov cnt$_15,eax
xor eax,eax
mov eax,i$_13
mov $Temp_67_17,eax
mov eax,$Temp_67_17
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
mov $Temp_68_20,eax
mov eax,$Temp_68_20
mov i$_2,eax
call putchar$
jmp LABEL_5
LABEL_4:nop
LABEL_5:nop
xor eax,eax
mov eax,i$_13
mov $Temp_69_22,eax
mov eax,$Temp_69_22
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
mov $Temp_70_24,eax
mov eax,$Temp_70_24
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
mov $Temp_71_28,eax

mov eax,$Temp_71_28
cdq
mov ecx,CONST_127
idiv ecx
mov $Temp_12_29,edx
xor eax,eax
mov al,CONST_110
mov $Temp_72_30,eax
mov eax,$Temp_12_29
add eax,$Temp_72_30
mov $Temp_13_31,eax
xor eax,eax
mov eax,$Temp_13_31
mov $Temp_73_32,al
mov al,$Temp_73_32
mov esi,$Temp_10_26
mov byte ptr cs$_14[1*esi],al
xor eax,eax
mov eax,CONST_127
mov $Temp_74_33,eax
mov eax,i$_13
cdq
idiv $Temp_74_33
mov $Temp_75_34,eax
mov eax,$Temp_75_34
mov i$_13,eax
jmp LABEL_8
LABEL_9:nop
LABEL_10:nop
xor eax,eax
mov eax,cnt$_15
mov $Temp_76_35,eax
mov eax,$Temp_76_35
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
mov $Temp_77_38,eax
mov eax,$Temp_77_38
mov i$_2,eax
call putchar$
jmp LABEL_10
LABEL_11:nop
ret
print_int$ ENDP
read_int$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_78_42,eax
mov eax,$Temp_78_42
mov minus$_41,eax
xor eax,eax
mov eax,CONST_42
mov $Temp_79_44,eax
mov eax,$Temp_79_44
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
mov $Temp_80_47,eax
mov eax,ch$_46
sub eax,$Temp_80_47

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
mov $Temp_81_49,eax
mov eax,ch$_46
sub eax,$Temp_81_49
shr eax,31
xor eax,1
mov $Temp_19_50,eax
xor eax,eax
mov al,CONST_197
mov $Temp_82_51,eax
mov eax,$Temp_82_51
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
mov $Temp_83_55,eax
mov eax,ch$_46
sub eax,$Temp_83_55

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
mov $Temp_84_57,eax
mov eax,$Temp_84_57
mov minus$_41,eax
jmp LABEL_19
LABEL_18:nop
xor eax,eax
mov al,CONST_110
mov $Temp_85_58,eax
mov eax,ch$_46
sub eax,$Temp_85_58
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
mov $Temp_86_61,eax
mov eax,ch$_46
sub eax,$Temp_86_61
shr eax,31
mov $Temp_26_62,eax
xor eax,eax
mov al,CONST_197
mov $Temp_87_63,eax
mov eax,$Temp_87_63
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
mov $Temp_88_66,eax
mov eax,$Temp_88_66
imul eax,CONST_127
mov $Temp_29_67,eax
xor eax,eax
mov al,CONST_110
mov $Temp_89_68,eax
mov eax,ch$_46
sub eax,$Temp_89_68
mov $Temp_30_69,eax
xor eax,eax
mov eax,$Temp_30_69
mov $Temp_90_70,eax
mov eax,$Temp_29_67
add eax,$Temp_90_70
mov $Temp_31_71,eax
xor eax,eax
mov eax,$Temp_31_71
mov $Temp_91_72,eax
mov eax,$Temp_91_72
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
bubbleSort$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_92_78,eax
mov eax,$Temp_92_78
mov i$_76,eax
jmp LABEL_29
LABEL_26:nop
xor eax,eax
mov eax,n$_75
mov $Temp_93_79,eax
mov eax,$Temp_93_79
sub eax,CONST_178
mov $Temp_33_80,eax
xor eax,eax
mov eax,i$_76
mov $Temp_94_81,eax
mov eax,$Temp_94_81
sub eax,$Temp_33_80
shr eax,31
mov $Temp_34_82,eax
mov eax,$Temp_34_82
and eax,eax
jnz LABEL_29
mov eax,$Temp_34_82
and eax,eax
jz LABEL_28
LABEL_27:nop
mov eax,i$_76
mov $Temp_35_83,eax
inc i$_76
jmp LABEL_26
LABEL_29:nop
xor eax,eax
mov eax,CONST_42
mov $Temp_95_84,eax
mov eax,$Temp_95_84
mov j$_77,eax
jmp LABEL_33
LABEL_30:nop
mov eax,n$_75
sub eax,i$_76
mov $Temp_36_85,eax
xor eax,eax
mov eax,$Temp_36_85
mov $Temp_96_86,eax
mov eax,$Temp_96_86
sub eax,CONST_178
mov $Temp_37_87,eax
xor eax,eax
mov eax,j$_77
mov $Temp_97_88,eax
mov eax,$Temp_97_88
sub eax,$Temp_37_87
shr eax,31
mov $Temp_38_89,eax
mov eax,$Temp_38_89
and eax,eax
jnz LABEL_33
mov eax,$Temp_38_89
and eax,eax
jz LABEL_32
LABEL_31:nop
mov eax,j$_77
mov $Temp_39_90,eax
inc j$_77
jmp LABEL_30
LABEL_33:nop
xor eax,eax
mov eax,j$_77
mov $Temp_98_92,eax
mov eax,$Temp_98_92
add eax,CONST_178
mov $Temp_41_93,eax
mov esi,$Temp_41_93
mov ebx,[arr$_74]
mov eax,dword ptr [ebx+4*esi]
mov esi,j$_77
mov ebx,[arr$_74]
sub eax,dword ptr [ebx+4*esi]
shr eax,31
mov $Temp_43_95,eax
mov eax,$Temp_43_95
and eax,eax
jz LABEL_34
mov esi,j$_77
mov ebx,[arr$_74]
mov eax,dword ptr [ebx+4*esi]
mov tmp$_97,eax
xor eax,eax
mov eax,j$_77
mov $Temp_99_99,eax
mov eax,$Temp_99_99
add eax,CONST_178
mov $Temp_46_100,eax
mov esi,$Temp_46_100
mov ebx,[arr$_74]
mov eax,dword ptr [ebx+4*esi]
mov esi,j$_77
mov ebx,[arr$_74]
mov dword ptr [ebx+4*esi],eax
xor eax,eax
mov eax,j$_77
mov $Temp_100_102,eax
mov eax,$Temp_100_102
add eax,CONST_178
mov $Temp_48_103,eax
mov eax,tmp$_97
mov esi,$Temp_48_103
mov ebx,[arr$_74]
mov dword ptr [ebx+4*esi],eax
jmp LABEL_35
LABEL_34:nop
LABEL_35:nop
jmp LABEL_31
LABEL_32:nop
jmp LABEL_27
LABEL_28:nop
ret
bubbleSort$ ENDP
printArray$ PROC
xor eax,eax
mov eax,CONST_42
mov $Temp_101_108,eax
mov eax,$Temp_101_108
mov i$_107,eax
jmp LABEL_39
LABEL_36:nop
mov eax,i$_107
sub eax,size$_106
shr eax,31
mov $Temp_50_109,eax
mov eax,$Temp_50_109
and eax,eax
jnz LABEL_39
mov eax,$Temp_50_109
and eax,eax
jz LABEL_38
LABEL_37:nop
mov eax,i$_107
mov $Temp_51_110,eax
inc i$_107
jmp LABEL_36
LABEL_39:nop
mov esi,i$_107
mov ebx,[arr$_105]
mov eax,dword ptr [ebx+4*esi]
mov i$_13,eax
call print_int$
xor eax,eax
mov al,CONST_408
mov $Temp_102_113,eax
mov eax,$Temp_102_113
mov i$_2,eax
call putchar$
jmp LABEL_37
LABEL_38:nop
ret
printArray$ ENDP
main PROC
xor eax,eax
mov eax,CONST_127
mov $Temp_103_120,eax
mov eax,$Temp_103_120
mov sz$_119,eax
mov eax,offset CONST_446
mov str$_3,eax
call print_str$
xor eax,eax
mov eax,CONST_42
mov $Temp_104_124,eax
mov eax,$Temp_104_124
mov i$_122,eax
jmp LABEL_43
LABEL_40:nop
mov eax,i$_122
sub eax,sz$_119
shr eax,31
mov $Temp_56_125,eax
mov eax,$Temp_56_125
and eax,eax
jnz LABEL_43
mov eax,$Temp_56_125
and eax,eax
jz LABEL_42
LABEL_41:nop
mov eax,i$_122
mov $Temp_57_126,eax
inc i$_122
jmp LABEL_40
LABEL_43:nop
call read_int$
mov eax,$return_value_40
mov $Temp_59_128,eax
mov eax,$Temp_59_128
mov esi,i$_122
mov dword ptr arr$_121[4*esi],eax
jmp LABEL_41
LABEL_42:nop
mov eax,offset arr$_121
mov arr$_74,eax
mov eax,sz$_119
mov n$_75,eax
call bubbleSort$
mov eax,offset CONST_482
mov str$_3,eax
call print_str$
mov eax,offset arr$_121
mov arr$_105,eax
mov eax,sz$_119
mov size$_106,eax
call printArray$
ret
main ENDP

END main
		