object MainForm: TMainForm
  Left = 0
  Top = 0
  AlphaBlendValue = 100
  Caption = 'Volume Creator'
  ClientHeight = 694
  ClientWidth = 1442
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  ShowHint = True
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 675
    Width = 1442
    Height = 19
    Panels = <>
  end
  object MainPanel: TPanel
    Left = 0
    Top = 25
    Width = 1442
    Height = 650
    Align = alClient
    TabOrder = 1
    object Splitter2: TSplitter
      Left = 1
      Top = 510
      Width = 1440
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      ExplicitLeft = 8
      ExplicitTop = 729
      ExplicitWidth = 1442
    end
    object Splitter1: TSplitter
      Left = 201
      Top = 1
      Height = 490
      ExplicitLeft = 195
      ExplicitTop = 19
      ExplicitHeight = 837
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 513
      Width = 1440
      Height = 136
      Align = alBottom
      PopupMenu = PopupMenu1
      TabOrder = 0
      ExplicitTop = 20
      ExplicitWidth = 302
      inline TLogMemoFrame1: TLogMemoFrame
        Left = 1
        Top = 1
        Width = 1438
        Height = 134
        Align = alClient
        TabOrder = 0
        ExplicitLeft = 1
        ExplicitTop = 1
        ExplicitWidth = 300
        ExplicitHeight = 134
        inherited Panel1: TPanel
          Width = 1438
          Height = 134
          ExplicitWidth = 300
          ExplicitHeight = 134
          inherited GroupBox1: TGroupBox
            Width = 1436
            ExplicitWidth = 298
          end
          inherited infoMemo: TMemo
            Width = 1436
            Height = 82
            ExplicitWidth = 1436
            ExplicitHeight = 82
          end
        end
      end
    end
    object ProjectManagerPanel: TPanel
      Left = 1
      Top = 1
      Width = 200
      Height = 490
      Align = alLeft
      TabOrder = 1
      object ProjectTView: TTreeView
        Left = 1
        Top = 1
        Width = 198
        Height = 488
        Align = alClient
        Indent = 19
        PopupMenu = ProjTreeViewPopup
        ReadOnly = True
        RightClickSelect = True
        RowSelect = True
        TabOrder = 0
        OnClick = ProjectTViewClick
        OnContextPopup = ProjectTViewContextPopup
        OnDblClick = ProjectTViewDblClick
        OnEdited = ProjectTViewEdited
        OnEditing = ProjectTViewEditing
      end
    end
    object ShowBottomPanelBtn: TButton
      Left = 1
      Top = 491
      Width = 1440
      Height = 19
      Action = ToggleBottomPanelA
      Align = alBottom
      TabOrder = 2
      Visible = False
    end
    object MainPC: TPageControl
      Left = 204
      Top = 1
      Width = 1237
      Height = 490
      Align = alClient
      PopupMenu = MainPCPopup
      TabOrder = 3
      OnContextPopup = MainPCContextPopup
    end
  end
  object TopPanel2: TPanel
    Left = 0
    Top = 0
    Width = 1442
    Height = 25
    Align = alTop
    TabOrder = 2
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 136
      Height = 23
      Align = alLeft
      TabOrder = 0
      object ToolBar1: TToolBar
        Left = 1
        Top = 1
        Width = 134
        Height = 22
        Hint = 'Test'
        ButtonWidth = 24
        Caption = 'ToolBar1'
        Images = ImageList1
        List = True
        AllowTextButtons = True
        TabOrder = 0
        object ToolButton3: TToolButton
          Left = 0
          Top = 0
          Action = NewProjectA
        end
        object ToolButton7: TToolButton
          Left = 24
          Top = 0
          Action = CloseProjectA
          ImageIndex = 6
        end
        object ToolButton1: TToolButton
          Left = 48
          Top = 0
          Action = FileOpen1
        end
        object ToolButton2: TToolButton
          Left = 72
          Top = 0
          Action = SaveProjectA
        end
        object ToolButton4: TToolButton
          Left = 96
          Top = 0
          Width = 8
          Caption = 'ToolButton4'
          ImageIndex = 3
          Style = tbsSeparator
        end
        object ToolButton6: TToolButton
          Left = 104
          Top = 0
          Action = OpenSettingsA
          ImageIndex = 7
        end
      end
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 32
    Top = 368
  end
  object MainMenu1: TMainMenu
    Images = ImageList1
    Left = 56
    Top = 152
    object File1: TMenuItem
      Caption = 'File'
      object New1: TMenuItem
        Action = NewProjectA
      end
      object Open1: TMenuItem
        Action = FileOpen1
      end
      object ReopenMenu: TMenuItem
        Caption = 'Reopen'
        Enabled = False
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Save1: TMenuItem
        Action = SaveProjectA
      end
      object SaveAs1: TMenuItem
        Action = SaveProjectAsA
      end
      object Close1: TMenuItem
        Action = CloseProjectA
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Action = FileExit1
      end
    end
    object Options1: TMenuItem
      Caption = 'Options'
      object ThemesMenu: TMenuItem
        Caption = 'Appearance'
      end
      object Settings1: TMenuItem
        Action = OpenSettingsA
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Caption = 'About'
        OnClick = About1Click
      end
    end
  end
  object MenuActions: TActionList
    Images = ImageList1
    Left = 48
    Top = 88
    object FileOpen1: TFileOpen
      Category = 'File'
      Caption = '&Open...'
      Dialog.DefaultExt = 'vc'
      Dialog.Filter = '*.vc||*.*'
      Hint = 'Open|Opens an existing file'
      ImageIndex = 1
      ShortCut = 16463
      OnAccept = FileOpen1Accept
    end
    object NewProjectA: TAction
      Category = 'File'
      Caption = 'New'
      Hint = 'New Project'
      ImageIndex = 0
      OnExecute = NewProjectAExecute
    end
    object SaveProjectA: TAction
      Category = 'File'
      Caption = 'Save'
      Hint = 'Save Current Project'
      ImageIndex = 2
      OnExecute = SaveProjectAExecute
      OnUpdate = SaveProjectAUpdate
    end
    object SaveProjectAsA: TAction
      Category = 'File'
      Caption = 'Save As'
      OnExecute = SaveProjectAsAExecute
      OnUpdate = SaveProjectAsAUpdate
    end
    object CloseProjectA: TAction
      Category = 'File'
      Caption = 'Close'
      Hint = 'Close Project'
      OnExecute = CloseProjectAExecute
      OnUpdate = CloseProjectAUpdate
    end
    object AddRenderProject: TAction
      Category = 'TreeView'
      Caption = 'Add Render Project'
      OnExecute = AddRenderProjectExecute
    end
    object EditViewNode: TAction
      Category = 'TreeView'
      Caption = 'EditViewNode'
      OnExecute = EditViewNodeExecute
    end
    object ToggleBottomPanelA: TAction
      Caption = 'Hide Log Window'
      OnExecute = ToggleBottomPanelAExecute
      OnUpdate = ToggleBottomPanelAUpdate
    end
    object ToggleImageGridA: TAction
      Caption = 'Toggle Image Grid'
    end
    object CreateTiffStackA: TAction
      Caption = 'Create Tiff Stack'
    end
    object CreateMIPA: TAction
      Caption = 'Create Max Intensity Projection'
    end
    object OpenSettingsA: TAction
      Caption = 'Settings'
      Hint = 'Open Settings'
      OnExecute = OpenSettingsAExecute
    end
    object FileExit1: TFileExit
      Category = 'File'
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 8
    end
    object RemoveFromProjectA: TAction
      Category = 'TreeView'
      Caption = 'Remove From Project'
      OnExecute = RemoveFromProjectAExecute
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'atp'
    Filter = 'ATExplorer Project|*.atp'
    Left = 32
    Top = 448
  end
  object ImageList1: TImageList
    Left = 32
    Top = 40
    Bitmap = {
      494C010109001800C80210001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000008686860086868600868686008686
      8600868686008686860086868600868686008686860086868600FFFFFF00C0C0
      C00086868600C0C0C000FFFFFF00C0C0C0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008686860086868600868686008686
      860086868600868686008686860086868600868686008686860086868600FFFF
      FF0086868600FFFFFF0086868600868686000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008000000080000000800000008000
      00000000000000000000868686008686860086868600FFFFFF00FFFFFF00FFFF
      FF00800000008000000080000000800000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      0000FF00000080000000000000000000000086868600FFFFFF00FFFFFF00FFFF
      FF00800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      000080000000FF0000008000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      0000FF00000080000000FF00000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      000080000000FF0000008000000000000000FFFFFF00FFFF0000FFFFFF00FFFF
      0000800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      0000FF00000080000000FF00000000000000FFFF0000FFFFFF00FFFF0000FFFF
      FF00800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      000080000000FF0000008000000000000000FFFFFF00FFFF0000FFFFFF00FFFF
      0000800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      0000FF00000080000000FF00000000000000FFFF0000FFFFFF00FFFF0000FFFF
      FF00800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008000
      0000800000008000000080000000800000008000000080000000800000008000
      0000800000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000800000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000A08870009078600080706000807060008070600080706000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0704000B0583000B0583000A0502000A05020009048
      2000904820009040200080402000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00080685000203040002030400020304000203040002030
      400020304000203040002030400020304000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000A0908000FFFFFF00FFFFFF00FFF8FF00FFF8FF0080706000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C1AA9100B0835700925F3B00A2714E00AD856000B8A38D00C9BE
      B500C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0785000FFF8F000D0B0A000D0B0A000D0B0A000C0B0
      A000C0A8A000C0A8900090402000C0C0C000C0C0C00060809000506070004050
      6000304050002030400090706000F0E0D000B0A09000B0A09000B0A09000B0A0
      9000B0A09000B0A09000B0A0900020304000C0C0C00090889000706060005048
      500050505000A0908000FFFFFF00F0D8B000F0D8B000F0D8B000807060005050
      5000504850007060600070686000C0C0C000C0C0C000C0C0C000C0C0C000CDB3
      9B00C38E6900E0C8B000F0F0F000FFFFFF00FFFFFF00F0F0F000E0C8C000B792
      6F00BCAB9A00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000D0886000FFFFFF00E0906000D0805000D0805000D080
      5000D0805000C0A8A00090482000C0C0C0007080900020B8F0000090D0000090
      D0000090D0000090D00090786000F0E8E000F0D8D000E0D0C000E0C8C000D0C0
      B000D0B8B000D0B8B000B0A09000203040009090900090989000A0A0A0004038
      400040384000A0908000FFFFFF00FFE8D000E0785000F0D8B000807060004038
      4000403840009090900090909000726A6200C0C0C000C0C0C000C0C0C000E0A8
      8000FFF0E000E0B8A000D0805000C0582000C0582000D0805000E0B8A000F0E8
      E000B4947400BFAA9900C0C0C000C0C0C000B0A0900060483000604830006048
      30006048300060483000D0907000FFFFFF00FFFFFF00FFF0F000F0E0D000F0D0
      C000F0C0B000C0B0A00090482000C0C0C0007088900070C8F00010B8F00010B0
      F00000A8E0000098D000A0807000F0F0F000C0B0A000C0B0A000C0A8A000B0A0
      9000D0C0B000B0A09000B0A090002030400090909000A0A0A000909890004038
      40004038400090887000E0E8E000F0E0B000F0D8B000F0D8B000807060004038
      400040384000A0A0A000A0A0A00070686000C0C0C000C0C0C000D19D7700FFF0
      E000E0A89000C0501000C0501000E0A89000FFFFFF00B0481000B0481000D0A0
      8000F0F0E000B2866800C9BEB500C0C0C000B0A09000FFF0F000F0E0D000E0D8
      D000E0D0C000E0C8C000E0A08000FFFFFF00F0A88000E0987000E0906000D080
      5000D0805000D0B0A000A0482000C0C0C0008088900070D0F00030C0F00010B8
      F00000A8F00000A0E000A0888000FFF8FF00F0F0F000F0E8E000F0D8D000E0D0
      C000705850006050400050484000404040009088900090889000908890007070
      7000707070007070700070707000707070007070700070707000707070007070
      700070707000908890009080800070686000C0C0C000CEB39A00F0D8C000F0C8
      B000E0582000D0581000D0501000E0805000E0A88000C0501000B0481000B048
      1000E0B8A000E0C8C000B4A38D00C0C0C000B0A09000FFF8F000E0B08000E0A0
      7000E0A07000D0987000E0A89000FFFFFF00FFFFFF00FFFFFF00FFF8F000F0E8
      E000F0D0C000D0B0A000A0502000C0C0C0008090A00080D8F00040C8F00030C0
      F00010B8F00000A0E000B0908000FFFFFF00C0B0A000C0B0A000C0A8A000F0E0
      D00080605000D0C8C00060504000C0C0C00090889000C0B8C000D0C8D0008088
      8000B0A8B000B0A8B000B0A8B000B0A8B000B0B0B000B0B0B000B0B0B000B0B0
      B00080788000C0C8C000B0B0B00070686000C0C0C000D1966600FFF8F000F098
      7000F0602000E0582000E0582000F0A89000FFFFFF00D0501000C0501000B050
      1000C0785000F0F0F000A77A6100C0C0C000C0A89000FFFFFF00FFF8F000F0F0
      F000F0E8E000F0E0D000E0B8A000FFFFFF00FFB09000FFB09000F0D8D000E090
      6000B0583000B0583000A0502000C0C0C0008098A00090E0F00060D8F00050C8
      F00030C0F00010B0F000B0989000FFFFFF00FFFFFF00FFF8FF00F0F0F000F0E8
      E0008068500080605000C0C0C000C0C0C00090909000D0D0D000D0C8D0008088
      8000B0A8B000B0A8B000B0A8B000B0A8B000FFA86000FFA86000FFA86000B0B0
      B00080788000C0C8C000C0C0C00070686000C0C0C000D1884E00FFFFFF00FF78
      4000FF683000F0682000F0602000F0885000FFFFFF00F0C0B000C0582000B050
      1000B0582000FFFFFF00925F3B00C0C0C000C0A8A000FFFFFF00FFC8A000F0B8
      9000E0B08000E0A07000F0C0A000FFFFFF00FFFFFF00FFFFFF00FFFFFF00F098
      7000F0C8B000B0583000C0C0C000C0C0C0008098A000A0E8F00080E0F00070D8
      F00050D0F00010B0F000B0A09000B0989000B0908000A0888000A08070009078
      600090706000C0C0C000C0C0C000C0C0C00090909000F0F8F000F0F0F000A0A0
      A000D0D0D000D0D0D000D0D0D000D0D0D000D0D0D000D0D0D000D0D0D000D0D0
      D00090989000F0F0F000F0E8F00070686000C0C0C000D18F5B00FFFFFF00FF80
      5000FF703000FF683000FF683000FF682000F0906000FFF8F000F0D8C000C050
      2000C0582000FFFFFF00925F3B00C0C0C000C0B0A000FFFFFF00FFFFFF00FFF8
      FF00FFF0F000F0E8E000F0C8B000FFFFFF00FFFFFF00FFFFFF00FFFFFF00F0A8
      8000C0683000C0C0C000C0C0C000C0C0C00090A0A000B0F0FF00A0E8FF0090E0
      F00070D0F00010A0D00010A0D00010A0D0001098D0000090D0000090D0000090
      D00030384000C0C0C000C0C0C000C0C0C000A098A000FFFFFF00FFFFFF009090
      9000E0D8E000E0D8E000E0D8E000E0D8E000E0D8E000E0D8E000E0D8E000E0D8
      E00080888000F0F8F000F0F8F00070686000C0C0C000D69F7D00FFF8F000FFA8
      8000FF704000FF885000FFB09000FF703000F0682000F0907000FFFFFF00F080
      5000D0886000FFF0F000AD8E6800C0C0C000D0B8B000FFFFFF00FFD8C000FFD0
      B000F0E0D000B0A09000F0C8B000F0C0B000F0C0B000F0B8A000F0B09000F0B0
      9000C0C0C000C0C0C000C0C0C000C0C0C00090A0B000B0F0FF00A0F0FF006080
      9000607080005070800050687000506870005060700040587000207090000090
      D00040486000C0C0C000C0C0C000C0C0C000C0C0C000B0B0B000B0B0B0009090
      9000909090009090900090909000909090009088900090889000908890009088
      8000808880009090900090909000C0C0C000C0C0C000D5B89E00F0D8C000FFD0
      C000FF784000FF987000FFFFFF00FFC8B000FF906000FFC8B000FFF8F000F078
      4000F0C8B000E0C8B000C9B09700C0C0C000D0C0B000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00C0A89000D0C8C00090706000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C00090A8B000B0F0FF00B0F0FF006088
      900090C8D00090E8F00080D8E00060C8E0005098B000405860002080A0000090
      D00050587000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C0005656
      560070687000B0908000FFFFFF00FFFFFF00FFF8FF00FFF8FF00807060007070
      700055555500C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000E0A47700FFF8
      F000FFC0A000FF784000FFB8A000FFF8F000FFFFFF00FFF0E000FF987000F0B8
      A000FFF0E000C7946100CDC1B500C0C0C000E0C0B000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00C0B0A000A0806000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C00090A8B000B0F0F000B0F0FF00A0F0
      F0007098A000A0F0F0005068700080C8D000507080003060800060C0F00020B8
      F00050607000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C00050585000B0908000FFFFFF00FFFFFF00FFF8FF00FFF8FF00807060005058
      5000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000D7BDA300E1BA
      A100FFF8F000FFD0C000FFA88000FF885000FF885000FFA88000F0D0C000FFF0
      E000D2AB8300D0B6A000C0C0C000C0C0C000E0C0B000E0C0B000D0C0B000D0C0
      B000D0B8B000D0B0A000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C00090A8B00090A8B00090A8
      B0006090A000A0E8F000A0E8F00090D8E0004068700070889000808890007088
      9000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000B0908000FFFFFF00FFFFFF00FFFFFF00FFF8FF0080706000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000D7BD
      A400E0A47700F0D8C000FFF8F000FFFFFF00FFFFFF00FFF8F000F0D8C000C79B
      6F00D3BCA500C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C00080B0C00080B0C00080A0B000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000B0908000B0908000B0908000B0908000B0908000B0908000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000D0B69E00DFB28F00D4A27D00D19D6A00D3AA8B00D0B69E00CFC3
      B900C0C0C000C0C0C000C0C0C000C0C0C0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000925436005D3A2800C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000B7A2
      9300634935006349350063493500634935006349350063493500634935006349
      35006349350063493500C0C0C000C0C0C00075848F0066808F0060798700576E
      7B004E626F0044566100394852002E3A4300252E35001B22290014191E000E12
      16000E131800C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C3646500AA55
      5600A45253009F4F50009A4D4D00944A4A008F4747008944440083414100783B
      3C00783B3C00723939006E363700C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000D1794E00AB623F008A50330057362700C0C0C000C0C0C000603B2A005837
      2700C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000B7A2
      9300FFFFFF00B7A29300B7A29300B7A29300B7A29300B7A29300B7A29300B7A2
      9300B7A2930063493500C0C0C000C0C0C0007787920089A1AB006AB2D400008F
      CD00008FCD00008FCD00048CC7000888BE000F82B400157CA9001B779F001F72
      9600214A5B00C0C0C000C0C0C000C0C0C000C0C0C000CF6B6C00F38E8F00E680
      8100AA44240047322100C3B4AB00C6BBB300CAC1BC00CEC8C400564D48009E3E
      33009C3D36009839310072393900C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000DE825300C0C0C000C0C0C000844C3100C0C0C000C7744B00AA623E00633C
      2900291F1C00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000B7A2
      9300FFFFFF00FFFFFF00FCFAF900F7F1EE00F1E7E100ECDDD500E6D3C900E1CA
      BD00B7A2930063493500C0C0C000C0C0C0007A8A95007EBED3008AA4AE007EDC
      FF005FCFFF0055CBFF004CC4FA0041BCF50037B3F0002EAAEB0024A0E500138C
      D400236780001B2A3000C0C0C000C0C0C000C0C0C000D16F7000FF999A00EC86
      8700E6808100715B4B00473C34008D786800EDE0D800F1E7E0008F7F7300A341
      3500A2423C009C3D3500783B3C00C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000E2845500C0C0C000C0C0C0008B503300C0C0C000D57B5000C0C0C000C0C0
      C0006A402B00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000B7A2
      9300FFFFFF00FFFFFF00FEFEFE00FAF7F500F5EDE900EFE3DC00EAD9D100E4CF
      C400B7A2930063493500C0C0C000C0C0C0007D8E980079D2EC008BA4AD0089C2
      CE0071D8FF0065D3FF005CCEFF0051C9FE0049C1FA003FB9F50034B0EE0029A8
      E9001085CD00224B5B00C0C0C000C0C0C000C0C0C000D4757600FF9FA000F590
      9100EC868700715B4B0000000000473C3400E9D9CE00ECDDD40085746700AE4B
      4300AA494400A3423C007D3E3E00C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000E7875600E5865600B06641008E5235008D523500CA744B00C0C0C000C0C0
      C0008F533400C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000B7A2
      9300FFFFFF00FFFFFF00FFFFFF00FDFCFB00F8F3F000F2E9E300EDDFD800E7D5
      CB00B7A2930063493500C0C0C000C0C0C00080919C0081D7EF007DC5E0008CA6
      B00080DDFE0068D3FF0067D4FF0062D1FF0058CDFF004EC7FC0046BEF7003BB6
      F20031ACEC002569810014445900C0C0C000C0C0C000D77B7C00FFA9AA00FB9F
      A000F5939400715B4B00715B4B00715B4B00715B4B00766252007D6A5B00BA56
      5400B24F4C00AA49440083414100C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000EE8C5900DC8053009E5B3B008E523500BE6E4600D57B4F00B96B
      45009F5C3A00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000BAA5
      9600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FBF8F700F6EFEB00F0E5DF00EBDB
      D300B7A2930063493500C0C0C000C0C0C00083959F0089DCF1008CE2FF008DA8
      B1008CBAC70074D8FF0067D4FF0067D4FF0067D4FF005FD0FF0054CDFF004BC5
      FC0041BBF7002EA2DB00475E6C00C0C0C000C0C0C000DB838400FFB3B400FFAD
      AE00FCA3A400F48E8F00EC868700E6808100DF797A00D7717200D16B6C00C15D
      5C00BA565400B2504C0089444400C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000EB895800E0835400CA764B00CD774C00D37A4E00CB75
      4C00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000BEA9
      9A00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFDFC00F9F5F200F4EBE600EEE1
      DA00B7A2930063493500C0C0C000C0C0C000869AA30092E1F20098E8FD0080C4
      DE008EA7B00081DEFD0084E0FF0084E0FF0084E0FF0084E0FF0081DFFF007BDD
      FF0074D8FF006BD6FF0056A9D1004E626F00C0C0C000DF8A8B00FFBBBC00FFB6
      B700C9636000C45E5600BE584B00B8523F00B34D3400AD472800A7411C00A13B
      1100C15D5C00BA5654008F474700C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000846E60007160560086665400C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C3AE
      9E00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FCFAF900F7F1EE00F1E7
      E100B7A2930063493500C0C0C000C0C0C000889CA5009AE6F3009FEBFB0098E8
      FE008BACB9008BACB9008AAAB70088A6B30086A3AF00839FAA00819AA6007F95
      A1007C919D007A8E9900798B950077889300C0C0C000E2919200FFBDBE00CC66
      6700FFFFFF00FFFFFF00FBF8F600F6EEEA00F0E5DE00EADBD200E5D1C600E1CA
      BD00A13B1100C25D5C00944A4A00C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C0008E8074007E6E6300695D5500524B4600C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C8B2
      A300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00FAF7F500F5ED
      E900B7A2930063493500C0C0C000C0C0C0008BA0A800A0EAF600A6EEF9009FEB
      FB0098E8FE007ADAFF0067D4FF0067D4FF0067D4FF0067D4FF0067D4FF0067D4
      FF0077889300C0C0C000C0C0C000C0C0C000C0C0C000E5979800FFBDBE00D36D
      6E00FFFFFF00FFFFFF00FFFFFF00FBF8F600F6EEEA00F0E5DE00EADBD200E5D1
      C600A7411C00CC6767009A4D4D00C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000B8AAA100A2948B00A1968D008E8177005B524C00C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000CCB6
      A700FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FDFCFB00B7A2
      9300B7A29300644A3600C0C0C000C0C0C0008EA2AB00A7EEF600ABF0F700A6EE
      F9009FEBFB0098E8FD0071D4FB00899EA7008699A30082949F007E909A007A8C
      970077889300C0C0C000C0C0C000C0C0C000C0C0C000E99E9F00FFBDBE00DC76
      7700FFFFFF00FFFFFF00FFFFFF00FFFFFF00FBF8F600F6EEEA00F0E5DE00EADB
      D200AD472800D77172009F4F5000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000BEB1A900A1938A00C0C0C000A1938A006B5F5600C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000D1BB
      AB00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B7A29300644A
      3600644A3600644A3600C0C0C000C0C0C0008FA4AC00A0D2DA00ABF0F700ABF0
      F700A6EEF9009FEBFB008DA1AA00C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C0008E6A530091684F0093674C00C0C0C000EDA6A700FFBDBE00E680
      8100FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FBF8F600F6EEEA00F0E5
      DE00B34D3400DF797A00A4525300C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000A99B9200AB9C9300C0C0C000BFB2A9007C6F6600C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000D5BF
      AF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B9A49500D4C5
      BA00644A3600C0C0C000C0C0C000C0C0C000C0C0C0008FA4AC008FA4AC008FA4
      AC008FA4AC008FA4AC0088A9B600C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C0008D6B540090694F00C0C0C000F0ACAD00FFBDBE00EF89
      8A00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FBF8F600F6EE
      EA00B8523F0067333300AA555600C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000A3968C00C0C0C000C0C0C000C0C0C000A1938A00C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000D8C2
      B200FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C0AB9C00644A
      3600C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C00095746000C0C0C000C0C0
      C000C0C0C000A6918200C0C0C00094745F00C0C0C000F3B2B300FFBDBE00F892
      9300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FBF8
      F600BE584B00B0585900B0585900C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000BFB2A900B2A69B00C0C0C000C0C0C000C0C0C000BFB2A9009485
      7B00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000D8C2
      B200D8C2B200D8C2B200D8C2B200D8C2B200D4BEAE00CFB9A900C9B3A400C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000A6918100A189
      7800AA958700C0C0C000C0C0C000C0C0C000C0C0C000F5B6B700F5B6B700F3B2
      B300F1ADAE00EEA7A800EAA1A200E79A9B00E4939400E08E8F00DD878800DA80
      8100D67A7B00D3747500D16F7000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000E007000000000000E007000000000000E007000000000000
      E007000000000000E007000000000000E007000000000000E007000000000000
      E007000000000000FFFF000000000000F81F000000000000F81F000000000000
      F81F000000000000FFFF000000000000FFFFFFFFFFFFFFFF0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFFFFFFFFFFFFFF0000000000000000
      0000000000000000000000000000000000000000000000000000000002000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000}
  end
  object ProjTreeViewPopup: TPopupMenu
    OnPopup = ProjTreeViewPopupPopup
    Left = 48
    Top = 224
    object ProjectOptions1: TMenuItem
      Caption = 'Project Options'
    end
    object AddRenderProject1: TMenuItem
      Action = AddRenderProject
    end
    object RemoveFromProject1: TMenuItem
      Action = RemoveFromProjectA
    end
    object Rename: TMenuItem
      Caption = 'Rename'
      OnClick = RenameClick
    end
    object Close2: TMenuItem
      Action = CloseProjectA
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 369
    Top = 912
    object Action11: TMenuItem
      Action = ToggleBottomPanelA
    end
  end
  object MainPCPopup: TPopupMenu
    Left = 320
    Top = 161
    object Close3: TMenuItem
      Caption = 'Close Page'
      OnClick = Close3Click
    end
    object Properties1: TMenuItem
      Caption = 'Properties'
    end
  end
end
