#include "NTFS.h"

#include "stdio.h"
#include "Unit1.h"
//����������
NTFS_FileSystem::NTFS_FileSystem()
{

	fileHandle = 0;
	bytesPerSector = 0;
	sectorPerCluster = 0;
	totalSectors = 0;


}
//---------------------------------------------------------------------------
//�������� �����
bool NTFS_FileSystem::Open(WCHAR *fileName)
{

   fileHandle = CreateFileW(
			fileName, // ��� ����� (WCHAR*)
			GENERIC_READ,	  // ����� �������
			FILE_SHARE_READ | FILE_SHARE_WRITE, // ����� ���������� ������
			NULL, // �������� ������������
			OPEN_EXISTING, // ������ ��������
			FILE_ATTRIBUTE_NORMAL, // ����� � ��������
			NULL // ��������� (�������������) ����� ������� � ������� ������� GENERIC_READ.
		);

if(fileHandle == INVALID_HANDLE_VALUE)
{
		MessageBoxW( NULL, L"������ �������� �����", L"������!!!", MB_OK );
		return false;
}

	return true;
}
//---------------------------------------------------------------------------
//�������� �����
void NTFS_FileSystem::Close()
{
 if (fileHandle == 0)
 {
	MessageBox(NULL, L"���� �� ������", L"������!!!", MB_OK );
 }
 CloseHandle(fileHandle);

}
//---------------------------------------------------------------------------
// ������ ������������ �������
bool NTFS_FileSystem::ReadBootSector()
{
	if ( fileHandle == 0 )
	{
		 MessageBoxW(NULL, L"��� �������� ������", L"������!!!", MB_OK);
		 return false;
	}

	BYTE bootSector[512]; // ����� ������������ �������
	ULONGLONG startOffset = 0;
	DWORD bytesToRead = 512;  // ������� �������
	DWORD bytesRead;  //  ������� ���� ������� �������

//��������� LARGE_INTEGER ������������ ��� ������������� 64-� ������� ��������� ����������������� ��������.
//LowPart	���������� ������� 32 ����
//HighPart	���������� ������� 32 ����
//QuadPart	���������� 64-� ������ �������� �����

	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	unsigned long currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart,&sectorOffset.HighPart, FILE_BEGIN);

	if (currentPosition != sectorOffset.LowPart)
	{
		MessageBoxW(NULL, L"������ ��������������� ��� ������ ������������ �������", L"������!!!", MB_OK);
		return false;
	}

// ������ ����������� ������, ���� �����-�� ������ ������������ �
	bool readResult = ReadFile( fileHandle, bootSector, bytesToRead, &bytesRead, NULL);
	if ( !readResult || bytesRead != bytesToRead )
	{
		MessageBoxW( NULL, L"������ ������ �����", L"������!!!", MB_OK );
		return false;
	}


	BootStructNTFS* bootParam;
	bootParam = (BootStructNTFS *) bootSector;
	bytesPerSector = bootParam->bytesPerSector;  // ���������� ������ � �������
	sectorPerCluster = bootParam->sectorPerCluster;    // ���������� �������� � ��������
	totalSectors = bootParam->totalSectors;       // ����� ��������
	strcpy_s(OEMName, strlen(bootParam->OEMName )+1, bootParam->OEMName);

	char *print = new char[512];

	sprintf(print,"���������� ���� � �������: %d\n"
				  "���������� �������� � ��������: %d\n"
				  "����� ���������� ��������: %d\n"
				  ,bytesPerSector,sectorPerCluster,totalSectors);
	IndexForm->PrintLabel->Caption = print;



	return true;

}

bool NTFS_FileSystem::ReadCluster(ULONGLONG startCluster,DWORD numberOfCluster, BYTE* outBuffer )
{
	if (fileHandle == 0 || bytesPerSector == 0 || sectorPerCluster == 0)
	{
		MessageBoxW( NULL, L"������ ������ �� ��� ������ ��� ������ �������", L"������!!!", MB_OK );
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
		MessageBoxW( NULL, L"������ ���������������� � �������", L"������!!!", MB_OK );
		return false;
	}

	bool readResult = ReadFile(fileHandle, outBuffer, bytesToRead,&bytesRead, NULL);

	if (!readResult || bytesRead != bytesToRead)
	{
		MessageBoxW( NULL, L"������ ������ ��������", L"������!!!", MB_OK );
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
	MessageBoxW( NULL, L"������ ���", L"������!!!", MB_OK );
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

