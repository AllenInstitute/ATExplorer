object CreateATIFDataStateTablesForm: TCreateATIFDataStateTablesForm
  Left = 0
  Top = 0
  Caption = 'Create State Tables'
  ClientHeight = 336
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 8
    Top = 64
    Width = 417
    Height = 105
    Caption = 'Quick Data Info'
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 22
      Width = 98
      Height = 13
      Caption = 'Number of Ribbons: '
    end
    object Label2: TLabel
      Left = 10
      Top = 48
      Width = 100
      Height = 13
      Caption = 'Number of Sections: '
    end
    object Label3: TLabel
      Left = 10
      Top = 73
      Width = 81
      Height = 13
      Caption = 'Number of Tiles: '
    end
    object Label4: TLabel
      Left = 236
      Top = 22
      Width = 98
      Height = 13
      Caption = 'Number of Sessions:'
    end
    object NrOfRibbonsLbl: TLabel
      Left = 134
      Top = 22
      Width = 6
      Height = 13
      Caption = '0'
    end
    object NrOfSectionsLbl: TLabel
      Left = 134
      Top = 48
      Width = 6
      Height = 13
      Caption = '0'
    end
    object NrOfSessionsLbl: TLabel
      Left = 360
      Top = 22
      Width = 6
      Height = 13
      Caption = '0'
    end
    object NrOfTilesLbl: TLabel
      Left = 134
      Top = 73
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label5: TLabel
      Left = 236
      Top = 48
      Width = 101
      Height = 13
      Caption = 'Number of Channels:'
    end
    object NrOfChannelsLbl: TLabel
      Left = 360
      Top = 48
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label6: TLabel
      Left = 236
      Top = 73
      Width = 117
      Height = 13
      Caption = 'Number of State Tables:'
    end
    object StateTablesLbl: TLabel
      Left = 360
      Top = 73
      Width = 23
      Height = 13
      Caption = '0 (0)'
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 292
    Width = 635
    Height = 44
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      635
      44)
    object RunBtn: TButton
      Left = 7
      Top = 9
      Width = 75
      Height = 25
      Caption = 'Run'
      TabOrder = 0
      OnClick = RunBtnClick
    end
    object CloseBtn: TButton
      Left = 552
      Top = 9
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 1
    end
  end
  object PopulatePB: TProgressBar
    Left = 0
    Top = 275
    Width = 635
    Height = 17
    Align = alBottom
    TabOrder = 2
  end
  object DockerContainerE: TSTDStringLabeledEdit
    Left = 18
    Top = 24
    Width = 407
    Height = 21
    EditLabel.Width = 83
    EditLabel.Height = 13
    EditLabel.Caption = 'Docker Container'
    Enabled = False
    TabOrder = 3
    OnKeyDown = DockerContainerEKeyDown
  end
end
