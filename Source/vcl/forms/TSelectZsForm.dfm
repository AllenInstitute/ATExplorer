object SelectZsForm: TSelectZsForm
  Left = 0
  Top = 0
  ActiveControl = ZDownSampleE
  Caption = 'Select Z'#39's'
  ClientHeight = 328
  ClientWidth = 538
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 538
    Height = 265
    Align = alClient
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 209
      Top = 1
      Width = 6
      Height = 263
      ExplicitLeft = 243
      ExplicitHeight = 424
    end
    object Panel3: TPanel
      Left = 215
      Top = 1
      Width = 88
      Height = 263
      Align = alLeft
      TabOrder = 0
      ExplicitLeft = 255
      ExplicitTop = -4
      DesignSize = (
        88
        263)
      object Label1: TLabel
        Left = 71
        Top = 35
        Width = 5
        Height = 13
        Caption = 'z'
      end
      object MoveToUnselectLBBtn: TButton
        Left = 6
        Top = 147
        Width = 75
        Height = 50
        Anchors = [akTop, akRight]
        Caption = '->'
        Enabled = False
        TabOrder = 0
        OnClick = MoveItems
      end
      object MoveToSelectedLBBtn: TButton
        Left = 6
        Top = 203
        Width = 75
        Height = 50
        Anchors = [akTop, akRight]
        Caption = '<-'
        Enabled = False
        TabOrder = 1
        OnClick = MoveItems
      end
      object ZDownSampleE: TIntegerLabeledEdit
        Left = 6
        Top = 32
        Width = 59
        Height = 21
        EditLabel.Width = 60
        EditLabel.Height = 13
        EditLabel.Caption = 'Select every'
        NumbersOnly = True
        TabOrder = 2
        Text = '1'
        OnKeyDown = ZDownSampleEKeyDown
        Value = 1
      end
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 208
      Height = 263
      Align = alLeft
      Caption = 'Selected'
      TabOrder = 1
      object SelectedItems: TListBox
        Left = 2
        Top = 15
        Width = 204
        Height = 246
        Align = alClient
        ItemHeight = 13
        MultiSelect = True
        TabOrder = 0
        OnClick = ItemsClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 303
      Top = 1
      Width = 234
      Height = 263
      Align = alClient
      Caption = 'Unselected'
      TabOrder = 2
      object UnSelectedItems: TListBox
        Left = 2
        Top = 15
        Width = 230
        Height = 246
        Align = alClient
        ItemHeight = 13
        MultiSelect = True
        TabOrder = 0
        OnClick = ItemsClick
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 265
    Width = 538
    Height = 63
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      538
      63)
    object NrOfZsLlbl: TIntLabel
      Left = 92
      Top = 24
      Width = 6
      Height = 13
      Caption = '1'
      Value = 1
      TheFont.Charset = DEFAULT_CHARSET
      TheFont.Color = clWindowText
      TheFont.Height = -11
      TheFont.Name = 'Tahoma'
      TheFont.Style = []
    end
    object Label2: TLabel
      Left = 16
      Top = 24
      Width = 70
      Height = 13
      Caption = 'Total Nr of z'#39's:'
    end
    object Button2: TButton
      Left = 453
      Top = 6
      Width = 75
      Height = 50
      Anchors = [akTop, akRight]
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 0
    end
    object Button3: TButton
      Left = 357
      Top = 6
      Width = 75
      Height = 50
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
end
