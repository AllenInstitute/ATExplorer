object GeneralPropertiesFrame: TGeneralPropertiesFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 305
  Align = alClient
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 451
    Height = 57
    Align = alTop
    Caption = 'General'
    TabOrder = 0
    Visible = False
    object ConnectSSHServersOnStartupCB: TPropertyCheckBox
      Left = 16
      Top = 25
      Width = 176
      Height = 17
      Caption = 'Connect SSH Servers On Startup'
      TabOrder = 0
      Visible = False
    end
  end
  object GroupBox4: TGroupBox
    Left = 0
    Top = 129
    Width = 451
    Height = 176
    Align = alClient
    Caption = 'Render Service Settings'
    TabOrder = 1
    DesignSize = (
      451
      176)
    object BaseURLE: TSTDStringLabeledEdit
      Left = 13
      Top = 42
      Width = 371
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 45
      EditLabel.Height = 13
      EditLabel.Caption = 'Base URL'
      TabOrder = 0
      Text = 'http://ibs-forrestc-ux1'
      Value = 'http://ibs-forrestc-ux1'
    end
    object TestRenderServiceBtn: TButton
      Left = 390
      Top = 40
      Width = 52
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Test'
      TabOrder = 1
      OnClick = TestRenderServiceBtnClick
    end
    object maxTileSpecsToRenderE: TIntegerLabeledEdit
      Left = 152
      Top = 88
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
      Left = 13
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
  object GroupBox2: TGroupBox
    Left = 0
    Top = 57
    Width = 451
    Height = 72
    Align = alTop
    Caption = 'Image Magick'
    TabOrder = 2
    DesignSize = (
      451
      72)
    object ImageMagickPathE: TSTDStringLabeledEdit
      Left = 16
      Top = 41
      Width = 392
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 90
      EditLabel.Height = 13
      EditLabel.Caption = 'Image Magick Path'
      TabOrder = 0
    end
    object BrowseForImageMagickPathBtn: TButton
      Left = 414
      Top = 41
      Width = 28
      Height = 21
      Anchors = [akTop, akRight]
      Caption = '...'
      TabOrder = 1
      OnClick = BrowseForFolderClick
    end
  end
end
