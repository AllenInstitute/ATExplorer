object CreateACQRenderStacksForm: TCreateACQRenderStacksForm
  Left = 0
  Top = 0
  Caption = 'Create Raw Data RenderStacks'
  ClientHeight = 285
  ClientWidth = 520
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object ProgressLabel: TLabel
    Left = 24
    Top = 160
    Width = 42
    Height = 13
    Caption = 'message'
  end
  object CurrentStateTbl: TLabel
    Left = 24
    Top = 192
    Width = 77
    Height = 13
    Caption = 'CurrentStateTbl'
  end
  object Panel1: TPanel
    Left = 0
    Top = 241
    Width = 520
    Height = 44
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      520
      44)
    object RunBtn: TButton
      Left = 7
      Top = 9
      Width = 75
      Height = 25
      Caption = 'Run'
      TabOrder = 0
      OnClick = RunBtnClick
    end
    object CloseBtn: TButton
      Left = 437
      Top = 9
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 1
    end
  end
  object PopulatePB: TProgressBar
    Left = 0
    Top = 224
    Width = 520
    Height = 17
    Align = alBottom
    TabOrder = 1
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 40
    Width = 185
    Height = 105
    Caption = 'Sessions'
    TabOrder = 2
  end
end
