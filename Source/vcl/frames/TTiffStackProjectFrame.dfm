object TiffStackProjectFrame: TTiffStackProjectFrame
  Left = 0
  Top = 0
  Width = 1195
  Height = 781
  Align = alClient
  TabOrder = 0
  ExplicitWidth = 451
  ExplicitHeight = 305
  object Panel1: TPanel
    Left = 353
    Top = 0
    Width = 842
    Height = 781
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 1010
    ExplicitTop = 56
    ExplicitWidth = 185
    ExplicitHeight = 41
    object ScrollBar1: TScrollBar
      Left = 1
      Top = 763
      Width = 840
      Height = 17
      Align = alBottom
      PageSize = 0
      TabOrder = 0
      ExplicitLeft = 360
      ExplicitTop = 736
      ExplicitWidth = 121
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 353
    Height = 781
    Align = alLeft
    Caption = 'Panel2'
    TabOrder = 1
    ExplicitTop = 105
    ExplicitHeight = 676
    object GroupBox1: TGroupBox
      Left = 1
      Top = 106
      Width = 351
      Height = 674
      Align = alClient
      Caption = 'TiffStack properties'
      TabOrder = 0
      ExplicitLeft = 353
      ExplicitTop = 105
      ExplicitWidth = 842
      ExplicitHeight = 676
      object Memo1: TMemo
        Left = 2
        Top = 15
        Width = 347
        Height = 657
        Align = alClient
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        ExplicitWidth = 838
        ExplicitHeight = 659
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 1
      Width = 351
      Height = 105
      Align = alTop
      Caption = 'TiffStack: '
      TabOrder = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 1195
      object Button1: TButton
        Left = 16
        Top = 32
        Width = 105
        Height = 25
        Caption = 'Open in Explorer'
        TabOrder = 0
        OnClick = Button1Click
      end
    end
  end
end
