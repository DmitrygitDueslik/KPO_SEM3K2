.586P
.MODEL FLAT,STDCALL
includelib kernel32.lib


ExitProcess PROTO: DWORD
MessageBoxA PROTO: DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096

.CONST


.DATA
MB_OK EQU 0

NUM1 DWORD 3
NUM2 DWORD 5
SUMMA DWORD ?

CAPT    DB "Лабораторная работа", 0 
TEXT1 DB "Результат сложения = "
DIGIT DB "?",0

.CODE

main PROC
START:
	mov eax,NUM1
	add eax,NUM2
	mov SUMMA,eax

	add al,'0'
	mov DIGIT,al

	INVOKE MessageBoxA,0,OFFSET TEXT1,OFFSET CAPT,MB_OK

	push -1
	call ExitProcess
	main ENDP
	end main