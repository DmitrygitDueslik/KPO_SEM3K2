.586P
.MODEL FLAT,STDCALL
includelib kernel32.lib


.STACK 4096
ExitProcess PROTO: DWORD
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD
.CONST
.DATA

MB_OK EQU 0
CAPT     DB "Есть ноль или нет", 0
MSG_ZERO DB "В массиве есть нулевой элемент", 0
MSG_NOZ  DB "В массиве нет нулевого элемента", 0

myBytes BYTE 10h,20h,30h,40h

myWords WORD 8Ah,3Bh,44h,5Fh,99h

myDoubles DWORD 1,2,3,4,5,6

myPointer DWORD myDoubles

ARR DWORD 1,2,0,4,5,6,7

.CODE
main PROC
	mov EBX,myPointer ;myDoubles 
	mov EAX,[EBX+4]	;2
	mov EDX,[EBX]	;1

	mov ESI,OFFSET ARR
	mov ECX,LENGTHOF ARR
	mov eax,0
	mov ebx,1

CYCLE:
	add eax,[esi]
	cmp dword ptr[esi],0
	jne NEXT	
	mov ebx,0
NEXT:
	add esi,TYPE ARR
	loop CYCLE

	cmp ebx,0
	je HAS_ZERO
	INVOKE MessageBoxA, 0, OFFSET MSG_NOZ, OFFSET CAPT, MB_OK
	jmp FINISH
HAS_ZERO:
	INVOKE MessageBoxA, 0, OFFSET MSG_ZERO, OFFSET CAPT, MB_OK
FINISH:
	push 0
	call ExitProcess
main ENDP
end main