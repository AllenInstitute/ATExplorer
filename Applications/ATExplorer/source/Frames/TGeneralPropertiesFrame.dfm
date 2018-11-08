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
    Height = 105
    Align = alTop
    Caption = 'General'
    TabOrder = 0
    Visible = False
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 105
    Width = 451
    Height = 72
    Align = alTop
    Caption = 'Image Magick'
    TabOrder = 1
    ExplicitTop = 57
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
