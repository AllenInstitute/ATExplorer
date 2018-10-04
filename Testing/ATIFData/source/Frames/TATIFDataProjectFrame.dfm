object ATIFDataProjectFrame: TATIFDataProjectFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 305
  Align = alClient
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 451
    Height = 305
    Align = alClient
    Caption = 'AT IF Data Properties'
    TabOrder = 0
    DesignSize = (
      451
      305)
    object DataRootFolderE: TSTDStringLabeledEdit
      Left = 16
      Top = 42
      Width = 417
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 82
      EditLabel.Height = 13
      EditLabel.Caption = 'DataRootFolderE'
      Enabled = False
      TabOrder = 0
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
      Top = 128
      Width = 417
      Height = 105
      Caption = 'Quick Info'
      TabOrder = 2
      object Label1: TLabel
        Left = 12
        Top = 22
        Width = 98
        Height = 13
        Caption = 'Number of Ribbons: '
      end
      object Label2: TLabel
        Left = 12
        Top = 48
        Width = 100
        Height = 13
        Caption = 'Number of Sections: '
      end
      object Label3: TLabel
        Left = 236
        Top = 48
        Width = 108
        Height = 13
        Caption = 'Total Number of Tiles: '
      end
      object Label4: TLabel
        Left = 236
        Top = 22
        Width = 98
        Height = 13
        Caption = 'Number of Sessions:'
      end
      object NrOfRibbonsLbl: TLabel
        Left = 128
        Top = 22
        Width = 6
        Height = 13
        Caption = '0'
      end
      object NrOfSectionsLbl: TLabel
        Left = 128
        Top = 48
        Width = 6
        Height = 13
        Caption = '0'
      end
      object NrOfSessionsLbl: TLabel
        Left = 360
        Top = 22
        Width = 17
        Height = 13
        Caption = '0'
      end
      object NrOfTilesLbl: TLabel
        Left = 360
        Top = 48
        Width = 17
        Height = 13
        Caption = '0'
      end
    end
  end
end
