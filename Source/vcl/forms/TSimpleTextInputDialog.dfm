object NewValueE: TNewValueE
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Input'
  ClientHeight = 97
  ClientWidth = 844
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  DesignSize = (
    844
    97)
  PixelsPerInch = 96
  TextHeight = 23
  object NewValueE: TSTDStringLabeledEdit
    Left = 8
    Top = 42
    Width = 649
    Height = 31
    EditLabel.Width = 89
    EditLabel.Height = 23
    EditLabel.Caption = 'New Value'
    TabOrder = 0
    OnChange = OnChange
  end
  object mCancelBtn: TButton
    Left = 723
    Top = 33
    Width = 100
    Height = 40
    Anchors = [akTop, akRight]
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
    ExplicitLeft = 744
  end
  object mOkBtn: TButton
    Left = 667
    Top = 33
    Width = 50
    Height = 40
    Anchors = [akTop, akRight]
    Caption = 'OK'
    Enabled = False
    ModalResult = 1
    TabOrder = 2
    ExplicitLeft = 688
  end
end
