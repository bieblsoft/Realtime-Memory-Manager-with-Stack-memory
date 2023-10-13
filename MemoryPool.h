#pragma once
#include <memory.h>
#include <iostream>
using namespace std;
#include "NullLocking.h"

template <typename T>
class Chunk
{
	public:
		T object;
		Chunk* _next;
};

int Data[5];

// implementierung für Übergabe eines Locking-Concept
template <typename T, class LOCKING=NullLocking>
class MemoryPool
{
public:

	// Anzahl der Objekte, für die der Pool Speicher
	// bereitstellen kann
	enum { e_size = 10 };

	// Zeiger auf die Liste der freien Elemente
	static Chunk<T>* _head;

	// memory Pool - stores our Objects and resides in Stack area
	static char _memory [e_size * sizeof(Chunk<T>)];

	// Anzahl der belegten chunks
	static int _index;

	static Chunk<T>* initializeFreeList() 
	{
	  Chunk<T>* chunkArray = reinterpret_cast<Chunk<T>*>( _memory );
	  
	  // link free list together
	  for( int i=0 ; i<e_size-1; ++i) 
	  {
		chunkArray[i]._next = &(chunkArray[i+1]);
	  }

	  // terminate the list with a null pointer
	  chunkArray[e_size-1]._next = 0;

	  // return head of the list
	  return chunkArray;
	};

	static void* alloc ( size_t size ) throw ( std::bad_alloc )
	{
		// nach ISO-norm erforderlich
		if ( size == 0 ) size = sizeof(T);

		// Prüfen, ob die Originalklasse oder eine abgeleitete
		// Klasse instanziert wurde
		if ( size != sizeof(T) )
			throw std::bad_alloc();

		// Locking
		LOCKING::acquire();

		// chunk aus der Liste entfernen
		if ( _head )
		{
			Chunk<T>* ptr = (Chunk<T>*) _head;
			_head = ptr->_next;

			LOCKING::release();

			return ptr;
		}
		else
		{
			// kein freier Speicher mehr ?
			if ( ! ( _index < e_size ) )
			{
				LOCKING::release();
				throw std::bad_alloc();
			}

			// Speicher aus dem Pool zuweisen
			Chunk<T>* x = (Chunk<T>*) _memory + ( _index++ + sizeof(Chunk<T>) );
			LOCKING::release();
			return x;
		}
	}

	// Die Methode free bindet den freigegebenen 
	// Speicherblock wieder in die Liste der
	// freien Speicherblöcke ein
	static void free ( void* ptr )
	{
		if ( ptr == NULL ) return;

		Chunk<T>* chunk = (Chunk<T>*) ptr;
		chunk->_next = _head;
		_head = chunk;
	}

private:

};

template <typename T, class LOCKING>
typename Chunk<T>* MemoryPool<T, LOCKING>::_head = 
	MemoryPool<T,LOCKING>::initializeFreeList();

template <typename T, class LOCKING>
typename char MemoryPool<T, LOCKING>::_memory[];

template <typename T, class LOCKING>
int MemoryPool<T, LOCKING>::_index = 0;

