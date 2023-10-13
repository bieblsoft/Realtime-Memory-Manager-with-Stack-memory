#pragma once
#include <windows.h>

class Mutex
{
  public:
    Mutex();
    virtual ~Mutex();
    void acquire();
    void release();
  private:
    // win32 struct
    CRITICAL_SECTION  MyBinarySemaphore;
};
