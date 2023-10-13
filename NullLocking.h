/*
	NullLocking

	implementierung des Locking Concept
	für single-thread Anwendungen.
	In solchen Anwendungen ist kein echtes 
	locking erforderlich, daher erfolgt hier eine Dummy
	Implementierung.
	Dadurch, dass die Funktionen acquire und release leer deklariert 
	und als inline geknnzeichnet sind, werden diese vom Compiler
	komplett wegoptimiert.
*/

class NullLocking
{
public:
	NullLocking()
	{
	}

	static inline void acquire()
	{
		cout << "Locking aquired" << endl;
	}

	static inline void release()
	{
		cout << "Locking released" << endl;
	}
};