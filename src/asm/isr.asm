extern isr_handler

%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    cli                         ; Disable interrupts firstly.
    push 0                      ; Push a dummy error code.
    push %1                     ; Push the interrupt number.
    jmp isr_common_stub         ; Go to our common handler code.
%endmacro

; This macro creates a stub for an ISR which passes it's own
; error code.
%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    cli                         ; Disable interrupts.
    push %1                     ; Push the interrupt number
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 255

; C function in idt.c
extern idt_handler

global isr_common_stub:function isr_common_stub.end-isr_common_stub

isr_common_stub:
    pusha      ; Push our register contents

    mov ax, ds ; Move lower bits of EAX into ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    push esp
    call isr_handler ; call the isr handler in isr.c
    add esp, 4

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    mov ss, bx

    popa      ; pop the register contents
    add esp, 8
    iret
.end:

extern irq_handler

global irq_common_stub:function irq_common_stub.end-irq_common_stub

irq_common_stub:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  push esp
  call irq_handler
  pop esp

  pop ebx
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  mov ss, bx

  popa
  add esp, 8
  sti
  iret
.end:

; Macro crates a stub for IRQ. First param is IRQ number, second is isr it is mapped to
%macro IRQ 2
  global irq%1
  irq%1:
    cli                         ; Disble Interrupts
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47


