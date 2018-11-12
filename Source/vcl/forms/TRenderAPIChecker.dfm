object RenderAPIChecker: TRenderAPIChecker
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'RenderAPIChecker'
  ClientHeight = 387
  ClientWidth = 678
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
    Width = 185
    Height = 346
    Align = alLeft
    TabOrder = 0
    ExplicitLeft = 144
    ExplicitTop = 200
    ExplicitHeight = 41
    DesignSize = (
      185
      346)
    object RequestBtn: TButton
      Left = 48
      Top = 308
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = 'Request'
      TabOrder = 0
      OnClick = RequestBtnClick
      ExplicitTop = 280
    end
    object APIs: TRadioGroup
      Left = 1
      Top = 1
      Width = 183
      Height = 80
      Align = alTop
      Caption = 'APIs'
      ItemIndex = 0
      Items.Strings = (
        'ServerProperties'
        'Owners')
      TabOrder = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 678
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 346
    Width = 678
    Height = 41
    Align = alBottom
    TabOrder = 1
    ExplicitLeft = 2
    ExplicitTop = 309
    ExplicitWidth = 582
    DesignSize = (
      678
      41)
    object CloseBtn: TButton
      Left = 592
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 0
      ExplicitLeft = 784
    end
  end
  object Panel3: TPanel
    Left = 185
    Top = 0
    Width = 493
    Height = 346
    Align = alClient
    Caption = 'Panel3'
    TabOrder = 2
    ExplicitLeft = 328
    ExplicitTop = 184
    ExplicitWidth = 185
    ExplicitHeight = 41
    object GroupBox1: TGroupBox
      Left = 1
      Top = 65
      Width = 491
      Height = 280
      Align = alClient
      Caption = 'Server Response'
      TabOrder = 0
      ExplicitLeft = 185
      ExplicitTop = 105
      ExplicitWidth = 493
      ExplicitHeight = 241
      object ResponseMemo: TMemo
        Left = 2
        Top = 15
        Width = 487
        Height = 263
        Align = alClient
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        ExplicitWidth = 489
        ExplicitHeight = 224
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 1
      Width = 491
      Height = 64
      Align = alTop
      Caption = 'Request'
      TabOrder = 1
      object RequestURL: TSTDStringLabeledEdit
        Left = 16
        Top = 33
        Width = 465
        Height = 21
        EditLabel.Width = 19
        EditLabel.Height = 13
        EditLabel.Caption = 'URL'
        TabOrder = 0
      end
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
    Left = 313
    Top = 112
  end
end
