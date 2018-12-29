//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

  String Nz_kat;

  int  war = 0;
  int  pozKursoraR1, pozKursoraR2;
  int  blad;
  
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Panel3->Top = 20;
        Panel3->Left = 50;
        Panel3->Width = 531 ;

        Form1->ClientHeight = (2 * Panel3->Top) + Panel3->Height;
        Form1->ClientWidth = (2 * Panel3->Left) + Panel3->Width;

  TRect R1;
   int LeftMargin = 10;
   int RightMargin = 5;
   R1 = RichEdit1->ClientRect;
   R1.Left = R1.Left + LeftMargin;
   R1.Top = R1.Top + 5;
   R1.Bottom = R1.Bottom - 2;
   R1.Right = R1.Right - RightMargin;
   SendMessage(RichEdit1->Handle, EM_SETRECT, 0, Longint(&R1));

 TRect R2;
   int LeftMargin2 = 10;
   int RightMargin2 = 5;
   R2 = RichEdit2->ClientRect;
   R2.Left = R2.Left + LeftMargin2;
   R2.Top = R2.Top + 5;
   R2.Bottom = R2.Bottom - 2;
   R2.Right = R2.Right - RightMargin2;
   SendMessage(RichEdit2->Handle, EM_SETRECT, 0, Longint(&R2));

   RichEdit1->Clear();
   RichEdit2->Clear();

   Label2->Caption = " --- ";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
   int Height;

   Height = (ClientHeight + 250) / 250 ;

   for (int Row = 0; Row <= 250 ; Row++)
   {
      Canvas->Brush->Color =(TColor) RGB(0, 250-Row, 0);

      Canvas->FillRect(Rect(0, Row * Height, ClientWidth, (Row + 1) * Height)) ;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
      Panel5->Visible = false;

      Memo1->SelectAll();
      Memo1->CopyToClipboard();

      RichEdit1->ReadOnly = false;
      RichEdit1->Clear();

      RichEdit1->PasteFromClipboard();

      RichEdit1->SelectAll();
      RichEdit1->SelAttributes->Color = clBlack;
      RichEdit1->SelAttributes->Size = 15;
      RichEdit1->SelAttributes->Name = "Arial";
      RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsUnderline ;
      RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style >> fsBold ;
      RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style >> fsItalic;

     RichEdit1->SelStart = 0;
     RichEdit2->Clear();
     RichEdit2->SelStart = 0;

     RichEdit1->ReadOnly = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel4Click(TObject *Sender)
{
        Memo1->Clear();
        Memo1->PasteFromClipboard();

        Button2->Click();       // -- 'Button2 - PasteFromClipboard'

        RichEdit1->SelStart = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RichEdit2Change(TObject *Sender)
{
    if ( RichEdit2->SelStart == 0 ) war = 0;

    if ( war == 2 )
     {
       pozKursoraR2 = RichEdit2->SelStart  ;

       RichEdit1->SelStart = pozKursoraR2 ;
       RichEdit1->SelLength =   -1;

       RichEdit2->SelStart = pozKursoraR2 ;
       RichEdit2->SelLength =   -1;

       Edit1->Text = RichEdit1->SelText;
       Edit2->Text = RichEdit2->SelText;

        if ( RichEdit1->SelText ==  RichEdit2->SelText )
         {
           RichEdit1->SelAttributes->Color = clGreen;
           RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsUnderline ;
           RichEdit1->SelStart = pozKursoraR2 ;
         }
        else
         {
            blad = blad + 1;
            Label2->Caption = blad;

           RichEdit1->SelAttributes->Color = clRed;
           RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsUnderline ;
           RichEdit1->SelStart = pozKursoraR2 ;
         }

          int NrStr = RichEdit1->SelStart;
          if ( NrStr == RichEdit1->Text.Length() )
          {
            Panel5->Visible = true;
            Panel5->Top = 315;  Panel5->Left = 110 ;
            Panel5->Caption = "Yoy made " + Label2->Caption + " mistakes";
          }
          else
          {
            RichEdit2->SelStart = pozKursoraR2;
            RichEdit1->Perform(EM_SCROLLCARET, 0, 0);
          }
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RichEdit2KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
         if (Key == VK_BACK )
         {
           war = 0 ;

           RichEdit1->SelStart = RichEdit2->SelStart;
           RichEdit1->SelLength = -1;
           RichEdit1->SelAttributes->Color = clBlack;
           RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsUnderline ;
         }
        else    war = 2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RichEdit2MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
      RichEdit2->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RichEdit3MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
      RichEdit2->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel2Click(TObject *Sender)
{
      Panel5->Visible = false;

      RichEdit1->ReadOnly = false;
      Label2->Caption = " - ";

      RichEdit2->Clear();
        blad = 0;

      RichEdit1->SelectAll();
      RichEdit1->SelAttributes->Color = clBlack;
      RichEdit1->SelAttributes->Size = 15;
      RichEdit1->SelAttributes->Name = "Arial";
      RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsUnderline ;

      RichEdit1->SelStart = 0;
      RichEdit2->SelStart = 0;

      RichEdit1->ReadOnly = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel6Click(TObject *Sender)
{
  if ( Panel7->Visible == true ) Panel7->Hide();
  else  Panel7->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel8Click(TObject *Sender)
{
    Panel7->Hide();
}
//---------------------------------------------------------------------------

