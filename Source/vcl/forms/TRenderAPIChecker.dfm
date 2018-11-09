object RenderAPIChecker: TRenderAPIChecker
  Left = 0
  Top = 0
  Caption = 'RenderAPIChecker'
  ClientHeight = 524
  ClientWidth = 976
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object APIs: TRadioGroup
    Left = 32
    Top = 40
    Width = 225
    Height = 297
    Caption = 'APIs'
    Items.Strings = (
      'ServerProperties'
      'Owners')
    TabOrder = 0
  end
end
