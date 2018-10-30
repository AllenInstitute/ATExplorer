object ATIFDataProjectFrame: TATIFDataProjectFrame
  Left = 0
  Top = 0
  Width = 972
  Height = 676
  Align = alClient
  TabOrder = 0
  ExplicitWidth = 451
  ExplicitHeight = 305
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 972
    Height = 241
    Align = alTop
    Caption = 'Raw AT IF Data Properties'
    TabOrder = 0
    ExplicitWidth = 451
    DesignSize = (
      972
      241)
    object DataRootFolderE: TSTDStringLabeledEdit
      Left = 16
      Top = 42
      Width = 938
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 82
      EditLabel.Height = 13
      EditLabel.Caption = 'DataRootFolderE'
      Enabled = False
      TabOrder = 0
      ExplicitWidth = 417
    end
    object ScanDataBtn: TButton
      Left = 16
      Top = 80
      Width = 81
      Height = 25
      Caption = 'Scan Data'
      TabOrder = 1
      OnClick = ScanDataBtnClick
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 120
      Width = 417
      Height = 105
      Caption = 'Quick Info'
      TabOrder = 2
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
    object PopulatePB: TProgressBar
      Left = 103
      Top = 88
      Width = 851
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 3
      ExplicitWidth = 330
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 241
    Width = 972
    Height = 435
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 451
    ExplicitHeight = 64
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 970
      Height = 433
      ActivePage = TabSheet1
      Align = alClient
      TabOrder = 0
      ExplicitHeight = 435
      object TabSheet1: TTabSheet
        Caption = 'State Tables'
        ExplicitWidth = 285
        ExplicitHeight = 169
        object FileListBox1: TFileListBox
          Left = 0
          Top = 41
          Width = 361
          Height = 364
          Align = alLeft
          ItemHeight = 13
          Mask = '*'
          TabOrder = 0
          OnChange = FileListBox1Change
          ExplicitTop = 0
          ExplicitHeight = 407
        end
        object FileMemo: TMemo
          Left = 361
          Top = 41
          Width = 601
          Height = 364
          Align = alClient
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 1
          WordWrap = False
          ExplicitTop = 0
          ExplicitHeight = 407
        end
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 962
          Height = 41
          Align = alTop
          TabOrder = 2
          ExplicitLeft = 184
          ExplicitTop = 32
          ExplicitWidth = 185
          object CreateStateTablesBtn: TButton
            Left = 11
            Top = 10
            Width = 121
            Height = 25
            Caption = 'Generate State Tables'
            TabOrder = 0
            OnClick = CreateStateTablesBtnClick
          end
          object CreateRenderStacksBtn: TButton
            Left = 138
            Top = 10
            Width = 128
            Height = 25
            Caption = 'Generate Render Stacks'
            TabOrder = 1
            OnClick = CreateStateTablesBtnClick
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Medians'
        ImageIndex = 1
        ExplicitHeight = 407
        object FileListBox2: TFileListBox
          Left = 0
          Top = 0
          Width = 281
          Height = 405
          Align = alLeft
          ItemHeight = 13
          Mask = '*'
          TabOrder = 0
          OnChange = FileListBox1Change
          ExplicitHeight = 407
        end
      end
    end
  end
end
