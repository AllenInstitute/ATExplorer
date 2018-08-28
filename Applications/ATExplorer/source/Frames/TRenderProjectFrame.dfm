object RenderProjectFrame: TRenderProjectFrame
  Left = 0
  Top = 0
  Width = 972
  Height = 891
  TabOrder = 0
  object mLeftPanel: TPanel
    Left = 0
    Top = 0
    Width = 385
    Height = 891
    Align = alLeft
    TabOrder = 0
    ExplicitHeight = 914
    object ScrollBox1: TScrollBox
      Left = 1
      Top = 1
      Width = 287
      Height = 889
      Align = alClient
      DoubleBuffered = True
      ParentDoubleBuffered = False
      TabOrder = 0
      ExplicitHeight = 912
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 283
        Height = 185
        Align = alTop
        Caption = 'Project Selection'
        TabOrder = 0
        DesignSize = (
          283
          185)
        object Label1: TLabel
          Left = 16
          Top = 22
          Width = 32
          Height = 13
          Caption = 'Owner'
        end
        object Label2: TLabel
          Left = 17
          Top = 74
          Width = 34
          Height = 13
          Caption = 'Project'
        end
        object Label3: TLabel
          Left = 17
          Top = 127
          Width = 31
          Height = 13
          Caption = 'Stacks'
        end
        object OwnerCB: TComboBox
          Left = 17
          Top = 38
          Width = 224
          Height = 21
          Style = csDropDownList
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 0
        end
        object ProjectCB: TComboBox
          Left = 16
          Top = 93
          Width = 225
          Height = 21
          Style = csDropDownList
          Anchors = [akLeft, akTop, akRight]
          DropDownCount = 25
          TabOrder = 1
        end
        object StackCB: TComboBox
          Left = 17
          Top = 146
          Width = 224
          Height = 21
          Hint = 'Test'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          Text = 'StackCB'
        end
      end
      object imageParasGB: TGroupBox
        Left = 0
        Top = 473
        Width = 283
        Height = 207
        Align = alTop
        Caption = 'Region of Interest (ROI)'
        TabOrder = 1
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
        object mResetButton: TButton
          Left = 144
          Top = 120
          Width = 135
          Height = 79
          Caption = 'Reset to Layer Bounds'
          TabOrder = 5
          WordWrap = True
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
          TabOrder = 6
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
          TabOrder = 7
          Text = '0'
        end
        object ScaleConstantE: TFloatLabeledEdit
          Left = 160
          Top = 76
          Width = 103
          Height = 21
          EditLabel.Width = 101
          EditLabel.Height = 13
          EditLabel.Caption = 'Extra Scale Constant'
          TabOrder = 8
          Text = '1.0000'
          Value = 1.000000000000000000
        end
      end
      object GroupBox9: TGroupBox
        Left = 0
        Top = 185
        Width = 283
        Height = 288
        Align = alTop
        Caption = 'ROI'#39's'
        TabOrder = 2
        object ROI_CB: TCheckListBox
          Left = 2
          Top = 15
          Width = 279
          Height = 230
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
        end
        object Panel4: TPanel
          Left = 2
          Top = 245
          Width = 279
          Height = 41
          Align = alBottom
          TabOrder = 1
          object Button1: TButton
            Left = 15
            Top = 6
            Width = 75
            Height = 25
            Caption = 'Refresh'
            TabOrder = 0
          end
        end
      end
    end
    object ZsPanel: TPanel
      Left = 288
      Top = 1
      Width = 96
      Height = 889
      Align = alRight
      TabOrder = 1
      ExplicitHeight = 912
      object Zs_GB: TGroupBox
        Left = 1
        Top = 1
        Width = 94
        Height = 389
        Align = alClient
        Caption = 'Sections'
        TabOrder = 0
        ExplicitHeight = 412
        object mZs: TCheckListBox
          Left = 2
          Top = 15
          Width = 90
          Height = 372
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
          ExplicitHeight = 395
        end
      end
      object CacheGB: TGroupBox
        Left = 1
        Top = 750
        Width = 94
        Height = 138
        Align = alBottom
        Caption = 'Local Cache'
        TabOrder = 1
        ExplicitTop = 773
        object FetchSelectedZsBtn: TButton
          Left = 5
          Top = 19
          Width = 86
          Height = 50
          Caption = 'Generate'
          TabOrder = 0
        end
        object ClearCacheBtn: TButton
          Left = 5
          Top = 75
          Width = 86
          Height = 50
          Caption = 'Clear'
          TabOrder = 1
        end
      end
      object GroupBox2: TGroupBox
        Left = 1
        Top = 570
        Width = 94
        Height = 180
        Align = alBottom
        Caption = 'Other'
        TabOrder = 2
        ExplicitTop = 593
        object OtherCB: TCheckListBox
          Left = 2
          Top = 15
          Width = 90
          Height = 163
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
        end
      end
      object GroupBox7: TGroupBox
        Left = 1
        Top = 390
        Width = 94
        Height = 180
        Align = alBottom
        Caption = 'Stacks'
        TabOrder = 3
        ExplicitTop = 413
        object StacksCB: TCheckListBox
          Left = 2
          Top = 15
          Width = 90
          Height = 163
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
        end
      end
    end
  end
  object ZsPopUpMenu: TPopupMenu
    Left = 448
    Top = 104
    object Checkrange1: TMenuItem
      Caption = 'Select/Unselect Z'#39's'
    end
    object CheckAll1: TMenuItem
      Caption = 'Check All'
    end
    object UncheckAll1: TMenuItem
      Caption = 'Uncheck All'
    end
    object CopyValidZs1: TMenuItem
      Caption = 'Copy Numbers'
    end
    object CreateTiffStack1: TMenuItem
    end
  end
  object StacksPopupMenu: TPopupMenu
    Left = 431
    Top = 444
    object CreateMaxIntensityProjection1: TMenuItem
    end
  end
  object CreateCacheTimer: TTimer
    Interval = 150
    Left = 88
    Top = 360
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
    Left = 40
    Top = 664
  end
end
