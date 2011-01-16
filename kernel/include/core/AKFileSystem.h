#ifndef AKFILESYSTEM_H
#define AKFILESYSTEM_H
#include <stdint.h>

class AKFileSystem
{
public:	//types
	typedef struct Node
	{
		char* filename;
		uint32_t pmask;
		uint32_t uid;
		uint32_t gid;
		uint32_t flags;
		uint64_t length;
	};
public:	//api
};
#endif