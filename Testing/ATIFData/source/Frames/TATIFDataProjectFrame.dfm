object ATIFDataProjectFrame: TATIFDataProjectFrame
  Left = 0
  Top = 0
  Width = 700
  Height = 302
  Align = alClient
  TabOrder = 0
  ExplicitWidth = 451
  ExplicitHeight = 305
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 700
    Height = 302
    Align = alClient
    Caption = 'AT IF Data Properties'
    TabOrder = 0
    ExplicitWidth = 451
    ExplicitHeight = 305
    DesignSize = (
      700
      302)
    object DataRootFolderE: TSTDStringLabeledEdit
      Left = 16
      Top = 42
      Width = 666
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
        Top = 41
        Width = 101
        Height = 13
        Caption = 'Number of Channels:'
      end
      object NrOfChannelsLbl: TLabel
        Left = 360
        Top = 41
        Width = 6
        Height = 13
        Caption = '0'
      end
    end
    object PopulatePB: TProgressBar
      Left = 103
      Top = 88
      Width = 579
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 3
    end
  end
end
