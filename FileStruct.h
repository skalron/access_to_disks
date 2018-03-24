#include <Windows.h>
#pragma pack(push, 1)    // включить однобайтовое выравнивание
typedef struct
{
	BYTE machInstruction[ 3 ];
	BYTE OEMName[8];
	UINT16 bytesPerSector;
	BYTE sectorPerCluster;
	BYTE padding1[2];
	BYTE padding2[5];
	BYTE typeStore;
	BYTE padding3[2];
	BYTE padding4[8];
	BYTE padding5[4];
	BYTE padding6[4];
	ULONGLONG totalSectors;
	ULONGLONG clusterMFT;
	ULONGLONG clusterDataMFT;
	BYTE sizeMFT;
	BYTE padding7[3];
	BYTE sizeIndex;
	BYTE padding8[3];
	ULONGLONG serialNumber;
	BYTE padding9[ 4 ];
	BYTE padding10[ 426 ];
	BYTE signature[ 2 ];

} BootStructNTFS;
#pragma pack(pop)  // восставноить обычное выравнивание


typedef struct
{
	__int64 currentCluster;
	BYTE signature[5];
	BYTE extensionFile[5];
} FileStruct;
