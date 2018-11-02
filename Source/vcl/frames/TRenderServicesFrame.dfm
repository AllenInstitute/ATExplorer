object RenderServicesFrame: TRenderServicesFrame
  Left = 0
  Top = 0
  Width = 477
  Height = 235
  Align = alClient
  AutoSize = True
  TabOrder = 0
  ExplicitWidth = 451
  ExplicitHeight = 305
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 161
    Height = 235
    Align = alLeft
    Caption = 'Services'
    TabOrder = 0
    Visible = False
    ExplicitHeight = 213
    object ServicesLB: TListBox
      Left = 2
      Top = 15
      Width = 157
      Height = 183
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      ExplicitLeft = -64
      ExplicitWidth = 121
      ExplicitHeight = 196
    end
    object Panel1: TPanel
      Left = 2
      Top = 198
      Width = 157
      Height = 35
      Align = alBottom
      TabOrder = 1
      ExplicitTop = 176
      ExplicitWidth = 101
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
    Width = 316
    Height = 235
    Align = alClient
    Caption = 'Render Service'
    TabOrder = 1
    ExplicitLeft = 0
    ExplicitTop = 129
    ExplicitWidth = 451
    ExplicitHeight = 176
    DesignSize = (
      316
      235)
    object BaseURLE: TSTDStringLabeledEdit
      Left = 13
      Top = 42
      Width = 236
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'Host'
      TabOrder = 0
      Text = 'http://ibs-forrestc-ux1'
      Value = 'http://ibs-forrestc-ux1'
      ExplicitWidth = 371
    end
    object TestRenderServiceBtn: TButton
      Left = 255
      Top = 40
      Width = 52
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Test'
      TabOrder = 1
      OnClick = TestRenderServiceBtnClick
      ExplicitLeft = 390
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
