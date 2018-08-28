object SelectRenderProjectParametersForm: TSelectRenderProjectParametersForm
  Left = 0
  Top = 0
  ActiveControl = HostPort
  Caption = 'Setup Render Project'
  ClientHeight = 305
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
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 574
    Height = 81
    Align = alTop
    Caption = 'Connection'
    TabOrder = 0
    DesignSize = (
      574
      81)
    object BaseURLE: TSTDStringLabeledEdit
      Left = 16
      Top = 40
      Width = 490
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'Host'
      TabOrder = 0
      Text = 'http://localhost'
      Value = 'http://localhost'
    end
    object HostPort: TIntegerLabeledEdit
      Left = 512
      Top = 40
      Width = 49
      Height = 21
      Anchors = [akTop, akRight]
      EditLabel.Width = 20
      EditLabel.Height = 13
      EditLabel.Caption = 'Port'
      NumbersOnly = True
      TabOrder = 1
      Text = '80'
      Value = 80
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 81
    Width = 574
    Height = 183
    Align = alClient
    Caption = 'Project'
    TabOrder = 1
    DesignSize = (
      574
      183)
    object Label2: TLabel
      Left = 17
      Top = 74
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
      Left = 16
      Top = 93
      Width = 225
      Height = 21
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
      DropDownCount = 25
      TabOrder = 0
    end
    object OwnerCB: TComboBox
      Left = 17
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
    Top = 264
    Width = 574
    Height = 41
    Align = alBottom
    TabOrder = 2
    object Button1: TButton
      Left = 405
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object Button2: TButton
      Left = 486
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Ok'
      ModalResult = 1
      TabOrder = 1
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
    Left = 448
    Top = 125
  end
end
