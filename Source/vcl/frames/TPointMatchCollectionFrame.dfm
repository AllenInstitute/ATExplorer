object PointMatchCollectionFrame: TPointMatchCollectionFrame
  Left = 0
  Top = 0
  Width = 864
  Height = 399
  Align = alClient
  TabOrder = 0
  ExplicitWidth = 451
  ExplicitHeight = 305
  object mLeftPanel: TPanel
    Left = 0
    Top = 0
    Width = 388
    Height = 399
    Align = alLeft
    TabOrder = 0
    ExplicitHeight = 305
    object ScrollBox1: TScrollBox
      Left = 1
      Top = 1
      Width = 290
      Height = 397
      VertScrollBar.Margin = 5
      VertScrollBar.Smooth = True
      VertScrollBar.Style = ssFlat
      Align = alClient
      Constraints.MinWidth = 290
      TabOrder = 0
      ExplicitHeight = 303
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 286
        Height = 153
        Align = alTop
        Caption = 'Point Match Context'
        TabOrder = 0
        object OwnerE: TSTDStringLabeledEdit
          Left = 11
          Top = 34
          Width = 262
          Height = 21
          EditLabel.Width = 32
          EditLabel.Height = 13
          EditLabel.Caption = 'Owner'
          Enabled = False
          TabOrder = 0
        end
        object CollectionE: TSTDStringLabeledEdit
          Left = 12
          Top = 77
          Width = 261
          Height = 21
          EditLabel.Width = 46
          EditLabel.Height = 13
          EditLabel.Caption = 'Collection'
          Enabled = False
          TabOrder = 1
        end
        object PairsE: TIntegerLabeledEdit
          Left = 12
          Top = 120
          Width = 61
          Height = 21
          EditLabel.Width = 29
          EditLabel.Height = 13
          EditLabel.Caption = 'PairsE'
          Enabled = False
          TabOrder = 2
          Text = '-1'
          Value = -1
        end
      end
      object Button1: TButton
        Left = 12
        Top = 176
        Width = 75
        Height = 25
        Action = DeletePMCA
        TabOrder = 1
      end
    end
    object IDsPanel: TPanel
      Left = 291
      Top = 1
      Width = 96
      Height = 397
      Align = alRight
      TabOrder = 1
      ExplicitHeight = 303
      object GroupBox2: TGroupBox
        Left = 1
        Top = 1
        Width = 94
        Height = 230
        Align = alTop
        Caption = 'p group IDs'
        TabOrder = 0
        object pGroupIDs: TCheckListBox
          Left = 2
          Top = 15
          Width = 90
          Height = 213
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
        end
      end
      object GroupBox3: TGroupBox
        Left = 1
        Top = 231
        Width = 94
        Height = 165
        Align = alClient
        Caption = 'q group IDs'
        TabOrder = 1
        ExplicitHeight = 71
        object qGroupIDs: TCheckListBox
          Left = 2
          Top = 15
          Width = 90
          Height = 88
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
          ExplicitHeight = 341
        end
        object Panel1: TPanel
          Left = 2
          Top = 103
          Width = 90
          Height = 60
          Align = alBottom
          TabOrder = 1
          ExplicitTop = 9
          object Button2: TButton
            Left = 3
            Top = 16
            Width = 75
            Height = 25
            Caption = 'Get pairs'
            TabOrder = 0
          end
        end
      end
    end
  end
  object VisualsPC: TPageControl
    Left = 388
    Top = 0
    Width = 476
    Height = 399
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 63
    ExplicitHeight = 305
  end
  object Actions: TActionList
    Left = 385
    Top = 130
    object DeletePMCA: TAction
      Caption = 'Delete'
      OnExecute = DeletePMCAExecute
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
    Left = 233
    Top = 185
  end
end
