includelib kernel32.lib  
.model flat,stdcall 
	
option casemap :none
 
includelib kernel32.lib
includelib masm32.lib
 
ExitProcess PROTO STDCALL:DWORD
StdOut		PROTO STDCALL:DWORD

test_struct$ STRUCT
a$ DWORD  ?
b$ DWORD  ?
c$ DWORD  ?
test_struct$ ENDS
.data
i$_1 DWORD  ?
$return_value_0 DWORD  ?
i$_2 DWORD ?
str$_6 DWORD ?
CONST_54 DWORD 0
$Temp_59_8 DWORD  ?
cur$_7 DWORD  ?
$Temp_60_10 DWORD  ?
$Temp_1_11 DWORD  ?
$Temp_2_12 DWORD  ?
$Temp_61_14 DWORD  ?
$Temp_62_18 DWORD  ?
cur$_17 DWORD  ?
$Temp_63_19 DWORD  ?
CONST_85 DWORD 20
$Temp_5_20 DWORD  ?
$Temp_6_21 DWORD  ?
str$_16 BYTE 20 DUP(?)
CONST_110 BYTE '0'
$Temp_64_23 DWORD  ?
$Temp_8_24 DWORD  ?
$Temp_65_25 BYTE  ?
$Temp_66_27 DWORD  ?
i$_29 DWORD ?
$Temp_67_32 DWORD  ?
cnt$_31 DWORD  ?
$Temp_68_33 DWORD  ?
$Temp_11_34 DWORD  ?
$Temp_12_35 DWORD  ?
CONST_156 BYTE '-'
$Temp_69_36 DWORD  ?
$Temp_70_38 DWORD  ?
$Temp_14_39 DWORD  ?
$Temp_71_40 DWORD  ?
$Temp_16_42 DWORD  ?
cs$_30 BYTE 20 DUP(?)
$Temp_72_44 DWORD  ?
CONST_186 DWORD 10
$Temp_18_45 DWORD  ?
$Temp_73_46 DWORD  ?
$Temp_19_47 DWORD  ?
$Temp_74_48 BYTE  ?
$Temp_75_49 DWORD  ?
$Temp_76_50 DWORD  ?
$Temp_77_51 DWORD  ?
$Temp_20_52 DWORD  ?
$Temp_78_54 DWORD  ?
a$_57 DWORD ?
b$_58 DWORD ?
$Temp_23_59 DWORD  ?
$return_value_56 DWORD  ?
a$_61 DWORD ?
b$_62 DWORD ?
$Temp_24_63 DWORD  ?
$return_value_60 DWORD  ?
CONST_253 DWORD 3
$Temp_79_66 DWORD  ?
a$_65 DWORD  ?
CONST_257 DWORD 5
$Temp_80_68 DWORD  ?
b$_67 DWORD  ?
CONST_264 DWORD 2
$Temp_81_71 DWORD  ?
c$_70 DWORD  ?
$Temp_82_73 DWORD  ?
x$_72 DWORD  ?
CONST_273 DWORD 3.500000
$Temp_83_75 DWORD  ?
f$_74 DWORD  ?
CONST_277 DWORD 3.200000
$Temp_84_77 DWORD  ?
s$_76 DWORD  ?
$Temp_25_82 DWORD  ?
xx$_83 DWORD  ?
$Temp_26_84 DWORD  ?
yy$_85 DWORD  ?
fuck2$_80 DWORD 10 DUP(?)
CONST_324 DWORD 100
$Temp_85_87 DWORD  ?
fuck3$_81 DWORD 10 DUP(?)
CONST_331 DWORD 2000
$Temp_86_89 DWORD  ?
fuck$_79 DWORD 10 DUP(?)
$Temp_32_93 DWORD  ?
ts$_78 test_struct$  <>
CONST_361 DWORD 345678
$Temp_36_97 DWORD  ?
$Temp_87_98 DWORD  ?
CONST_365 BYTE '5'
$Temp_88_99 DWORD  ?
CONST_370 BYTE ' '
$Temp_89_101 DWORD  ?
CONST_375 DWORD 234
$Temp_90_103 DWORD  ?
$Temp_91_105 DWORD  ?
$Temp_40_106 DWORD  ?
$Temp_41_107 DWORD  ?
$Temp_42_108 DWORD  ?
$Temp_92_109 DWORD  ?
i$_69 DWORD  ?
$Temp_93_110 DWORD  ?
$Temp_43_111 DWORD  ?
$Temp_44_112 DWORD  ?
y$_113 DWORD  ?
$Temp_94_114 DWORD  ?
$Temp_95_115 DWORD  ?
$Temp_96_116 DWORD  ?
$Temp_97_119 DWORD  ?
$Temp_98_122 DWORD  ?
$Temp_99_125 DWORD  ?
$Temp_100_129 DWORD  ?
CONST_486 BYTE "fucK!!!!!!!!!!\n",0

.stack 100
.code
getchar$ PROC
xor edx,edx
mov ah,1
int 21h
mov dl,al
mov i$_1,edx
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
mov eax,CONST_54
mov $Temp_59_8,eax
mov eax,$Temp_59_8
mov cur$_7,eax
jmp LABEL_3
LABEL_0:nop
xor eax,eax
mov esi,cur$_7
mov ebx,[str$_6]
mov al,byte ptr [ebx+1*esi]
mov $Temp_60_10,eax
mov eax,$Temp_60_10
sub eax,CONST_54

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
xor eax,1
			mov $Temp_1_11,eax
mov eax,$Temp_1_11
and eax,eax
jnz LABEL_3
mov eax,$Temp_1_11
and eax,eax
jz LABEL_2
LABEL_1:nop
mov eax,cur$_7
mov $Temp_2_12,eax
inc cur$_7
jmp LABEL_0
LABEL_3:nop
xor eax,eax
mov esi,cur$_7
mov ebx,[str$_6]
mov al,byte ptr [ebx+1*esi]
mov $Temp_61_14,eax
mov eax,$Temp_61_14
mov i$_2,eax
call putchar$
jmp LABEL_1
LABEL_2:nop
ret
print_str$ ENDP
print_own_str$ PROC
xor eax,eax
mov eax,CONST_54
mov $Temp_62_18,eax
mov eax,$Temp_62_18
mov cur$_17,eax
jmp LABEL_7
LABEL_4:nop
xor eax,eax
mov eax,cur$_17
mov $Temp_63_19,eax
mov eax,$Temp_63_19
sub eax,CONST_85
shr eax,31
mov $Temp_5_20,eax
mov eax,$Temp_5_20
and eax,eax
jnz LABEL_7
mov eax,$Temp_5_20
and eax,eax
jz LABEL_6
LABEL_5:nop
mov eax,cur$_17
mov $Temp_6_21,eax
inc cur$_17
jmp LABEL_4
LABEL_7:nop
xor eax,eax
mov al,CONST_110
mov $Temp_64_23,eax
mov eax,$Temp_64_23
add eax,cur$_17
mov $Temp_8_24,eax
xor eax,eax
mov eax,$Temp_8_24
mov $Temp_65_25,al
mov al,$Temp_65_25
mov esi,cur$_17
mov byte ptr str$_16[1*esi],al
xor eax,eax
mov esi,cur$_17
mov al,byte ptr str$_16[1*esi]
mov $Temp_66_27,eax
mov eax,$Temp_66_27
mov i$_2,eax
call putchar$
jmp LABEL_5
LABEL_6:nop
ret
print_own_str$ ENDP
print_int$ PROC
xor eax,eax
mov eax,CONST_54
mov $Temp_67_32,eax
mov eax,$Temp_67_32
mov cnt$_31,eax
xor eax,eax
mov eax,i$_29
mov $Temp_68_33,eax
mov eax,$Temp_68_33
sub eax,CONST_54
shr eax,31
mov $Temp_11_34,eax
mov eax,$Temp_11_34
and eax,eax
jz LABEL_8
mov eax,i$_29
neg eax
mov $Temp_12_35,eax
mov eax,$Temp_12_35
mov i$_29,eax
xor eax,eax
mov al,CONST_156
mov $Temp_69_36,eax
mov eax,$Temp_69_36
mov i$_2,eax
call putchar$
jmp LABEL_9
LABEL_8:nop
LABEL_9:nop
xor eax,eax
mov eax,i$_29
mov $Temp_70_38,eax
mov eax,$Temp_70_38
sub eax,CONST_54

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_14_39,eax
mov eax,$Temp_14_39
and eax,eax
jz LABEL_10
xor eax,eax
mov al,CONST_110
mov $Temp_71_40,eax
mov eax,$Temp_71_40
mov i$_2,eax
call putchar$
jmp LABEL_11
LABEL_10:nop
LABEL_11:nop
LABEL_12:nop
mov eax,i$_29
and eax,eax
jz LABEL_13
mov eax,cnt$_31
mov $Temp_16_42,eax
inc cnt$_31
xor eax,eax
mov eax,i$_29
mov $Temp_72_44,eax

mov eax,$Temp_72_44
cdq
mov ecx,CONST_186
idiv ecx
mov $Temp_18_45,edx
xor eax,eax
mov al,CONST_110
mov $Temp_73_46,eax
mov eax,$Temp_18_45
add eax,$Temp_73_46
mov $Temp_19_47,eax
xor eax,eax
mov eax,$Temp_19_47
mov $Temp_74_48,al
mov al,$Temp_74_48
mov esi,$Temp_16_42
mov byte ptr cs$_30[1*esi],al
xor eax,eax
mov eax,CONST_186
mov $Temp_75_49,eax
mov eax,i$_29
cdq
idiv $Temp_75_49
mov $Temp_76_50,eax
mov eax,$Temp_76_50
mov i$_29,eax
jmp LABEL_12
LABEL_13:nop
LABEL_14:nop
xor eax,eax
mov eax,cnt$_31
mov $Temp_77_51,eax
mov eax,$Temp_77_51
sub eax,CONST_54
shr eax,31
xor eax,1
mov $Temp_20_52,eax
mov eax,$Temp_20_52
and eax,eax
jz LABEL_15
dec cnt$_31
xor eax,eax
mov esi,cnt$_31
mov al,byte ptr cs$_30[1*esi]
mov $Temp_78_54,eax
mov eax,$Temp_78_54
mov i$_2,eax
call putchar$
jmp LABEL_14
LABEL_15:nop
ret
print_int$ ENDP
add_two_num$ PROC
mov eax,a$_57
add eax,b$_58
mov $Temp_23_59,eax
mov eax,$Temp_23_59
mov $return_value_56,eax
ret
add_two_num$ ENDP
sub_two_num$ PROC
mov eax,a$_61
sub eax,b$_62
mov $Temp_24_63,eax
mov eax,$Temp_24_63
mov $return_value_60,eax
ret
sub_two_num$ ENDP
main PROC
xor eax,eax
mov eax,CONST_253
mov $Temp_79_66,eax
mov eax,$Temp_79_66
mov a$_65,eax
xor eax,eax
mov eax,CONST_257
mov $Temp_80_68,eax
mov eax,$Temp_80_68
mov b$_67,eax
xor eax,eax
mov eax,CONST_264
mov $Temp_81_71,eax
mov eax,$Temp_81_71
mov c$_70,eax
xor eax,eax
mov eax,CONST_54
mov $Temp_82_73,eax
mov eax,$Temp_82_73
mov x$_72,eax
fild CONST_273
fst $Temp_83_75
mov eax,$Temp_83_75
mov f$_74,eax
fild CONST_277
fst $Temp_84_77
mov eax,$Temp_84_77
mov s$_76,eax
mov eax,a$_65
mov a$_57,eax
mov eax,b$_67
mov b$_58,eax
call add_two_num$
mov eax,$return_value_56
mov $Temp_25_82,eax
mov eax,$Temp_25_82
mov xx$_83,eax
mov eax,a$_65
mov a$_61,eax
mov eax,b$_67
mov b$_62,eax
call sub_two_num$
mov eax,$return_value_60
mov $Temp_26_84,eax
mov eax,$Temp_26_84
mov yy$_85,eax
xor eax,eax
mov eax,CONST_324
mov $Temp_85_87,eax
mov eax,$Temp_85_87
mov esi,b$_67
mov dword ptr fuck2$_80[4*esi],eax
xor eax,eax
mov eax,CONST_331
mov $Temp_86_89,eax
mov eax,$Temp_86_89
mov esi,c$_70
mov dword ptr fuck3$_81[4*esi],eax
mov esi,b$_67
mov eax,dword ptr fuck2$_80[4*esi]
mov esi,c$_70
add eax,dword ptr fuck3$_81[4*esi]
mov $Temp_32_93,eax
mov eax,$Temp_32_93
mov esi,a$_65
mov dword ptr fuck$_79[4*esi],eax
mov eax,CONST_361
neg eax
mov $Temp_36_97,eax
xor eax,eax
mov eax,$Temp_36_97
mov $Temp_87_98,eax
mov eax,$Temp_87_98
mov ts$_78.c$,eax
mov eax,ts$_78.c$
mov ts$_78.b$,eax
mov eax,ts$_78.b$
mov ts$_78.a$,eax
xor eax,eax
mov al,CONST_365
mov $Temp_88_99,eax
mov eax,$Temp_88_99
mov i$_2,eax
call putchar$
xor eax,eax
mov al,CONST_370
mov $Temp_89_101,eax
mov eax,$Temp_89_101
mov i$_2,eax
call putchar$
xor eax,eax
mov eax,CONST_375
mov $Temp_90_103,eax
mov eax,$Temp_90_103
mov i$_29,eax
call print_int$
fld f$_74
fld s$_76
fadd
fst $Temp_91_105
mov eax,$Temp_91_105
mov f$_74,eax
mov eax,b$_67
sub eax,a$_65
shr eax,31
mov $Temp_40_106,eax
mov eax,$Temp_40_106
and eax,eax
jz LABEL_16
mov eax,a$_65
sub eax,b$_67
mov $Temp_41_107,eax
mov eax,$Temp_41_107
mov c$_70,eax
jmp LABEL_17
LABEL_16:nop
mov eax,b$_67
sub eax,a$_65
mov $Temp_42_108,eax
mov eax,$Temp_42_108
mov c$_70,eax
LABEL_17:nop
xor eax,eax
mov eax,CONST_54
mov $Temp_92_109,eax
mov eax,$Temp_92_109
mov i$_69,eax
jmp LABEL_21
LABEL_18:nop
xor eax,eax
mov eax,i$_69
mov $Temp_93_110,eax
mov eax,$Temp_93_110
sub eax,CONST_253
shr eax,31
mov $Temp_43_111,eax
mov eax,$Temp_43_111
and eax,eax
jnz LABEL_21
mov eax,$Temp_43_111
and eax,eax
jz LABEL_20
LABEL_19:nop
mov eax,i$_69
mov $Temp_44_112,eax
inc i$_69
jmp LABEL_18
LABEL_21:nop
mov eax,x$_72
mov y$_113,eax
xor eax,eax
mov eax,CONST_85
mov $Temp_94_114,eax
mov eax,x$_72
add eax,$Temp_94_114
mov $Temp_95_115,eax
mov eax,$Temp_95_115
mov x$_72,eax
xor eax,eax
mov al,CONST_156
mov $Temp_96_116,eax
mov eax,$Temp_96_116
mov i$_2,eax
call putchar$
mov eax,y$_113
mov i$_29,eax
call print_int$
jmp LABEL_19
LABEL_20:nop
xor eax,eax
mov al,CONST_370
mov $Temp_97_119,eax
mov eax,$Temp_97_119
mov i$_2,eax
call putchar$
mov eax,x$_72
mov i$_29,eax
call print_int$
xor eax,eax
mov al,CONST_370
mov $Temp_98_122,eax
mov eax,$Temp_98_122
mov i$_2,eax
call putchar$
mov eax,xx$_83
mov i$_29,eax
call print_int$
xor eax,eax
mov al,CONST_370
mov $Temp_99_125,eax
mov eax,$Temp_99_125
mov i$_2,eax
call putchar$
mov esi,a$_65
mov eax,dword ptr fuck$_79[4*esi]
mov i$_29,eax
call print_int$
xor eax,eax
mov al,CONST_370
mov $Temp_100_129,eax
mov eax,$Temp_100_129
mov i$_2,eax
call putchar$
mov eax,ts$_78.a$
mov i$_29,eax
call print_int$
call print_own_str$
mov eax,offset CONST_486
mov str$_6,eax
call print_str$
ret
main ENDP

END main
		