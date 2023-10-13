#include <iostream>
using namespace std;
#include "mutex.h"

Mutex::Mutex()
{ 
  InitializeCriticalSection ( &MyBinarySemaphore );
}

Mutex::~Mutex()
{
  DeleteCriticalSection ( &MyBinarySemaphore );
}

void Mutex::acquire()
{
  EnterCriticalSection ( &MyBinarySemaphore );
}

void Mutex::release()
{
  LeaveCriticalSection ( &MyBinarySemaphore );
}




