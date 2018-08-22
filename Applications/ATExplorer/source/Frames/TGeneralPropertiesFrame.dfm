object GeneralPropertiesFrame: TGeneralPropertiesFrame
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
    Caption = 'General'
    TabOrder = 0
    object GroupBox4: TGroupBox
      Left = 2
      Top = 131
      Width = 447
      Height = 176
      Align = alTop
      Caption = 'Render Service Settings'
      TabOrder = 0
      DesignSize = (
        447
        176)
      object BaseURLE: TSTDStringLabeledEdit
        Left = 13
        Top = 42
        Width = 104
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 45
        EditLabel.Height = 13
        EditLabel.Caption = 'Base URL'
        TabOrder = 0
        Text = 'http://localhost'
        Value = 'http://localhost'
      end
      object TestRenderServiceBtn: TButton
        Left = 123
        Top = 40
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = 'Test'
        TabOrder = 1
      end
      object maxTileSpecsToRenderE: TIntegerLabeledEdit
        Left = 16
        Top = 144
        Width = 121
        Height = 21
        EditLabel.Width = 121
        EditLabel.Height = 13
        EditLabel.Caption = 'Max # of Tiles To Render'
        TabOrder = 2
        Text = '150'
        Value = 150
      end
      object RenderPort: TIntegerLabeledEdit
        Left = 16
        Top = 88
        Width = 121
        Height = 21
        EditLabel.Width = 55
        EditLabel.Height = 13
        EditLabel.Caption = 'RenderPort'
        TabOrder = 3
        Text = '80'
        Value = 80
      end
    end
    object Panel1: TPanel
      Left = 2
      Top = 15
      Width = 447
      Height = 116
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        447
        116)
      object ConnectSSHServersOnStartupCB: TPropertyCheckBox
        Left = 16
        Top = 73
        Width = 176
        Height = 17
        Caption = 'Connect SSH Servers On Startup'
        TabOrder = 0
      end
      object ImageCacheFolderE: TSTDStringLabeledEdit
        Left = 16
        Top = 29
        Width = 380
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 102
        EditLabel.Height = 13
        EditLabel.Caption = 'Root folder for cache'
        TabOrder = 1
        Text = 'c:\ImageCache'
        Value = 'c:\ImageCache'
      end
      object mBrowseForCacheFolder: TButton
        Left = 402
        Top = 27
        Width = 33
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '...'
        TabOrder = 2
        OnClick = mBrowseForCacheFolderClick
      end
    end
  end
end
