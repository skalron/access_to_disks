#include "FileStruct.h"
class NTFS_FileSystem
{
	protected:
		HANDLE fileHandle;  // дескриптор файла
		UINT16 bytesPerSector; //количество байтов в секторе
		BYTE sectorPerCluster; // количество секторов в кластере
		ULONGLONG totalSectors;
		BYTE OEMName[9];

	 public:
		NTFS_FileSystem();  //конструктор
		bool Open(WCHAR* fileName);   // открытие диска
		void Close( ); // закрытие
		bool ReadBootSector();   // чтение загрузочного сектора
		bool ReadCluster(ULONGLONG startCluster, DWORD numberOfCluster, BYTE* outBuffer );  // чтения кластера

		void SetFileHandle(HANDLE fileHandler);
		ULONGLONG GetTotalSectors();  // количество секторов
		ULONGLONG GetClusterMFT();   //-------удалить
		BYTE GetSectorPerCluster();  //количество секторов в калстере
		BYTE * GetOEMName();
		UINT16 GetBytesPerSector();  // количество байтов в секторе
		HANDLE GetFileHandle();      //    получение дескриптора файла
		void errors();

};
