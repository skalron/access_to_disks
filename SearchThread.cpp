//---------------------------------------------------------------------------
#include <System.hpp>
#pragma hdrstop

#include "SearchThread.h"
#include  "Unit1.h"
#include "FileStruct.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall SearchThread::SearchThread(BYTE * dataBufferPtr,int    bytesPerCluster,bool   CreateSuspended, int counter_clust )
: TThread(CreateSuspended )
{

	FreeOnTerminate = true;
	IndexForm->ProgressBar->Max = counter_clust;
	point = 1;


	BufferReadyEvent = new TEvent( NULL, true, false, "", false );   // обьект событий, синхронизирвоать два потока между собой
	BufferCopiedEvent = new TEvent( NULL, true, false, "", false );
	currentCluster = 0; //
	BytesPerCluster = bytesPerCluster;
	OutBufferPtr = dataBufferPtr;
	DataBuffer = new BYTE[bytesPerCluster];



}
//---------------------------------------------------------------------------
void __fastcall SearchThread::Execute()
{

	while (true)
	{
		// Ждать, пока не будет подготовлен буфер для копирования
		if ( BufferReadyEvent->WaitFor( WaitDelayMs ) == wrSignaled )  //gjckt ctnbdtynf d bnthfnjht
		{
			// Скопировать данные
			CopyData();

			// Отпустить буфер
			BufferReadyEvent->ResetEvent( );  //сброк собыотия
			BufferCopiedEvent->SetEvent( );  // второе событие, переход в итератор

			// Запустить поиск
			SearchData( );
			IndexForm->ProgressBar->Position = point;
				point++;
		}
		if ( Terminated )
		{
			break;
		}
	}
	// Удалить события
	delete BufferReadyEvent;
	delete BufferCopiedEvent;

	// Удалить буфер
	delete[ ]DataBuffer;
	Synchronize(&printMessageComplit);

}
//---------------------------------------------------------------------------

void SearchThread::SetCurrentCluster( int curCluster )
{
	currentCluster = curCluster;
}

void SearchThread::SearchData( )
{
	// Провести поиск
	if ( memcmp(DataBuffer, "\x42\x4D", 2 ) == 0)
	{

		memcpy(signature, "\x42\x4D\x00\x00", 4);
		memcpy(extensionFile, ".bmp", 4);
		Synchronize(&AddMatch );

	}
	if ( memcmp( DataBuffer, "\x25\x50\x44\x46", 4 ) == 0 )
	{

		memcpy( signature, "\x25\x50\x44\x46", 4 );
		memcpy( extensionFile, ".pdf", 4 );
		Synchronize(&AddMatch );

	}
}

void __fastcall SearchThread::AddMatch( )
{
	PVirtualNode newNode = IndexForm->VirtualStringTree1->AddChild(IndexForm->VirtualStringTree1->RootNode);
	FileStruct* nodeData = (FileStruct*)IndexForm->VirtualStringTree1->GetNodeData(newNode );
	nodeData->currentCluster = currentCluster;
	memcpy(nodeData->signature, signature, 4 );
	memcpy( nodeData->extensionFile, extensionFile, 4 );

}
void SearchThread::CopyData( )
{
	memcpy( DataBuffer, OutBufferPtr, BytesPerCluster );
}
void __fastcall SearchThread::printMessageComplit( )
{
		MessageBoxW( NULL, L"Поиск завершен упешно, либо остановлен", L"Успех", MB_OK );
}

