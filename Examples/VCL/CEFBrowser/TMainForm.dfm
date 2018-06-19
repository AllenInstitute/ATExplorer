object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 592
  ClientWidth = 1061
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DcefBrowser1: TDcefBrowser
    Left = 0
    Top = 73
    Width = 1061
    Height = 519
    TabOrder = 0
    Align = alClient
    DefaultURL = 'about:blank'
    DcefBOptions.DevToolsEnable = False
    DcefBOptions.CloseWPagesClosed = False
    DcefBOptions.DownLoadPath = 'C:\CodeGear\Tokyo\bin\Download\'
    OnKeyEvent = DcefBrowser1KeyEvent
    ExplicitTop = 0
    ExplicitWidth = 1011
    ExplicitHeight = 592
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1061
    Height = 73
    Align = alTop
    TabOrder = 1
    ExplicitWidth = 1011
    DesignSize = (
      1061
      73)
    object URLEdit: TEdit
      Left = 16
      Top = 27
      Width = 978
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      Text = 
        'http://neuroglancer-demo.appspot.com/#!%7B%22layers%22:%7B%22em%' +
        '22:%7B%22source%22:%22precomputed://http://atbigdawg.corp.alleni' +
        'nstitute.org/cloudvolume/M247514_Rorb_1/Site3/cv_Site3Align2_EM_' +
        'clahe_mm/%22%2C%22type%22:%22image%22%7D%7D%2C%22navigation%22:%' +
        '7B%22pose%22:%7B%22position%22:%7B%22voxelSize%22:%5B3%2C3%2C50%' +
        '5D%2C%22voxelCoordinates%22:%5B6441.41015625%2C6346.705078125%2C' +
        '29%5D%7D%7D%2C%22zoomFactor%22:50.79278903269983%7D%2C%22showAxi' +
        'sLines%22:false%7D'
    end
    object Button1: TButton
      Left = 1000
      Top = 25
      Width = 50
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Go'
      TabOrder = 1
    end
  end
end
