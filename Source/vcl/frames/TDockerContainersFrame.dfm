object DockerContainersFrame: TDockerContainersFrame
  Left = 0
  Top = 0
  Width = 736
  Height = 519
  Align = alClient
  AutoSize = True
  TabOrder = 0
  ExplicitWidth = 451
  ExplicitHeight = 305
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 161
    Height = 519
    Align = alLeft
    Caption = 'Containers'
    TabOrder = 0
    ExplicitHeight = 305
    object ItemsLB: TListBox
      Left = 2
      Top = 15
      Width = 157
      Height = 467
      Align = alClient
      ItemHeight = 13
      PopupMenu = PopupMenu1
      TabOrder = 0
      OnClick = ItemsLBClick
      ExplicitLeft = 1
    end
    object Panel1: TPanel
      Left = 2
      Top = 482
      Width = 157
      Height = 35
      Align = alBottom
      TabOrder = 1
      ExplicitTop = 268
      object AddBtn: TButton
        Left = 8
        Top = 6
        Width = 41
        Height = 25
        Caption = 'New'
        TabOrder = 0
        OnClick = AddBtnClick
      end
      object RemoveBtn: TButton
        Left = 93
        Top = 6
        Width = 57
        Height = 25
        Caption = 'Remove'
        TabOrder = 1
        OnClick = RemoveBtnClick
      end
    end
  end
  object GroupBox4: TGroupBox
    Left = 161
    Top = 0
    Width = 575
    Height = 519
    Align = alClient
    Caption = 'Container'
    TabOrder = 1
    ExplicitLeft = 158
    ExplicitTop = -3
    object TestBtn: TButton
      Left = 13
      Top = 203
      Width = 108
      Height = 46
      Caption = 'Test'
      TabOrder = 0
      OnClick = TestBtnClick
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
