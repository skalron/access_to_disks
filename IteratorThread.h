//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "SearchThread.h"
//---------------------------------------------------------------------------
class IteratorThread : public TThread
{
private:
protected:
	HANDLE FileSystemHandle;
	SearchThread * MySearchThread;
	void __fastcall Execute();
public:
	__fastcall IteratorThread(WCHAR* filePath, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
