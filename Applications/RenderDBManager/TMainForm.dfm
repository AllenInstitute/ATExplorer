object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'RenderDB Manager'
  ClientHeight = 751
  ClientWidth = 1216
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 545
    Width = 1216
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 64
    ExplicitTop = 565
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 1216
    Height = 545
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    object TabSheet2: TTabSheet
      Caption = 'Render Projects'
      ImageIndex = 1
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 529
        Height = 517
        Align = alLeft
        TabOrder = 0
        object Panel4: TPanel
          Left = 1
          Top = 1
          Width = 185
          Height = 515
          Align = alLeft
          TabOrder = 0
          object RenderProjectsLB: TListBox
            Left = 1
            Top = 53
            Width = 183
            Height = 420
            Align = alClient
            ItemHeight = 13
            PopupMenu = RenderProjectsPopup
            TabOrder = 0
            OnClick = RenderProjectsLBClick
            OnKeyDown = DeleteItem
          end
          object Panel5: TPanel
            Left = 1
            Top = 473
            Width = 183
            Height = 41
            Align = alBottom
            TabOrder = 1
            object Button2: TButton
              Left = 8
              Top = 6
              Width = 114
              Height = 25
              Action = PopulateRPOwners
              TabOrder = 0
            end
          end
          object Panel6: TPanel
            Left = 1
            Top = 1
            Width = 183
            Height = 52
            Align = alTop
            TabOrder = 2
            object Label2: TLabel
              Left = 8
              Top = 8
              Width = 32
              Height = 13
              Caption = 'Owner'
            end
            object RPOwnersCB: TComboBox
              Left = 1
              Top = 30
              Width = 181
              Height = 21
              Align = alBottom
              Sorted = True
              TabOrder = 0
              Text = 'OwnersCB'
              OnCloseUp = PopulateRPProjectsForOwnerAExecute
            end
          end
        end
        object RenderStacksLB: TCheckListBox
          Left = 186
          Top = 1
          Width = 342
          Height = 515
          Align = alClient
          ItemHeight = 13
          PopupMenu = StacksPopup
          TabOrder = 1
          OnKeyDown = DeleteItem
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'PointMatches'
      object PointMatchesPanel: TPanel
        Left = 0
        Top = 0
        Width = 529
        Height = 517
        Align = alLeft
        TabOrder = 0
        object LeftPanel: TPanel
          Left = 1
          Top = 1
          Width = 185
          Height = 515
          Align = alLeft
          TabOrder = 0
          object PMCollections: TListBox
            Left = 1
            Top = 53
            Width = 183
            Height = 420
            Align = alClient
            ItemHeight = 13
            PopupMenu = PMCListPopup
            TabOrder = 0
            OnKeyDown = DeleteItem
          end
          object Panel1: TPanel
            Left = 1
            Top = 473
            Width = 183
            Height = 41
            Align = alBottom
            TabOrder = 1
            object Button1: TButton
              Left = 1
              Top = 6
              Width = 114
              Height = 25
              Action = PopulatePointMatchOwnersA
              TabOrder = 0
            end
          end
          object Panel2: TPanel
            Left = 1
            Top = 1
            Width = 183
            Height = 52
            Align = alTop
            TabOrder = 2
            object Label1: TLabel
              Left = 8
              Top = 8
              Width = 32
              Height = 13
              Caption = 'Owner'
            end
            object PMOwnersCB: TComboBox
              Left = 1
              Top = 30
              Width = 181
              Height = 21
              Align = alBottom
              Sorted = True
              TabOrder = 0
              Text = 'PMOwnersCB'
              OnCloseUp = PMOwnersCBCloseUp
            end
          end
        end
      end
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 548
    Width = 1216
    Height = 203
    Align = alBottom
    TabOrder = 1
    object LogMemoFrame1: TLogMemoFrame
      Left = 1
      Top = 1
      Width = 1214
      Height = 201
      Align = alClient
      TabOrder = 0
    end
  end
  object RenderAPIActions: TActionList
    Left = 61
    Top = 353
    object PopulatePointMatchOwnersA: TAction
      Caption = 'Populate'
      OnExecute = PopulatePointMatchOwnersAExecute
    end
    object PopulateCollectionsForOwnerA: TAction
      Caption = 'PopulateCollectionsForOwnerA'
      OnExecute = PopulateCollectionsForOwnerAExecute
    end
    object PopulateRPOwners: TAction
      Caption = 'PopulateRPOwners'
      OnExecute = PopulateRPOwnersExecute
    end
    object PopulateRPProjectsForOwnerA: TAction
      Caption = 'PopulateRPProjectsForOwnerA'
      OnExecute = PopulateRPProjectsForOwnerAExecute
    end
    object DeleteRenderProjectA: TAction
      Caption = 'Delete'
      OnExecute = DeleteRenderProjectAExecute
    end
    object PopulateRenderStacksForProjectA: TAction
      Caption = 'PopulateRenderStacksForProjectA'
      OnExecute = PopulateRenderStacksForProjectAExecute
    end
    object DeleteStackA: TAction
      Caption = 'Delete'
      OnExecute = DeleteStackAExecute
    end
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 396
    Top = 240
  end
  object PMCListPopup: TPopupMenu
    Left = 77
    Top = 193
    object DeletePMCA: TMenuItem
      Caption = 'Delete'
      OnClick = DeletePMCAClick
    end
  end
  object RenderProjectsPopup: TPopupMenu
    Left = 45
    Top = 257
    object MenuItem1: TMenuItem
      Action = DeleteRenderProjectA
    end
  end
  object StacksPopup: TPopupMenu
    Left = 277
    Top = 153
    object MenuItem2: TMenuItem
      Action = DeleteStackA
    end
  end
end
