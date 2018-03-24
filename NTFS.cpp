#include "NTFS.h"

#include "stdio.h"
#include "Unit1.h"
//констуртор
NTFS_FileSystem::NTFS_FileSystem()
{

	fileHandle = 0;
	bytesPerSector = 0;
	sectorPerCluster = 0;
	totalSectors = 0;


}
//---------------------------------------------------------------------------
//открытие диска
bool NTFS_FileSystem::Open(WCHAR *fileName)
{

   fileHandle = CreateFileW(
			fileName, // Имя файла (WCHAR*)
			GENERIC_READ,	  // Режим доступа
			FILE_SHARE_READ | FILE_SHARE_WRITE, // Режим совместной работы
			NULL, // Атрибуты безопасности
			OPEN_EXISTING, // Способ открытия
			FILE_ATTRIBUTE_NORMAL, // Флаги и атрибуты
			NULL // Описатель (идентификатор) файла шаблона с правами доступа GENERIC_READ.
		);

if(fileHandle == INVALID_HANDLE_VALUE)
{
		MessageBoxW( NULL, L"Ошибка открытия файла", L"Ошибка!!!", MB_OK );
		return false;
}

	return true;
}
//---------------------------------------------------------------------------
//закрытие диска
void NTFS_FileSystem::Close()
{
 if (fileHandle == 0)
 {
	MessageBox(NULL, L"Файл не открыт", L"Ошибка!!!", MB_OK );
 }
 CloseHandle(fileHandle);

}
//---------------------------------------------------------------------------
// чтение загрузочного сектора
bool NTFS_FileSystem::ReadBootSector()
{
	if ( fileHandle == 0 )
	{
		 MessageBoxW(NULL, L"Нет открытых файлов", L"Ошибка!!!", MB_OK);
		 return false;
	}

	BYTE bootSector[512]; // длина загрузочного сектора
	ULONGLONG startOffset = 0;
	DWORD bytesToRead = 512;  // сколько считать
	DWORD bytesRead;  //  сколько было реально считано

//Структура LARGE_INTEGER используется для представления 64-х битного знакового целочислительного значения.
//LowPart	Определяет младшее 32 бита
//HighPart	Определяет старшие 32 бита
//QuadPart	Определяет 64-х битное знаковое целое

	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	unsigned long currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart,&sectorOffset.HighPart, FILE_BEGIN);

	if (currentPosition != sectorOffset.LowPart)
	{
		MessageBoxW(NULL, L"Ошибка позицинирования при чтении загрузочного сектора", L"Ошибка!!!", MB_OK);
		return false;
	}

// читаем загрузочный сектор, если какая-то ошибка обрабатываем её
	bool readResult = ReadFile( fileHandle, bootSector, bytesToRead, &bytesRead, NULL);
	if ( !readResult || bytesRead != bytesToRead )
	{
		MessageBoxW( NULL, L"Ошибка чтения файла", L"Ошибка!!!", MB_OK );
		return false;
	}


	BootStructNTFS* bootParam;
	bootParam = (BootStructNTFS *) bootSector;
	bytesPerSector = bootParam->bytesPerSector;  // количество байтов в секторе
	sectorPerCluster = bootParam->sectorPerCluster;    // количество секторов в кластере
	totalSectors = bootParam->totalSectors;       // всего секторов
	strcpy_s(OEMName, strlen(bootParam->OEMName )+1, bootParam->OEMName);

	char *print = new char[512];

	sprintf(print,"Количество байт в секторе: %d\n"
				  "Количество секторов в кластере: %d\n"
				  "Общее количество секторов: %d\n"
				  ,bytesPerSector,sectorPerCluster,totalSectors);
	IndexForm->PrintLabel->Caption = print;



	return true;

}

bool NTFS_FileSystem::ReadCluster(ULONGLONG startCluster,DWORD numberOfCluster, BYTE* outBuffer )
{
	if (fileHandle == 0 || bytesPerSector == 0 || sectorPerCluster == 0)
	{
		MessageBoxW( NULL, L"Ошибка раздел не был открыт или открыт неверно", L"Ошибка!!!", MB_OK );
		return false;
	}
	ULONGLONG startOffset = bytesPerSector * sectorPerCluster * startCluster;
	DWORD bytesToRead = bytesPerSector * sectorPerCluster * numberOfCluster;
	DWORD bytesRead;
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	unsigned long currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);

	if (currentPosition != sectorOffset.LowPart)
	{
		MessageBoxW( NULL, L"Ошибка позиционирования в разделе", L"Ошибка!!!", MB_OK );
		return false;
	}

	bool readResult = ReadFile(fileHandle, outBuffer, bytesToRead,&bytesRead, NULL);

	if (!readResult || bytesRead != bytesToRead)
	{
		MessageBoxW( NULL, L"Ошибка чтения кластера", L"Ошибка!!!", MB_OK );
		return false;
	}

	return true;

}


void NTFS_FileSystem::SetFileHandle(HANDLE fileHandler)
{
	fileHandle = fileHandler;
}

void NTFS_FileSystem::errors()
{
	MessageBoxW( NULL, L"Ошибка бро", L"Ошибка!!!", MB_OK );
}

ULONGLONG NTFS_FileSystem::GetTotalSectors()
{
	return totalSectors;
}

BYTE NTFS_FileSystem::GetSectorPerCluster()
{
	return sectorPerCluster;
}
BYTE* NTFS_FileSystem::GetOEMName()
{
	return OEMName;
}


UINT16 NTFS_FileSystem::GetBytesPerSector()
{
	return bytesPerSector;
}

HANDLE NTFS_FileSystem::GetFileHandle()
{
	return fileHandle;
}

