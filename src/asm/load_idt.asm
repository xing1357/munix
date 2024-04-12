global load_idt:function load_idt.end-load_idt

load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret
.end:
