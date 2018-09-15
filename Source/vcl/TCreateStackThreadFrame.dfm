object CreateStackThreadFrame: TCreateStackThreadFrame
  Left = 0
  Top = 0
  Width = 262
  Height = 68
  Constraints.MinHeight = 68
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 262
    Height = 68
    Align = alClient
    Caption = 'StackName'
    TabOrder = 0
    ExplicitLeft = 96
    ExplicitTop = 88
    ExplicitWidth = 185
    ExplicitHeight = 105
    DesignSize = (
      262
      68)
    object CurrentZ: TLabel
      Left = 198
      Top = 48
      Width = 43
      Height = 13
      Anchors = [akTop, akRight]
      Caption = '0 (20)'
    end
    object ProgressBar1: TProgressBar
      Left = 6
      Top = 24
      Width = 223
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
    end
    object Button1: TButton
      Left = 235
      Top = 24
      Width = 22
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'x'
      TabOrder = 1
      OnClick = Button1Click
    end
  end
end
