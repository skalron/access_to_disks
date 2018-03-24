//---------------------------------------------------------------------------

#ifndef SearchThreadH
#define SearchThreadH
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
 const int WaitDelayMs = 200;
//---------------------------------------------------------------------------

class SearchThread: public TThread
{
private:
	__int64 point;
	int BytesPerCluster;
	BYTE* OutBufferPtr;
	BYTE* DataBuffer;
	int currentCluster;
	BYTE signature[5];
	BYTE extensionFile[4];

	void CopyData();
	void SearchData( );
	void __fastcall AddMatch( );
	void __fastcall CompleteSearch();
protected:

	void __fastcall Execute();
public:
	__fastcall SearchThread(BYTE * dataBufferPtr,int clusterSize,bool CreateSuspended, int counter_clust);
	void SetCurrentCluster(int curCluster);
	void __fastcall printMessageComplit();

  TEvent * BufferReadyEvent;
  TEvent * BufferCopiedEvent;


};
//---------------------------------------------------------------------------
#endif
