.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib
ExitProcess PROTO :DWORD
.STACK 4096
.DATA
T0	BYTE	01h
V0	SWORD	0
T1	BYTE	01h
V1	SWORD	-15
T2	BYTE	01h
V2	SWORD	32767
T3	BYTE	01h
V3	SWORD	-32768
T4	BYTE	02h
V4	WORD	0
T5	BYTE	02h
V5	WORD	22
T6	BYTE	02h
V6	WORD	65535
.CODE
main PROC
	movsx	eax, V0
	movsx	eax, V1
	movsx	eax, V2
	movsx	eax, V3
	movzx	eax, V4
	movzx	eax, V5
	movzx	eax, V6
	push	0
	call	ExitProcess
main ENDP
end main
