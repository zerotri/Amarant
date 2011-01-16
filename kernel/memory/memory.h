//Initializes the memory map.
int kernel_memory_init(void* start, unsigned int size);

//allocates a chunk of memory.
void* kernel_memory_allocate   (unsigned int size);
void  kernel_memory_free       (void* ptr);

//reallocates memory. creates a new buffer (if required) and copies the
//previous buffer into that location. **EXPENSIVE**
void* kernel_memory_reallocate (void* ptr, unsigned int size);
