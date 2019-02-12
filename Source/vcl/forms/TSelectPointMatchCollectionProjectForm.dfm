object SelectPointmatchCollectionProjectForm: TSelectPointmatchCollectionProjectForm
  Left = 0
  Top = 0
  Caption = 'Choose a Pointmatch Collection'
  ClientHeight = 176
  ClientWidth = 710
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 135
    Width = 710
    Height = 41
    Align = alBottom
    TabOrder = 0
    object Button1: TButton
      Left = 532
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object Button2: TButton
      Left = 613
      Top = 6
      Width = 85
      Height = 25
      Caption = 'Ok'
      ModalResult = 1
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 710
    Height = 135
    Align = alClient
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 708
      Height = 57
      Align = alTop
      Caption = 'Connection'
      TabOrder = 0
      object PopulateOwnersBtn: TButton
        Left = 647
        Top = 20
        Width = 50
        Height = 25
        Caption = 'Refresh'
        TabOrder = 0
        OnClick = PopulateOwnersBtnClick
      end
      object RenderServicesCB: TComboBox
        Left = 16
        Top = 22
        Width = 625
        Height = 21
        TabOrder = 1
        Text = 'RenderServicesCB'
        OnChange = RenderServicesCBChange
        OnCloseUp = RenderServicesCBCloseUp
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 58
      Width = 708
      Height = 76
      Align = alClient
      Caption = 'Project'
      TabOrder = 1
      DesignSize = (
        708
        76)
      object Label2: TLabel
        Left = 343
        Top = 19
        Width = 46
        Height = 13
        Caption = 'Collection'
      end
      object Label1: TLabel
        Left = 10
        Top = 22
        Width = 32
        Height = 13
        Caption = 'Owner'
      end
      object CollectionCB: TComboBox
        Left = 343
        Top = 38
        Width = 354
        Height = 21
        Style = csDropDownList
        Anchors = [akLeft, akTop, akRight]
        DropDownCount = 25
        TabOrder = 0
      end
      object OwnerCB: TComboBox
        Left = 10
        Top = 38
        Width = 327
        Height = 21
        Style = csDropDownList
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
        OnChange = OwnerCBChange
      end
    end
  end
end
