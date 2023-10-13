#pragma once
#include "MemoryPool.h"
#include <iostream>
using namespace std;

template <typename T>
class PoolAllocator
{
public:
	
	// Speicher aus dem Pool zuweisen
	static void* operator new ( size_t size ) throw ( std::bad_alloc )
	{
		return MemoryPool<T>::alloc( size );
	}

	// Speicher wieder an den Pool zurückgeben
	static void operator delete ( void* ptr )
	{
		MemoryPool<T>::free(ptr);
	}

	// Überschreiben des globalen Placement-operators new
	static void* operator new ( size_t size, void* ptr )
	{
		return ptr;
	}

	// Überschreiben des globalen Placement-operators delete
	static void operator delete ( void*, void* )
	{

	}
};

