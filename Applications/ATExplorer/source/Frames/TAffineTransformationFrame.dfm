inherited AffineTransformationFrame: TAffineTransformationFrame
  Width = 392
  Height = 533
  ExplicitWidth = 392
  ExplicitHeight = 533
  inherited GroupBox1: TGroupBox
    Width = 392
    ExplicitWidth = 392
    inherited RenderClientScriptsFolderE: TSTDStringLabeledEdit
      EditLabel.ExplicitWidth = 124
    end
  end
  inherited Panel2: TPanel
    Width = 392
    Height = 364
    ExplicitWidth = 392
    ExplicitHeight = 364
    inherited StacksGB: TGroupBox
      Height = 362
      ExplicitHeight = 362
      inherited StacksForProjectCB: TCheckListBox
        Height = 339
        Flat = False
        PopupMenu = StacksPopup
        Sorted = True
        ExplicitHeight = 339
      end
    end
    inherited GroupBox2: TGroupBox
      Width = 205
      Height = 362
      ExplicitWidth = 205
      ExplicitHeight = 362
      DesignSize = (
        205
        362)
      object ZLbl: TIntLabel [0]
        Left = 72
        Top = 325
        Width = 10
        Height = 13
        Caption = '-1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        Value = -1
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -11
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
      object TranslateYE: TIntegerLabeledEdit [1]
        Left = 10
        Top = 86
        Width = 97
        Height = 21
        EditLabel.Width = 92
        EditLabel.Height = 13
        EditLabel.Caption = 'Translate Y (pixels)'
        TabOrder = 3
        Text = '0'
      end
      object TranslateXE: TIntegerLabeledEdit [2]
        Left = 10
        Top = 38
        Width = 97
        Height = 21
        EditLabel.Width = 92
        EditLabel.Height = 13
        EditLabel.Caption = 'Translate X (pixels)'
        TabOrder = 2
        Text = '0'
      end
      object RotationE: TFloatLabeledEdit [3]
        Left = 10
        Top = 134
        Width = 97
        Height = 21
        EditLabel.Width = 70
        EditLabel.Height = 13
        EditLabel.Caption = 'Rotation (deg)'
        TabOrder = 1
        Text = '0'
      end
      object AppendToCurrentStackCB: TPropertyCheckBox [4]
        Left = 10
        Top = 175
        Width = 95
        Height = 41
        Caption = 'Append Transform to Current Stack'
        TabOrder = 0
        WordWrap = True
      end
      inherited ExecuteBtn: TButton
        Left = 6
        Top = 230
        Width = 95
        TabOrder = 4
        OnClick = ExecuteBtnClick
        ExplicitLeft = 6
        ExplicitTop = 230
        ExplicitWidth = 95
      end
      object ProgressBar1: TProgressBar
        Left = 2
        Top = 344
        Width = 201
        Height = 16
        Align = alBottom
        TabOrder = 5
        ExplicitLeft = 1
        ExplicitTop = 347
        ExplicitWidth = 390
      end
    end
  end
  object StacksPopup: TPopupMenu
    OnPopup = StacksPopupPopup
    Left = 80
    Top = 272
    object DeleteStack1: TMenuItem
      Action = DeleteStackA
    end
  end
  object StacksActions: TActionList
    Left = 64
    Top = 360
    object DeleteStackA: TAction
      Caption = 'Delete Stack'
      OnExecute = DeleteStackAExecute
    end
  end
end
