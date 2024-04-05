#include "kernel.h"
#include "screen.h"
#include "vga.h"

void kmain() {
    screen_init(WHITE, BLUE);
    screen_put_string("Welcome to SimpleOS!\n");
}
