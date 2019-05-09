object GeneralPropertiesFrame: TGeneralPropertiesFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 305
  Align = alClient
  AutoSize = True
  TabOrder = 0
  object GroupBox2: TGroupBox
    Left = 0
    Top = 105
    Width = 451
    Height = 72
    Align = alTop
    Caption = 'Image Magick'
    TabOrder = 0
    DesignSize = (
      451
      72)
    object ImageMagickPathE: TSTDStringLabeledEdit
      Left = 16
      Top = 41
      Width = 354
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 90
      EditLabel.Height = 13
      EditLabel.Caption = 'Image Magick Path'
      TabOrder = 0
    end
    object BrowseForImageMagickPathBtn: TButton
      Left = 376
      Top = 41
      Width = 28
      Height = 21
      Anchors = [akTop, akRight]
      Caption = '...'
      TabOrder = 1
      OnClick = BrowseForFolderClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 0
    Width = 451
    Height = 105
    Align = alTop
    Caption = 'Render Backends'
    TabOrder = 1
    DesignSize = (
      451
      105)
    object Label8: TLabel
      Left = 16
      Top = 21
      Width = 73
      Height = 13
      Caption = 'Render Service'
    end
    object RenderServicesCB: TComboBox
      Left = 16
      Top = 40
      Width = 354
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      Text = 'ComboBox1'
    end
  end
end
