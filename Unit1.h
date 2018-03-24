//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.ComCtrls.hpp>
#include "IteratorThread.h"
//---------------------------------------------------------------------------
class TIndexForm : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree1;
	TEdit *EditPath;
	TButton *LaunchButton;
	TButton *StopButton;
	TProgressBar *ProgressBar;
	TLabel *PrintLabel;
	TButton *ClearButton;
	void __fastcall LaunchButtonClick(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall ClearButtonClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TIndexForm(TComponent* Owner);

	IteratorThread* myIteratorThread;
};
//---------------------------------------------------------------------------
extern PACKAGE TIndexForm *IndexForm;
//---------------------------------------------------------------------------
#endif
