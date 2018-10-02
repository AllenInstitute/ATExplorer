object CreateATIFDataProjectForm: TCreateATIFDataProjectForm
  Left = 0
  Top = 0
  Caption = 'Setup an ATIF Data Project'
  ClientHeight = 131
  ClientWidth = 574
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 90
    Width = 574
    Height = 41
    Align = alBottom
    TabOrder = 0
    ExplicitTop = 237
    object Button1: TButton
      Left = 396
      Top = 9
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object Button2: TButton
      Left = 477
      Top = 9
      Width = 85
      Height = 25
      Caption = 'Ok'
      ModalResult = 1
      TabOrder = 1
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 0
    Width = 574
    Height = 90
    Align = alClient
    Caption = 'Data Output'
    TabOrder = 1
    ExplicitTop = 159
    ExplicitHeight = 78
    DesignSize = (
      574
      90)
    object DataRootFolderE: TSTDStringLabeledEdit
      Left = 10
      Top = 41
      Width = 518
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 82
      EditLabel.Height = 13
      EditLabel.Caption = 'Data Root Folder'
      TabOrder = 0
      Text = 'C:\Data'
      Value = 'C:\Data'
    end
    object BrowseForDataOutputPathBtn: TButton
      Left = 534
      Top = 41
      Width = 28
      Height = 21
      Anchors = [akTop, akRight]
      Caption = '...'
      TabOrder = 1
      OnClick = BrowseForDataOutputPathBtnClick
    end
  end
end
