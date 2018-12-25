section .text
    global _loadPageDirectory:function (_loadPageDirectory.LPDend - _loadPageDirectory)
	_loadPageDirectory:
		push ebp
		mov ebp, esp
		mov eax, [esp + 8]
		mov cr3, eax
		mov esp, ebp
		pop ebp
		ret
	.LPDend:


    global _enablePaging:function (_enablePaging.EPend - _enablePaging)
	_enablePaging:
		push ebp
		mov ebp, esp
		mov eax, cr0
		or eax, 0x80000000
		mov cr0, eax
		mov esp, ebp
		pop ebp
		ret
	.EPend:
