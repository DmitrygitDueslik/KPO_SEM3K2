.586
.MODEL FLAT, STDCALL

.CODE
getmin PROC USES ecx esi, pArr:DWORD, cnt:DWORD
	mov  esi, pArr
	mov  ecx, cnt
	mov  eax, [esi]
	dec  ecx
	jz   MIN_DONE
MIN_NEXT:
	add  esi, 4
	cmp  eax, [esi]
	jle  MIN_SKIP
	mov  eax, [esi]
MIN_SKIP:
	loop MIN_NEXT
MIN_DONE:
	ret
getmin ENDP

getmax PROC USES ecx esi, pArr:DWORD, cnt:DWORD
	mov  esi, pArr
	mov  ecx, cnt
	mov  eax, [esi]
	dec  ecx
	jz   MAX_DONE
MAX_NEXT:
	add  esi, 4
	cmp  eax, [esi]
	jge  MAX_SKIP
	mov  eax, [esi]
MAX_SKIP:
	loop MAX_NEXT
MAX_DONE:
	ret
getmax ENDP

END