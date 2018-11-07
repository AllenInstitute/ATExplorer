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
        Width = 49
        Height = 25
        Caption = 'Add'
        TabOrder = 0
        OnClick = AddRenderServiceBtnClick
      end
      object RemoveServiceBtn: TButton
        Left = 80
        Top = 6
        Width = 57
        Height = 25
        Caption = 'Remove'
        TabOrder = 1
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
    DesignSize = (
      290
      305)
    object HostE: TSTDStringLabeledEdit
      Left = 13
      Top = 42
      Width = 210
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'Host'
      TabOrder = 0
      Text = 'http://ibs-forrestc-ux1'
      Value = 'http://ibs-forrestc-ux1'
    end
    object TestRenderServiceBtn: TButton
      Left = 229
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
      Width = 97
      Height = 21
      EditLabel.Width = 114
      EditLabel.Height = 13
      EditLabel.Caption = 'Max # of tiles to render'
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
end
