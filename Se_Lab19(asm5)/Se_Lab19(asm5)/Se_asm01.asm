.586
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO: DWORD

.STACK 4986
.DATA
massiv   SDWORD 12, -5, 33, 7, -12, 18, 0, 95, -3, 9
minimum  SDWORD ?

.CODE
getmin PROC USES ecx esi,pArr:DWORD,cnt:DWORD
	mov esi,pArr
	mov ecx,cnt
	mov eax,[esi]
	dec ecx
	jz MIN_DONE
MIN_NEXT:
	add esi,4
	cmp eax,[esi]
	jle MIN_SKIP
	mov eax,[esi]
MIN_SKIP:
	loop MIN_NEXT
MIN_DONE:
	ret
getmin ENDP


main PROC
	push LENGTHOF massiv
	push OFFSET massiv
	call getmin
	mov  minimum, eax

	push 0
	call ExitProcess
main ENDP
end main