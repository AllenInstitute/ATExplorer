object CreateLocalVolumesForm: TCreateLocalVolumesForm
  Left = 0
  Top = 0
  Caption = 'Create Volumes'
  ClientHeight = 373
  ClientWidth = 825
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 329
    Width = 825
    Height = 44
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      825
      44)
    object RunBtn: TButton
      Left = 7
      Top = 9
      Width = 75
      Height = 25
      Caption = 'Run'
      Enabled = False
      TabOrder = 0
      OnClick = RunBtnClick
    end
    object CloseBtn: TButton
      Left = 742
      Top = 9
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 1
      OnClick = CloseBtnClick
    end
    object RemoveSectionsCB: TPropertyCheckBox
      Left = 108
      Top = 17
      Width = 148
      Height = 17
      Caption = 'Cleanup Duplicates'
      TabOrder = 2
    end
  end
  object MainPanel: TPanel
    Left = 0
    Top = 0
    Width = 825
    Height = 329
    Align = alClient
    Constraints.MinHeight = 311
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 186
      Top = 1
      Height = 327
      ExplicitLeft = 152
      ExplicitTop = -4
    end
    object Zs_GB: TGroupBox
      Left = 468
      Top = 1
      Width = 94
      Height = 327
      Align = alLeft
      Caption = 'Sections'
      TabOrder = 0
      object mZs: TCheckListBox
        Left = 2
        Top = 15
        Width = 90
        Height = 310
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
      end
    end
    object Panel2: TPanel
      Left = 189
      Top = 1
      Width = 279
      Height = 327
      Align = alLeft
      TabOrder = 1
      object imageParasGB: TGroupBox
        Left = 1
        Top = 160
        Width = 277
        Height = 166
        Align = alBottom
        Caption = 'Region of Interest (ROI)'
        TabOrder = 0
        object mScaleE: TFloatLabeledEdit
          Left = 16
          Top = 34
          Width = 50
          Height = 21
          EditLabel.Width = 25
          EditLabel.Height = 13
          EditLabel.Caption = 'Scale'
          TabOrder = 0
          Text = '0.0500'
          OnKeyDown = ROIChange
          Value = 0.050000000000000000
        end
        object Width: TIntegerLabeledEdit
          Left = 17
          Top = 122
          Width = 49
          Height = 21
          EditLabel.Width = 28
          EditLabel.Height = 13
          EditLabel.Caption = 'Width'
          TabOrder = 3
          Text = '12000'
          OnKeyDown = ROIChange
          Value = 12000
        end
        object Height: TIntegerLabeledEdit
          Left = 88
          Top = 122
          Width = 50
          Height = 21
          EditLabel.Width = 31
          EditLabel.Height = 13
          EditLabel.Caption = 'Height'
          TabOrder = 4
          Text = '32000'
          OnKeyDown = ROIChange
          Value = 32000
        end
        object XCoordE: TIntegerLabeledEdit
          Left = 17
          Top = 76
          Width = 49
          Height = 21
          EditLabel.Width = 6
          EditLabel.Height = 13
          EditLabel.Caption = 'X'
          TabOrder = 1
          Text = '8000'
          OnKeyDown = ROIChange
          Value = 8000
        end
        object YCoordE: TIntegerLabeledEdit
          Left = 88
          Top = 76
          Width = 50
          Height = 21
          EditLabel.Width = 6
          EditLabel.Height = 13
          EditLabel.Caption = 'Y'
          TabOrder = 2
          Text = '3200'
          OnKeyDown = ROIChange
          Value = 3200
        end
        object MaxIntensityE: TIntegerLabeledEdit
          Left = 157
          Top = 34
          Width = 66
          Height = 21
          EditLabel.Width = 66
          EditLabel.Height = 13
          EditLabel.Caption = 'Max Intensity'
          TabOrder = 5
          Text = '65535'
          OnKeyDown = ROIChange
          Value = 65535
        end
        object MinIntensityE: TIntegerLabeledEdit
          Left = 85
          Top = 34
          Width = 66
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'Min Intensity'
          TabOrder = 6
          Text = '0'
          OnKeyDown = ROIChange
        end
      end
      object GroupBox1: TGroupBox
        Left = 1
        Top = 1
        Width = 277
        Height = 159
        Align = alClient
        Caption = 'Image Output'
        TabOrder = 1
        ExplicitHeight = 168
        object ImageTypeRG: TRadioGroup
          Left = 5
          Top = 27
          Width = 100
          Height = 99
          Caption = 'Image Format'
          ItemIndex = 0
          Items.Strings = (
            'JPEG'
            'TIFF'
            'PNG')
          TabOrder = 0
        end
      end
    end
    object ThreadsPanel: TScrollBox
      Left = 562
      Top = 1
      Width = 262
      Height = 327
      Align = alClient
      TabOrder = 2
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 185
      Height = 327
      Align = alLeft
      TabOrder = 3
      object GroupBox3: TGroupBox
        Left = 1
        Top = 65
        Width = 183
        Height = 261
        Align = alClient
        Caption = 'Channels'
        TabOrder = 0
        object ChannelsCB: TCheckListBox
          Left = 2
          Top = 15
          Width = 179
          Height = 244
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
          OnClick = ChannelsCBClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 1
        Top = 1
        Width = 183
        Height = 64
        Align = alTop
        Caption = 'Stack'
        TabOrder = 1
        object StackCB: TComboBox
          Left = 5
          Top = 27
          Width = 173
          Height = 21
          Hint = 'Test'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Text = 'StackCB'
          OnChange = StackCBChange
        end
      end
    end
  end
  object CreateStacksTimer: TTimer
    Interval = 150
    OnTimer = CreateStacksTimerTimer
    Left = 528
    Top = 48
  end
end
