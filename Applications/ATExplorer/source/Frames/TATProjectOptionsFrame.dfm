object ATProjectOptionsFrame: TATProjectOptionsFrame
  Left = 0
  Top = 0
  Width = 745
  Height = 442
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 745
    Height = 442
    Align = alClient
    Caption = 'General'
    TabOrder = 0
    ExplicitLeft = 40
    ExplicitTop = 32
    ExplicitWidth = 185
    ExplicitHeight = 105
    DesignSize = (
      745
      442)
    object STDStringLabeledEdit1: TSTDStringLabeledEdit
      Left = 16
      Top = 48
      Width = 668
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 98
      EditLabel.Height = 13
      EditLabel.Caption = 'AT Data Root Folder'
      TabOrder = 0
    end
    object Button1: TButton
      Left = 688
      Top = 46
      Width = 52
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '...'
      TabOrder = 1
    end
  end
end
