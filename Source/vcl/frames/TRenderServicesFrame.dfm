object RenderServicesFrame: TRenderServicesFrame
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
    Width = 161
    Height = 305
    Align = alLeft
    Caption = 'Services'
    TabOrder = 0
    object ServicesLB: TListBox
      Left = 2
      Top = 15
      Width = 157
      Height = 253
      Align = alClient
      ItemHeight = 13
      PopupMenu = PopupMenu1
      TabOrder = 0
      OnClick = ServicesLBClick
    end
    object Panel1: TPanel
      Left = 2
      Top = 268
      Width = 157
      Height = 35
      Align = alBottom
      TabOrder = 1
      object AddRenderServiceBtn: TButton
        Left = 8
        Top = 6
        Width = 41
        Height = 25
        Caption = 'New'
        TabOrder = 0
        OnClick = AddRenderServiceBtnClick
      end
      object RemoveServiceBtn: TButton
        Left = 93
        Top = 6
        Width = 57
        Height = 25
        Caption = 'Remove'
        TabOrder = 1
        OnClick = RemoveServiceBtnClick
      end
    end
  end
  object GroupBox4: TGroupBox
    Left = 161
    Top = 0
    Width = 290
    Height = 305
    Align = alClient
    Caption = 'Render Service'
    TabOrder = 1
    object HostE: TSTDStringLabeledEdit
      Left = 55
      Top = 42
      Width = 133
      Height = 21
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'Host'
      TabOrder = 1
      Text = 'ibs-forrestc-ux1'
      Value = 'ibs-forrestc-ux1'
    end
    object TestRenderServiceBtn: TButton
      Left = 13
      Top = 203
      Width = 108
      Height = 46
      Caption = 'Test'
      TabOrder = 5
      OnClick = TestRenderServiceBtnClick
    end
    object MaxTileSpecsToRenderE: TIntegerLabeledEdit
      Left = 13
      Top = 152
      Width = 60
      Height = 21
      EditLabel.Width = 114
      EditLabel.Height = 13
      EditLabel.Caption = 'Max # of tiles to render'
      TabOrder = 4
      Text = '150'
      Value = 150
    end
    object PortE: TIntegerLabeledEdit
      Left = 194
      Top = 42
      Width = 58
      Height = 21
      EditLabel.Width = 26
      EditLabel.Height = 13
      EditLabel.Caption = 'PortE'
      TabOrder = 2
      Text = '80'
      Value = 80
    end
    object ProtocolE: TSTDStringLabeledEdit
      Left = 13
      Top = 42
      Width = 36
      Height = 21
      EditLabel.Width = 39
      EditLabel.Height = 13
      EditLabel.Caption = 'Protocol'
      TabOrder = 0
      Text = 'http'
      Value = 'http'
    end
    object VersionE: TSTDStringLabeledEdit
      Left = 13
      Top = 90
      Width = 84
      Height = 21
      EditLabel.Width = 35
      EditLabel.Height = 13
      EditLabel.Caption = 'Version'
      TabOrder = 3
      Text = '/version/v1'
      Value = '/version/v1'
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 64
    Top = 96
    object Rename: TMenuItem
      Caption = 'Rename'
      OnClick = RenameClick
    end
  end
end
