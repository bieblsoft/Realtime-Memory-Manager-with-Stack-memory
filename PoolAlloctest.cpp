#include "Message.h"
#include "PoolAllocator.h"
#include <iostream>
using namespace std;


void main()
{
	try
	{
		void* Nachrichten[11];
		Message *Nachricht;

		for ( int i = 0; i < 10; i++ )
		{
			Nachricht = new Message();
			Nachricht->_address = i;
			for ( int x=0; x<50; x++ )
			{
				Nachricht->_data[x] = (char) (i+' ');
			}
			Nachrichten[i] = (void*) Nachricht;
		}

		cout << "Pool angelegt und gefüllt!" << endl;

		for ( int j = 0; j < 10; j++ )
		{
			delete Nachricht;
		}

		cout << "Pool wieder freigegeben!" << endl;

		NewMessage* x = new NewMessage();
	}
	catch ( ... )
	{
		cout << "Exception !" << endl;
	}
}
