#include "FileStruct.h"
class NTFS_FileSystem
{
	protected:
		HANDLE fileHandle;  // ���������� �����
		UINT16 bytesPerSector; //���������� ������ � �������
		BYTE sectorPerCluster; // ���������� �������� � ��������
		ULONGLONG totalSectors;
		BYTE OEMName[9];

	 public:
		NTFS_FileSystem();  //�����������
		bool Open(WCHAR* fileName);   // �������� �����
		void Close( ); // ��������
		bool ReadBootSector();   // ������ ������������ �������
		bool ReadCluster(ULONGLONG startCluster, DWORD numberOfCluster, BYTE* outBuffer );  // ������ ��������

		void SetFileHandle(HANDLE fileHandler);
		ULONGLONG GetTotalSectors();  // ���������� ��������
		ULONGLONG GetClusterMFT();   //-------�������
		BYTE GetSectorPerCluster();  //���������� �������� � ��������
		BYTE * GetOEMName();
		UINT16 GetBytesPerSector();  // ���������� ������ � �������
		HANDLE GetFileHandle();      //    ��������� ����������� �����
		void errors();

};
