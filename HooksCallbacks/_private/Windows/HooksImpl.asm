; This file contains the implementation of _penter and _pexit functions.
; Those function calls are inserted by MSVC at every function entry and exit
; if /Gh and /GH options are enabled

; Functions (defined in C/C++) that are called from within _penter/_pexit
extrn onFunctionEnter:Proc
extrn onFunctionExit:Proc

.code
;--------------------------------------------------------------------
; _penter procedure
;--------------------------------------------------------------------

_penter proc
    ; At this point, rsp (stack pointer) will have the address where _penter will return to when finished
    ; The below push operations will grow the stack (decrement rsp, as stack grows downwards)
    ; While debugging, rsp was getting decremented by 8 bytes

    ; Store the volatile registers because they may/will be lost when entering a function call [MSDN]
    ; rax, rcx, rdx, r8-r11 are volatile registers. Thus, saving their values so that we can
    ; restore them after the function call, onFunctionEnter
    push r11
    push r10
    push r9
    push r8
    push rax
    push rdx
    push rcx

    ; According to x64 calling conventions
    ; 1. The first four integer or pointer parameters are passed in the rcx, rdx, r8, and r9 registers.
    ; 2. The first four floating-point parameters are passed in the first four SSE registers, xmm0-xmm3.
    ; 3. The caller reserves space on the stack for arguments passed in registers. The called function 
    ; can use this space to spill the contents of registers to the stack.
    ; [a] So, according to point 3, reserve 4 registers x 8 bytes = 32 bytes in the stack for rcx, rdx, r8, and r9).
    sub  rsp,20h 

    ; BOOKKEEPING DONE, now we'll need to send the argument to function onFunctionEnter.
    ; According to point 1 above, it is to be sent in rcx register
    ; But, what should we send?
    ; The argument is the address of the function calling this _penter function
    ; To find the function calling _penter we need to do some pointer arithmetic

    ; We are 88 (0x58) bytes down from the beginning position of rsp when we entered this proc. 
    ; 7 registers * 8 bytes + 32 bytes = 88 bytes
    ; * Let's copy rsp value to rcx
    mov  rcx,rsp
    ; * Add 88 bytes (stack grows towards lower memory addresses), so that we're pointing to the position
    ; of the stack where we were at beginning
    mov  rcx,qword ptr[rcx+58h]
    ; * Subtract 1 for the instruction ("call") and 4 bytes for the operand
    ; The operand is 4 bytes even in x64 as this is an offset value relative to the address of the instruction
    ; from where it is called. This calculation can be seen while debugging. 
    sub  rcx,5

    ; call the function
    call onFunctionEnter

    ; Now, clean up stack and unwind it in the reverse order

    ;Release the space reserved for the registers by adding 32 bytes
    add  rsp,20h 

    ;Restore the registers back by poping out
    pop rcx
    pop rdx
    pop rax
    pop r8
    pop r9
    pop r10
    pop r11

    ;return
    ret

_penter endp

;--------------------------------------------------------------------
; _pexit procedure
;--------------------------------------------------------------------
_pexit proc
    
    ; Store the volatile registers
    push r11
    push r10
    push r9
    push r8
    push rax
    push rdx
    push rcx

    ; reserve space for 4 registers [ rcx,rdx,r8 and r9 ] 32 bytes
    sub  rsp,20h 
    
    ; Get the return address of the function
    mov  rcx,rsp
    mov  rcx,qword ptr[rcx+58h]

    call onFunctionExit

    ;Release the space reserved for the registersk by adding 32 bytes
    add rsp,20h

    ;Restore the registers back by poping out
    pop rcx
    pop rdx
    pop rax
    pop r8
    pop r9
    pop r10
    pop r11

    ;return
    ret
    
_pexit endp


end