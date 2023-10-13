#pragma once
#include "PoolAllocator.h"

class Message : public PoolAllocator<Message>
{
public:
	Message*& getNext() const
	{
		return _next;
	}

	int _address;
	char _data[50];

	mutable Message* _next;
};


class NewMessage : public Message
{
public:
	int Number;
};
