//4bytes in 32bit mode
struct __kmeminfo_s
{
	unsigned int stat;	//status
	unsigned int size;	//size
	unsigned int psid;	//process id (used if the process dies. all memory gets freed)
	__kmeminto_s* next;	//pointer to next
};	//data pointer is assumed to be directly after this struct.
