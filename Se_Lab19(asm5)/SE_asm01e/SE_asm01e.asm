.586
.MODEL FLAT, STDCALL
includelib kernel32.lib
includelib libucrt.lib
includelib ..\Debug\SE_asm01d.lib

ExitProcess   PROTO :DWORD
GetStdHandle  PROTO :DWORD
WriteConsoleA PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD

getmin PROTO C :DWORD, :DWORD
getmax PROTO C :DWORD, :DWORD

.STACK 4096

.DATA
massiv   SDWORD 12, -5, 33, 7, -12, 18, 0, 95, -3, 9
msg      BYTE "getmax + getmin = "
result   BYTE 12 dup(0)
endl     BYTE 13, 10
written  DWORD ?

.CODE
tostr PROC USES ebx ecx edx edi, pStr:DWORD, num:SDWORD
	mov  edi, pStr
	mov  eax, num
	mov  ecx, 0
	cmp  eax, 0
	jge  T_POS
	mov  byte ptr [edi], '-'
	inc  edi
	neg  eax
T_POS:
	mov  ebx, 10
T_DIV:
	mov  edx, 0
	div  ebx
	push edx
	inc  ecx
	cmp  eax, 0
	jne  T_DIV
T_WRITE:
	pop  edx
	add  dl, '0'
	mov  [edi], dl
	inc  edi
	loop T_WRITE
	mov  eax, edi
	sub  eax, pStr
	ret
tostr ENDP


main PROC
	push LENGTHOF massiv
	push OFFSET massiv
	call getmax
	add  esp, 8
	mov  ebx, eax

	push LENGTHOF massiv
	push OFFSET massiv
	call getmin
	add  esp, 8
	add  ebx, eax

	INVOKE tostr, OFFSET result, ebx
	mov  esi, eax

	INVOKE GetStdHandle, -11
	mov  edi, eax
	INVOKE WriteConsoleA, edi, OFFSET msg, LENGTHOF msg, OFFSET written, 0
	INVOKE WriteConsoleA, edi, OFFSET result, esi, OFFSET written, 0
	INVOKE WriteConsoleA, edi, OFFSET endl, 2, OFFSET written, 0

	push 0
	call ExitProcess
main ENDP
end main