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
    object Button2: TButton
      Left = 742
      Top = 9
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 1
      OnClick = Button2Click
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
      Left = 161
      Top = 1
      Height = 327
      ExplicitLeft = 152
      ExplicitTop = -4
    end
    object Zs_GB: TGroupBox
      Left = 443
      Top = 1
      Width = 94
      Height = 327
      Align = alLeft
      Caption = 'Sections'
      TabOrder = 0
      ExplicitLeft = 440
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
    object RenderStacksCB: TCheckListBox
      Left = 1
      Top = 1
      Width = 160
      Height = 327
      Align = alLeft
      ItemHeight = 13
      TabOrder = 1
      OnClick = RenderStacksCBClick
    end
    object Panel2: TPanel
      Left = 164
      Top = 1
      Width = 279
      Height = 327
      Align = alLeft
      TabOrder = 2
      ExplicitLeft = 161
      object imageParasGB: TGroupBox
        Left = 1
        Top = 175
        Width = 277
        Height = 151
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
        end
      end
      object GroupBox1: TGroupBox
        Left = 1
        Top = 1
        Width = 277
        Height = 174
        Align = alClient
        Caption = 'Image Output'
        TabOrder = 1
        object Label4: TLabel
          Left = 71
          Top = 59
          Width = 55
          Height = 13
          Caption = 'Image type'
          Enabled = False
        end
        object ImageTypeRG: TRadioGroup
          Left = 5
          Top = 14
          Width = 133
          Height = 99
          Caption = 'Image Format'
          ItemIndex = 0
          Items.Strings = (
            'JPEG'
            'TIFF'
            'PNG')
          TabOrder = 1
          OnClick = ImageTypeRGClick
        end
        object ImageTypeCB: TComboBox
          Left = 71
          Top = 78
          Width = 55
          Height = 21
          Style = csDropDownList
          Enabled = False
          ItemIndex = 1
          TabOrder = 0
          Text = '16 bit'
          Visible = False
          Items.Strings = (
            '24 bit (RGB)'
            '16 bit'
            '8 bit')
        end
        object RemoveSectionsCB: TPropertyCheckBox
          Left = 5
          Top = 119
          Width = 148
          Height = 17
          Caption = 'Cleanup Duplicates'
          TabOrder = 2
        end
      end
    end
    object ThreadsPanel: TScrollBox
      Left = 537
      Top = 1
      Width = 287
      Height = 327
      Align = alClient
      TabOrder = 3
      ExplicitLeft = 534
      ExplicitWidth = 290
    end
  end
  object IdHTTP1: TIdHTTP
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 432
    Top = 24
  end
  object CreateStacksTimer: TTimer
    Interval = 150
    OnTimer = CreateStacksTimerTimer
    Left = 528
    Top = 48
  end
end
