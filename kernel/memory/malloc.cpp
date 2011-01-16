/*
 * Copyright (c) 2002 Justin Armstrong
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//#include "kernel.h"
//#include "semaphore.h"
#include "../icxxabi/icxxabi.h"
typedef unsigned int u32;
typedef unsigned char u8;
/*
 * a simple malloc implementation, based on the one
 * described in "The C Programming Language" by Kernighan & Ritchie
 */



typedef struct header_t {

    struct header_t *next;
    u32 size;

} header_t;


extern void* __bss_end__;  //the end of bss
#define RAM_START (u8*)0x02000000
#define RAM_END (u8*)0x02040000
header_t* s_start = NULL;

static bool s_inited = FALSE;
static u32 s_max_heap_size = 0;

//static struct semaphore_t s_malloc_sem;


static void _init_heap() {
    header_t* first;
    
    s_start = (header_t*)RAM_START;

    first = s_start+1;

    s_start->size = 0;
    s_start->next = first;

    first->next = s_start;
    first->size = ((RAM_END - RAM_START)-sizeof(header_t))/sizeof(header_t);
    s_max_heap_size = first->size;
    
    //semaphore_create(&s_malloc_sem, 1);

    s_inited = TRUE;

}

u32 count_bytes_free() {
    u32 count = 0;
    header_t* p = s_start;
    
    if (!s_inited) return 0;

    //semaphore_wait(&s_malloc_sem);
    
    do {
        count += p->size*sizeof(header_t);
        p = p->next;
    }
    while (p!=s_start);
    
    //semaphore_signal(&s_malloc_sem);
    
    return count;

}

u32 max_heap_size() {

    return s_max_heap_size * sizeof(header_t);

}

void* malloc(int nbytes) {

    header_t* p;
    header_t* prev;
    
    u32 nunits = (nbytes+sizeof(header_t)-1)/sizeof(header_t) + 1;
    
    if (!s_inited) _init_heap();

    //semaphore_wait(&s_malloc_sem);
    
    prev = s_start;
    
    p = prev->next;
    while(1) {
    
        if (p->size >= nunits) {
            if (p->size == nunits) {
                //an exact fit!
                prev->next = p->next;
            }
            else {
                //block is bigger than we need, split it
                p->size -= nunits;
                
                p += p->size;
                p->size = nunits;
                
            }
            //semaphore_signal(&s_malloc_sem);
            return (void*)(p+1);
        
        }
    
        
        /*wrapped around - no block found */
        if (p == s_start) {
            //semaphore_signal(&s_malloc_sem);
            return NULL;
        }
            
        prev = p;
        p = p->next;

    }
    


}


void
free(void* blk) {   

    header_t* blk_hdr;
    header_t* prev;
    header_t* next;
    
    //printf("free %p\r\n", blk);
    if (!blk) return;
    
    blk_hdr = (header_t*)blk - 1;

    //semaphore_wait(&s_malloc_sem);

    prev = s_start;
    next = s_start->next;
    do {

        if (next > blk_hdr) break;   //next is now pointing at the next free block after blk_hdr
        prev = next;
        next = next->next;
        
    }
    while (next != s_start);

                
    blk_hdr->next = next;  
    prev->next = blk_hdr;
    //block is now back in the list


    //next we see if we can merge any adjacent blocks with this one
    
    if (blk_hdr + blk_hdr->size == next) {
        blk_hdr->size += blk_hdr->next->size;
        blk_hdr->next = blk_hdr->next->next;        
        
    }

    if ((prev != s_start) && (prev + prev->size == blk_hdr)) {

        prev->size += blk_hdr->size;
        prev->next = blk_hdr->next;
        
    }
    
    //semaphore_signal(&s_malloc_sem);
}

