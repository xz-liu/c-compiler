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
i$_6 DWORD ?
CONST_54 DWORD 0
$Temp_46_9 DWORD  ?
cnt$_8 DWORD  ?
$Temp_47_10 DWORD  ?
$Temp_0_11 DWORD  ?
$Temp_1_12 DWORD  ?
CONST_70 BYTE '-'
$Temp_48_13 DWORD  ?
$Temp_49_15 DWORD  ?
$Temp_3_16 DWORD  ?
CONST_83 BYTE '0'
$Temp_50_17 DWORD  ?
$Temp_5_19 DWORD  ?
cs$_7 BYTE 20 DUP(?)
$Temp_51_21 DWORD  ?
CONST_100 DWORD 10
$Temp_7_22 DWORD  ?
$Temp_52_23 DWORD  ?
$Temp_8_24 DWORD  ?
$Temp_53_25 BYTE  ?
$Temp_54_26 DWORD  ?
$Temp_55_27 DWORD  ?
$Temp_56_28 DWORD  ?
$Temp_9_29 DWORD  ?
$Temp_57_31 DWORD  ?
a$_34 DWORD ?
b$_35 DWORD ?
$Temp_12_36 DWORD  ?
$return_value_33 DWORD  ?
a$_38 DWORD ?
b$_39 DWORD ?
$Temp_13_40 DWORD  ?
$return_value_37 DWORD  ?
CONST_167 DWORD 3
$Temp_58_43 DWORD  ?
a$_42 DWORD  ?
CONST_171 DWORD 5
$Temp_59_45 DWORD  ?
b$_44 DWORD  ?
CONST_178 DWORD 2
$Temp_60_48 DWORD  ?
c$_47 DWORD  ?
$Temp_61_50 DWORD  ?
x$_49 DWORD  ?
CONST_187 DWORD 3.500000
$Temp_62_52 DWORD  ?
f$_51 DWORD  ?
CONST_191 DWORD 3.200000
$Temp_63_54 DWORD  ?
s$_53 DWORD  ?
$Temp_14_59 DWORD  ?
xx$_60 DWORD  ?
$Temp_15_61 DWORD  ?
yy$_62 DWORD  ?
fuck2$_57 DWORD 10 DUP(?)
CONST_238 DWORD 100
$Temp_64_64 DWORD  ?
fuck3$_58 DWORD 10 DUP(?)
CONST_245 DWORD 2000
$Temp_65_66 DWORD  ?
fuck$_56 DWORD 10 DUP(?)
$Temp_21_70 DWORD  ?
ts$_55 test_struct$  <>
CONST_275 DWORD 345678
$Temp_25_74 DWORD  ?
$Temp_66_75 DWORD  ?
CONST_279 BYTE '5'
$Temp_67_76 DWORD  ?
CONST_284 BYTE ' '
$Temp_68_78 DWORD  ?
CONST_289 DWORD 234
$Temp_69_80 DWORD  ?
$Temp_70_82 DWORD  ?
$Temp_29_83 DWORD  ?
$Temp_30_84 DWORD  ?
$Temp_31_85 DWORD  ?
$Temp_71_86 DWORD  ?
i$_46 DWORD  ?
$Temp_72_87 DWORD  ?
$Temp_32_88 DWORD  ?
$Temp_33_89 DWORD  ?
y$_90 DWORD  ?
CONST_48 DWORD 20
$Temp_73_91 DWORD  ?
$Temp_74_92 DWORD  ?
$Temp_75_93 DWORD  ?
$Temp_76_96 DWORD  ?
$Temp_77_99 DWORD  ?
$Temp_78_102 DWORD  ?
$Temp_79_106 DWORD  ?

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
print_int$ PROC
xor eax,eax
mov eax,CONST_54
mov $Temp_46_9,eax
mov eax,$Temp_46_9
mov cnt$_8,eax
xor eax,eax
mov eax,i$_6
mov $Temp_47_10,eax
mov eax,$Temp_47_10
sub eax,CONST_54
shr eax,31
mov $Temp_0_11,eax
mov eax,$Temp_0_11
and eax,eax
jz LABEL_0
mov eax,i$_6
neg eax
mov $Temp_1_12,eax
mov eax,$Temp_1_12
mov i$_6,eax
xor eax,eax
mov al,CONST_70
mov $Temp_48_13,eax
mov eax,$Temp_48_13
mov i$_2,eax
call putchar$
jmp LABEL_1
LABEL_0:nop
LABEL_1:nop
xor eax,eax
mov eax,i$_6
mov $Temp_49_15,eax
mov eax,$Temp_49_15
sub eax,CONST_54

test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			mov $Temp_3_16,eax
mov eax,$Temp_3_16
and eax,eax
jz LABEL_2
xor eax,eax
mov al,CONST_83
mov $Temp_50_17,eax
mov eax,$Temp_50_17
mov i$_2,eax
call putchar$
jmp LABEL_3
LABEL_2:nop
LABEL_3:nop
LABEL_4:nop
mov eax,i$_6
and eax,eax
jz LABEL_5
mov eax,cnt$_8
mov $Temp_5_19,eax
inc cnt$_8
xor eax,eax
mov eax,i$_6
mov $Temp_51_21,eax

mov eax,$Temp_51_21
cdq
mov ecx,CONST_100
idiv ecx
mov $Temp_7_22,edx
xor eax,eax
mov al,CONST_83
mov $Temp_52_23,eax
mov eax,$Temp_7_22
add eax,$Temp_52_23
mov $Temp_8_24,eax
xor eax,eax
mov eax,$Temp_8_24
mov $Temp_53_25,al
mov al,$Temp_53_25
mov esi,$Temp_5_19
mov cs$_7[esi],al
xor eax,eax
mov eax,CONST_100
mov $Temp_54_26,eax
mov eax,i$_6
cdq
idiv $Temp_54_26
mov $Temp_55_27,eax
mov eax,$Temp_55_27
mov i$_6,eax
jmp LABEL_4
LABEL_5:nop
LABEL_6:nop
xor eax,eax
mov eax,cnt$_8
mov $Temp_56_28,eax
mov eax,$Temp_56_28
sub eax,CONST_54
shr eax,31
xor eax,1
mov $Temp_9_29,eax
mov eax,$Temp_9_29
and eax,eax
jz LABEL_7
dec cnt$_8
xor eax,eax
mov esi,cnt$_8
mov al,cs$_7[esi]
mov $Temp_57_31,eax
mov eax,$Temp_57_31
mov i$_2,eax
call putchar$
jmp LABEL_6
LABEL_7:nop
ret
print_int$ ENDP
add_two_num$ PROC
mov eax,a$_34
add eax,b$_35
mov $Temp_12_36,eax
mov eax,$Temp_12_36
mov $return_value_33,eax
ret
add_two_num$ ENDP
sub_two_num$ PROC
mov eax,a$_38
sub eax,b$_39
mov $Temp_13_40,eax
mov eax,$Temp_13_40
mov $return_value_37,eax
ret
sub_two_num$ ENDP
main PROC
xor eax,eax
mov eax,CONST_167
mov $Temp_58_43,eax
mov eax,$Temp_58_43
mov a$_42,eax
xor eax,eax
mov eax,CONST_171
mov $Temp_59_45,eax
mov eax,$Temp_59_45
mov b$_44,eax
xor eax,eax
mov eax,CONST_178
mov $Temp_60_48,eax
mov eax,$Temp_60_48
mov c$_47,eax
xor eax,eax
mov eax,CONST_54
mov $Temp_61_50,eax
mov eax,$Temp_61_50
mov x$_49,eax
fild CONST_187
fst $Temp_62_52
mov eax,$Temp_62_52
mov f$_51,eax
fild CONST_191
fst $Temp_63_54
mov eax,$Temp_63_54
mov s$_53,eax
mov eax,a$_42
mov a$_34,eax
mov eax,b$_44
mov b$_35,eax
call add_two_num$
mov eax,$return_value_33
mov $Temp_14_59,eax
mov eax,$Temp_14_59
mov xx$_60,eax
mov eax,a$_42
mov a$_38,eax
mov eax,b$_44
mov b$_39,eax
call sub_two_num$
mov eax,$return_value_37
mov $Temp_15_61,eax
mov eax,$Temp_15_61
mov yy$_62,eax
xor eax,eax
mov eax,CONST_238
mov $Temp_64_64,eax
mov eax,$Temp_64_64
mov esi,b$_44
mov fuck2$_57[esi],eax
xor eax,eax
mov eax,CONST_245
mov $Temp_65_66,eax
mov eax,$Temp_65_66
mov esi,c$_47
mov fuck3$_58[esi],eax
mov esi,b$_44
mov eax,fuck2$_57[esi]
mov esi,c$_47
add eax,fuck3$_58[esi]
mov $Temp_21_70,eax
mov eax,$Temp_21_70
mov esi,a$_42
mov fuck$_56[esi],eax
mov eax,CONST_275
neg eax
mov $Temp_25_74,eax
xor eax,eax
mov eax,$Temp_25_74
mov $Temp_66_75,eax
mov eax,$Temp_66_75
mov ts$_55.c$,eax
mov eax,ts$_55.c$
mov ts$_55.b$,eax
mov eax,ts$_55.b$
mov ts$_55.a$,eax
xor eax,eax
mov al,CONST_279
mov $Temp_67_76,eax
mov eax,$Temp_67_76
mov i$_2,eax
call putchar$
xor eax,eax
mov al,CONST_284
mov $Temp_68_78,eax
mov eax,$Temp_68_78
mov i$_2,eax
call putchar$
xor eax,eax
mov eax,CONST_289
mov $Temp_69_80,eax
mov eax,$Temp_69_80
mov i$_6,eax
call print_int$
fld f$_51
fld s$_53
fadd
fst $Temp_70_82
mov eax,$Temp_70_82
mov f$_51,eax
mov eax,b$_44
sub eax,a$_42
shr eax,31
mov $Temp_29_83,eax
mov eax,$Temp_29_83
and eax,eax
jz LABEL_8
mov eax,a$_42
sub eax,b$_44
mov $Temp_30_84,eax
mov eax,$Temp_30_84
mov c$_47,eax
jmp LABEL_9
LABEL_8:nop
mov eax,b$_44
sub eax,a$_42
mov $Temp_31_85,eax
mov eax,$Temp_31_85
mov c$_47,eax
LABEL_9:nop
xor eax,eax
mov eax,CONST_54
mov $Temp_71_86,eax
mov eax,$Temp_71_86
mov i$_46,eax
jmp LABEL_13
LABEL_10:nop
xor eax,eax
mov eax,i$_46
mov $Temp_72_87,eax
mov eax,$Temp_72_87
sub eax,CONST_167
shr eax,31
mov $Temp_32_88,eax
mov eax,$Temp_32_88
and eax,eax
jnz LABEL_13
mov eax,$Temp_32_88
and eax,eax
jz LABEL_12
LABEL_11:nop
mov eax,i$_46
mov $Temp_33_89,eax
inc i$_46
jmp LABEL_10
LABEL_13:nop
mov eax,x$_49
mov y$_90,eax
xor eax,eax
mov eax,CONST_48
mov $Temp_73_91,eax
mov eax,x$_49
add eax,$Temp_73_91
mov $Temp_74_92,eax
mov eax,$Temp_74_92
mov x$_49,eax
xor eax,eax
mov al,CONST_70
mov $Temp_75_93,eax
mov eax,$Temp_75_93
mov i$_2,eax
call putchar$
mov eax,y$_90
mov i$_6,eax
call print_int$
jmp LABEL_11
LABEL_12:nop
xor eax,eax
mov al,CONST_284
mov $Temp_76_96,eax
mov eax,$Temp_76_96
mov i$_2,eax
call putchar$
mov eax,x$_49
mov i$_6,eax
call print_int$
xor eax,eax
mov al,CONST_284
mov $Temp_77_99,eax
mov eax,$Temp_77_99
mov i$_2,eax
call putchar$
mov eax,xx$_60
mov i$_6,eax
call print_int$
xor eax,eax
mov al,CONST_284
mov $Temp_78_102,eax
mov eax,$Temp_78_102
mov i$_2,eax
call putchar$
mov esi,a$_42
mov eax,fuck$_56[esi]
mov i$_6,eax
call print_int$
xor eax,eax
mov al,CONST_284
mov $Temp_79_106,eax
mov eax,$Temp_79_106
mov i$_2,eax
call putchar$
mov eax,ts$_55.a$
mov i$_6,eax
call print_int$
ret
main ENDP

END main
		