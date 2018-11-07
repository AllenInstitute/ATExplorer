object ATProjectOptionsFrame: TATProjectOptionsFrame
  Left = 0
  Top = 0
  Width = 645
  Height = 193
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 645
    Height = 193
    Align = alClient
    Caption = 'General'
    TabOrder = 0
    ExplicitWidth = 745
    ExplicitHeight = 442
    DesignSize = (
      645
      193)
    object STDStringLabeledEdit1: TSTDStringLabeledEdit
      Left = 16
      Top = 48
      Width = 568
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 98
      EditLabel.Height = 13
      EditLabel.Caption = 'AT Data Root Folder'
      TabOrder = 0
      ExplicitWidth = 668
    end
    object Button1: TButton
      Left = 588
      Top = 46
      Width = 52
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '...'
      TabOrder = 1
      ExplicitLeft = 688
    end
  end
end
