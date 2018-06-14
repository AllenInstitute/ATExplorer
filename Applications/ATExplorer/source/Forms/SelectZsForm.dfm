object Form6: TForm6
  Left = 0
  Top = 0
  Caption = 'Select Z'#39's'
  ClientHeight = 489
  ClientWidth = 634
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 634
    Height = 426
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 168
    ExplicitTop = 120
    ExplicitWidth = 553
    ExplicitHeight = 257
    object Splitter1: TSplitter
      Left = 243
      Top = 1
      Width = 164
      Height = 424
      ExplicitLeft = 132
      ExplicitHeight = 255
    end
    object ListBox1: TListBox
      Left = 1
      Top = 1
      Width = 242
      Height = 424
      Align = alLeft
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 0
    end
    object ListBox2: TListBox
      Left = 407
      Top = 1
      Width = 226
      Height = 424
      Align = alClient
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 1
      ExplicitLeft = 293
      ExplicitWidth = 259
      ExplicitHeight = 255
    end
    object Button1: TButton
      Left = 168
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Button1'
      TabOrder = 2
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 426
    Width = 634
    Height = 63
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 504
    ExplicitWidth = 825
    DesignSize = (
      634
      63)
    object Button2: TButton
      Left = 549
      Top = 8
      Width = 75
      Height = 50
      Anchors = [akTop, akRight]
      Caption = 'OK'
      TabOrder = 0
      ExplicitLeft = 728
    end
    object Button3: TButton
      Left = 453
      Top = 8
      Width = 75
      Height = 50
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      TabOrder = 1
      ExplicitLeft = 632
    end
  end
end
