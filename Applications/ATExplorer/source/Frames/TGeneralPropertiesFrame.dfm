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
    Caption = 'Default Docker and Render Backends'
    TabOrder = 1
    object Label7: TLabel
      Left = 10
      Top = 29
      Width = 158
      Height = 13
      Caption = 'Render Python Docker Container'
    end
    object Label8: TLabel
      Left = 244
      Top = 29
      Width = 73
      Height = 13
      Caption = 'Render Service'
    end
    object RenderPythonContainersCB: TComboBox
      Left = 10
      Top = 48
      Width = 207
      Height = 21
      TabOrder = 0
      Text = 'RenderPythonContainersCB'
      OnChange = RenderPythonContainersCBChange
    end
    object RenderServicesCB: TComboBox
      Left = 244
      Top = 48
      Width = 215
      Height = 21
      TabOrder = 1
      Text = 'ComboBox1'
    end
  end
end
