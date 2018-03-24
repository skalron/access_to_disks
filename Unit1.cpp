//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Unit1.h"
#include "NTFS.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TIndexForm* IndexForm;
//---------------------------------------------------------------------------
__fastcall TIndexForm::TIndexForm(TComponent* Owner)
	: TForm(Owner)
{
VirtualStringTree1->NodeDataSize = sizeof(FileStruct);
}
//---------------------------------------------------------------------------
void __fastcall TIndexForm::LaunchButtonClick(TObject *Sender)
{
  VirtualStringTree1->Clear();
  myIteratorThread = new IteratorThread(EditPath->Text.c_str(), false);
}
//---------------------------------------------------------------------------

void __fastcall TIndexForm::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
		if (!Node)
	{
		MessageBoxW(NULL,L"Ошибка выбора Node",L"Ошибка",MB_OK);
		return;
	}
	FileStruct * nodeData = (FileStruct *)Sender->GetNodeData(Node);
	switch (Column)
	{
	case 0:
		CellText = nodeData->currentCluster;
		break;
	case 1:
		CellText = (char *)nodeData->signature;
		break;
	case 2:
		CellText = (char *)nodeData->extensionFile;
		break;
	}
}
//---------------------------------------------------------------------------



void __fastcall TIndexForm::StopButtonClick(TObject *Sender)
{
   myIteratorThread->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TIndexForm::ClearButtonClick(TObject *Sender)
{
   VirtualStringTree1->Clear();
   PrintLabel->Caption = "";
   ProgressBar->Position = 0;
}
//---------------------------------------------------------------------------

