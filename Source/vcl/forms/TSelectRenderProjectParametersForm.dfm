object SelectRenderProjectParametersForm: TSelectRenderProjectParametersForm
  Left = 0
  Top = 0
  Caption = 'Setup Render Project'
  ClientHeight = 278
  ClientWidth = 574
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
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 574
    Height = 57
    Align = alTop
    Caption = 'Connection'
    TabOrder = 0
    object PopulateOwnersBtn: TButton
      Left = 527
      Top = 20
      Width = 35
      Height = 25
      Caption = 'Go'
      TabOrder = 0
      OnClick = PopulateOwnersBtnClick
    end
    object RenderServicesCB: TComboBox
      Left = 16
      Top = 22
      Width = 505
      Height = 21
      TabOrder = 1
      Text = 'RenderServicesCB'
      OnChange = RenderServicesCBChange
      OnCloseUp = RenderServicesCBCloseUp
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 57
    Width = 574
    Height = 78
    Align = alTop
    Caption = 'Project'
    TabOrder = 1
    DesignSize = (
      574
      78)
    object Label2: TLabel
      Left = 255
      Top = 19
      Width = 34
      Height = 13
      Caption = 'Project'
    end
    object Label1: TLabel
      Left = 16
      Top = 22
      Width = 32
      Height = 13
      Caption = 'Owner'
    end
    object ProjectCB: TComboBox
      Left = 255
      Top = 38
      Width = 225
      Height = 21
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
      DropDownCount = 25
      TabOrder = 0
    end
    object OwnerCB: TComboBox
      Left = 10
      Top = 38
      Width = 224
      Height = 21
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      OnChange = OwnerCBChange
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 237
    Width = 574
    Height = 41
    Align = alBottom
    TabOrder = 2
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
    Top = 135
    Width = 574
    Height = 102
    Align = alClient
    Caption = 'Data Output'
    TabOrder = 3
    DesignSize = (
      574
      102)
    object OutputDataRootFolderE: TSTDStringLabeledEdit
      Left = 10
      Top = 41
      Width = 518
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 86
      EditLabel.Height = 13
      EditLabel.Caption = 'Output Data Root'
      TabOrder = 0
      Text = 'C:\ImageCache'
      Value = 'C:\ImageCache'
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
  object IdHTTP1: TIdHTTP
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 424
    Top = 165
  end
end
