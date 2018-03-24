//---------------------------------------------------------------------------


#pragma hdrstop
 #include "NTFS.h"
#include "IteratorThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall IteratorThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall IteratorThread::IteratorThread(WCHAR* filePath,bool CreateSuspended)
	: TThread(CreateSuspended)
{

	FreeOnTerminate = true; // для того чтобы явно не уничтожать поток
	NTFS_FileSystem objFileSystem = NTFS_FileSystem( );
	// Открыть файловую систему
	if(!objFileSystem.Open(filePath)) return;
	FileSystemHandle = objFileSystem.GetFileHandle();



}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{

	// Определить размер кластера
	NTFS_FileSystem iterFileSystem = NTFS_FileSystem(); // создание нового объекта
	iterFileSystem.SetFileHandle(FileSystemHandle);   // устанавливаем для нового обьекта дескриптор файла
	if(!iterFileSystem.ReadBootSector()) return; // чтение загрузочного сектора


	int counter_clust = iterFileSystem.GetTotalSectors( ) / iterFileSystem.GetSectorPerCluster( );
	int bytesPerCluster = iterFileSystem.GetBytesPerSector() * iterFileSystem.GetSectorPerCluster( );
	BYTE * dataBuffer = new BYTE[bytesPerCluster];

//  ЗДЕСЬ СОЗДАЕМ ВТОРОЙ ПОТОК ДЛЯ ПОИСКА
	MySearchThread = new SearchThread(dataBuffer, bytesPerCluster, false, counter_clust);
//  memcmp
//  memptr1  Указатель на первый блок памяти.
//  memptr2   Указатель на второй блок памяти.
//  num       Количество байтов для сравнения.
//  РЕЗУЛЬТАТ: если нулевое значение , то содержимое обоих блоков памяти равны.



	if (memcmp(iterFileSystem.GetOEMName(), "\x4e\x54\x46\x53\x20\x20\x20\x20",  8) == 0 )
			if ( memcmp(iterFileSystem.GetOEMName( ),
		"\x4e\x54\x46\x53\x20\x20\x20\x20",8 ) == 0 )
	{
		for ( int i = 0; i < iterFileSystem.GetTotalSectors( ) / iterFileSystem.GetSectorPerCluster( ); i++ )
		{

			if ( !iterFileSystem.ReadCluster( i, 1, dataBuffer ) )
			{
				return;
			}


			MySearchThread->BufferReadyEvent->SetEvent( ); //


			while ( MySearchThread->BufferCopiedEvent->WaitFor( WaitDelayMs )
				!= wrSignaled )
			{
			}
			MySearchThread->SetCurrentCluster( i );
			MySearchThread->BufferCopiedEvent->ResetEvent( );  //ñáðîñ ñîáûòèÿ
			if ( Terminated )  // åñëè êîìàíäà íà óíè÷òîæåíèå ïîòîêà
			{
				break;
			}
		}
	}
	else
	{
		MessageBoxW(NULL,L"Файл не является разделом NTFS",L"Ошибка!!!!",MB_OK);
		return;
	}

	 // Завершить поиск
	MySearchThread->Terminate( );
	iterFileSystem.Close();
	delete[] dataBuffer;
}
//---------------------------------------------------------------------------
