object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'RenderDB Manager'
  ClientHeight = 751
  ClientWidth = 1216
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 545
    Width = 1216
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 64
    ExplicitTop = 565
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 1216
    Height = 545
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'PointMatches'
      object ListBox1: TListBox
        Left = 0
        Top = 0
        Width = 145
        Height = 517
        Align = alLeft
        ItemHeight = 13
        TabOrder = 0
      end
      object Button1: TButton
        Left = 216
        Top = 431
        Width = 75
        Height = 25
        Caption = 'Refresh'
        TabOrder = 1
      end
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 548
    Width = 1216
    Height = 203
    Align = alBottom
    TabOrder = 1
    inline TLogMemoFrame1: TLogMemoFrame
      Left = 1
      Top = 1
      Width = 1214
      Height = 201
      Align = alClient
      TabOrder = 0
      ExplicitLeft = 1
      ExplicitTop = 1
      ExplicitWidth = 1214
      ExplicitHeight = 201
      inherited Panel1: TPanel
        Width = 1214
        Height = 201
        ExplicitWidth = 1214
        ExplicitHeight = 201
        inherited GroupBox1: TGroupBox
          Width = 1212
          ExplicitWidth = 1212
        end
        inherited infoMemo: TMemo
          Width = 1212
          Height = 149
          ExplicitWidth = 1212
          ExplicitHeight = 149
        end
      end
    end
  end
end
