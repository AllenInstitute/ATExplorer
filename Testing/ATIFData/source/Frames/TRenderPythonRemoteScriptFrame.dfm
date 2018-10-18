object RenderPythonRemoteScriptFrame: TRenderPythonRemoteScriptFrame
  Left = 0
  Top = 0
  Width = 699
  Height = 576
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 699
    Height = 169
    Align = alTop
    Caption = 'Render Parameters'
    TabOrder = 0
    Visible = False
    object RenderHostE: TSTDStringLabeledEdit
      Left = 16
      Top = 38
      Width = 121
      Height = 21
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'Host'
      TabOrder = 0
      Text = 'ibs-forrestc-ux1'
      Value = 'ibs-forrestc-ux1'
    end
    object RenderOwnerE: TSTDStringLabeledEdit
      Left = 16
      Top = 84
      Width = 121
      Height = 21
      EditLabel.Width = 32
      EditLabel.Height = 13
      EditLabel.Caption = 'Owner'
      Enabled = False
      TabOrder = 1
    end
    object RenderProjectE: TSTDStringLabeledEdit
      Left = 176
      Top = 84
      Width = 201
      Height = 21
      EditLabel.Width = 72
      EditLabel.Height = 13
      EditLabel.Caption = 'Render Project'
      Enabled = False
      TabOrder = 2
    end
    object RenderClientScriptsFolderE: TSTDStringLabeledEdit
      Left = 16
      Top = 131
      Width = 361
      Height = 21
      EditLabel.Width = 103
      EditLabel.Height = 13
      EditLabel.Caption = 'Render Scripts Folder'
      TabOrder = 3
      Text = '/var/www/render/render-ws-java-client/src/main/scripts'
      Value = '/var/www/render/render-ws-java-client/src/main/scripts'
    end
    object RenderHostPortE: TIntegerLabeledEdit
      Left = 304
      Top = 38
      Width = 73
      Height = 21
      EditLabel.Width = 20
      EditLabel.Height = 13
      EditLabel.Caption = 'Port'
      TabOrder = 4
      Text = '80'
      Value = 80
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 169
    Width = 699
    Height = 407
    Align = alClient
    TabOrder = 1
    object StacksGB: TGroupBox
      Left = 1
      Top = 1
      Width = 185
      Height = 405
      Align = alLeft
      Caption = 'Stacks'
      TabOrder = 0
      object StacksForProjectCB: TCheckListBox
        AlignWithMargins = True
        Left = 17
        Top = 18
        Width = 163
        Height = 382
        Margins.Left = 15
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
      end
    end
    object GroupBox2: TGroupBox
      Left = 186
      Top = 1
      Width = 512
      Height = 405
      Align = alClient
      Caption = 'Parameters'
      TabOrder = 1
      DesignSize = (
        512
        405)
      object ExecuteBtn: TButton
        Left = 29
        Top = 274
        Width = 115
        Height = 73
        Anchors = [akTop]
        Caption = 'Execute'
        TabOrder = 0
      end
    end
  end
end
