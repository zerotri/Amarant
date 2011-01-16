extern uint32_t end_kernel;
__kmeminfo_s* _kernel_memory_firstblock;

int kernel_memory_init(void* start, unsigned int size)
{
	_kernel_memory_firstblock = (__kmeminfo_s*)start;
	_kernel_memory_firstblock->size=0;
	_kernel_memory_firstblock->next=0;
	_kernel_memory_firstblock->stat=0;
	_kernel_memory_firstblock->psid=0;
}

//allocates a chunk of memory.
void* kernel_memory_allocate   (unsigned int size)
{
	//Set starting point to the first block in memory
	__kmeminfo_s* cur_block = _kernel_memory_firstblock;

	//loop until at the end of the block list
	while(cur_block->next != 0)
	{
		cur_block = cur_block->next;
	}

	//create a new block at the end of all of the others.
	cur_block->next = (int)(*cur_block) + sizeof(__kmeminfo_s) + (cur_block->size);
	cur_block = cur_block->next;

}
void  kernel_memory_free       (void* ptr);

//reallocates memory. creates a new buffer (if required) and copies the
//previous buffer into that location. **EXPENSIVE**
void* kernel_memory_reallocate (void* ptr, unsigned int size);
