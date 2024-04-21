#include "pmm.h"
#include "screen.h"
#include "string.h"
#include "kernel.h"

uint8_t* bitmap = (uint8_t*)(&__kernel_section_end);
uint32_t bitmap_size = 0;
uint8_t* mem_start = 0; // Start of physical memory
uint32_t total_frames = 0;

void pmm_init(uint32_t mem_size)
{
    total_frames = mem_size / FRAME_SIZE;

    bitmap_size = total_frames / 8;

    memset(bitmap, 0, bitmap_size);

    mem_start = (uint8_t*)BLOCK_ALIGN(((uint32_t)(bitmap + bitmap_size)));

    printf("\nTotal Physical Memory: %d mb", mem_size / (1024 * 1024));
    printf("\nBitmap Size: %d", bitmap_size);
    printf("\nNumber of Physical Frames: %d", total_frames);
    printf("\nStart of Usable Physical Memory: 0x%x", mem_start); // 90% sure thats wrong but whatever
}


uint32_t get_first_free_frame()
{
    for(uint32_t i = 0; i < total_frames; i++)
    {
        if(!ISSET(i))
            return i;
    }

    printf("Damn no free frames. Womp Womp :(");
    return -1;
}

uint32_t pmm_alloc_frame()
{
    uint32_t frame_idx = get_first_free_frame();
    SET_BIT(frame_idx);
    return frame_idx;
}

void pmm_free_frame(int idx)
{
    CLEAR_BIT(idx);
}

void pmm_test()
{
    int t1 = pmm_alloc_frame();
    printf("\nFirst free frame at %d", t1);

    int t2 = pmm_alloc_frame();
    printf("\nSecond free frame at %d", t2);

    int t3 = pmm_alloc_frame();
    printf("\nThird free frame at %d", t3);

    pmm_free_frame(t2);
    printf("\nClearing t2");

    int t4 = get_first_free_frame();
    printf("\nIs this 1? : %d", t4);
}
