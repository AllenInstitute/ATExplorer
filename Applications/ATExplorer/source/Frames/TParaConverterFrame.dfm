object ParaConverterFrame: TParaConverterFrame
  Left = 0
  Top = 0
  Width = 764
  Height = 571
  TabOrder = 0
  object SettingsGB: TGroupBox
    Left = 0
    Top = 70
    Width = 764
    Height = 501
    Align = alClient
    Caption = 'Settings'
    TabOrder = 0
    object RunGB: TGroupBox
      Left = 2
      Top = 145
      Width = 760
      Height = 354
      Align = alClient
      Caption = 'Run'
      TabOrder = 0
      object NumberOfProcessesE: TIntegerLabeledEdit
        Left = 16
        Top = 35
        Width = 103
        Height = 21
        EditLabel.Width = 134
        EditLabel.Height = 13
        EditLabel.Caption = 'Number of Processes (>=2)'
        NumbersOnly = True
        TabOrder = 0
        Text = '9'
        Value = 9
      end
      object RunBtn: TButton
        Left = 344
        Top = 16
        Width = 89
        Height = 49
        Caption = 'Run'
        TabOrder = 1
        OnClick = RunBtnClick
      end
      object NicenessE: TIntegerLabeledEdit
        Left = 184
        Top = 35
        Width = 103
        Height = 21
        EditLabel.Width = 42
        EditLabel.Height = 13
        EditLabel.Caption = 'Niceness'
        NumbersOnly = True
        TabOrder = 2
        Text = '5'
        Value = 5
      end
      object KillBtn: TButton
        Left = 439
        Top = 16
        Width = 89
        Height = 49
        Caption = 'Kill'
        TabOrder = 3
        OnClick = KillBtnClick
      end
    end
    object Panel1: TPanel
      Left = 2
      Top = 15
      Width = 760
      Height = 130
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object GroupBox3: TGroupBox
        Left = 0
        Top = 0
        Width = 337
        Height = 130
        Align = alLeft
        Caption = 'Input/Output'
        TabOrder = 0
        object InputFolderE: TSTDStringLabeledEdit
          Left = 16
          Top = 36
          Width = 305
          Height = 21
          EditLabel.Width = 102
          EditLabel.Height = 13
          EditLabel.Caption = 'Image Folder (TIFFS)'
          TabOrder = 0
        end
        object OutputFolderE: TSTDStringLabeledEdit
          Left = 16
          Top = 83
          Width = 305
          Height = 21
          EditLabel.Width = 112
          EditLabel.Height = 13
          EditLabel.Caption = 'Output Folder (Terafly)'
          TabOrder = 1
        end
      end
      object GroupBox2: TGroupBox
        Left = 337
        Top = 0
        Width = 423
        Height = 130
        Align = alClient
        Caption = 'Box generation'
        TabOrder = 1
        object BoxHeightE: TIntegerLabeledEdit
          Left = 87
          Top = 37
          Width = 50
          Height = 21
          EditLabel.Width = 31
          EditLabel.Height = 13
          EditLabel.Caption = 'Height'
          NumbersOnly = True
          TabOrder = 0
          Text = '512'
          Value = 512
        end
        object BoxWidthE: TIntegerLabeledEdit
          Left = 16
          Top = 36
          Width = 50
          Height = 21
          EditLabel.Width = 28
          EditLabel.Height = 13
          EditLabel.Caption = 'Width'
          NumbersOnly = True
          TabOrder = 1
          Text = '512'
          Value = 512
        end
        object BoxDepthE: TIntegerLabeledEdit
          Left = 158
          Top = 37
          Width = 50
          Height = 21
          EditLabel.Width = 29
          EditLabel.Height = 13
          EditLabel.Caption = 'Depth'
          NumbersOnly = True
          TabOrder = 2
          Text = '512'
          Value = 512
        end
        object ResolutionsE: TSTDStringLabeledEdit
          Left = 16
          Top = 85
          Width = 50
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 13
          EditLabel.Caption = 'Resolutions'
          TabOrder = 3
          Text = '012345'
          Value = '012345'
        end
      end
    end
  end
  inline TSSHFrame1: TSSHFrame
    Left = 0
    Top = 0
    Width = 764
    Height = 70
    Align = alTop
    AutoSize = True
    TabOrder = 1
    ExplicitWidth = 764
    inherited GroupBox1: TGroupBox
      inherited ConnectBtn: TButton
        OnClick = TSSHFrame1ConnectBtnClick
      end
    end
    inherited ScSSHShell1: TScSSHShell
      OnAsyncReceive = TSSHFrame1ScSSHShell1AsyncReceive
    end
    inherited ScSSHClient: TScSSHClient
      AfterConnect = TSSHFrame1ScSSHClientAfterConnect
      AfterDisconnect = TSSHFrame1ScSSHClientAfterDisconnect
    end
  end
  object ScriptMemo: TMemo
    Left = 380
    Top = 360
    Width = 361
    Height = 137
    Lines.Strings = (
      '#! /bin/bash'
      'echo "Running script..."'
      ''
      'args=("$@")'
      '#Data output folder'
      'outputFolder=${args[0]}'
      ''
      '#Data input folder'
      'inputFolder=${args[1]}'
      ''
      '#Number of processes'
      'nrofProcs=${args[2]}'
      'nrofPyProcs=$(($nrofProcs-1))'
      ''
      '#Job niceness'
      'niceness=${args[3]}'
      ''
      '#Box Width, Height and Depth'
      'boxW=${args[4]}'
      'boxH=${args[5]}'
      'boxD=${args[6]}'
      ''
      '#Output resolutions (Pyramids)'
      'resolutions=${args[7]}'
      ''
      '#Source format'
      'srcFormat="TIFF (series, 2D)"'
      ''
      '#Destination Format'
      'destFormat="TIFF (tiled, 3D)"'
      ''
      '#Write run info to file'
      'info=$outputFolder"/terraFly_info.txt"'
      'echo "Writing info to file: "$info       | tee $info'
      'echo "This job was started on: "`date`  | tee -a $info'
      'echo "Input Folder: "$inputFolder       | tee -a $info'
      'echo "Output Folder: "$outputFolder     | tee -a $info'
      'echo "Number of Processes: "$nrofProcs  | tee -a $info'
      'echo "Job niceness: "$niceness          | tee -a $info'
      'echo "Output Box Width:  "$boxW         | tee -a $info'
      'echo "Output Box Height: "$boxH         | tee -a $info'
      'echo "Output Box Depth:  "$boxD         | tee -a $info'
      'echo "Resolutions:  "$resolutions       | tee -a $info'
      'echo "Source format: "$srcFormat        | tee -a $info'
      'echo "Destination format: "$destFormat  | tee -a $info'
      ''
      'script_name=`basename "$0"`'
      'script_path="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"'
      'cd $script_path'
      'running_from=`pwd -P`'
      'echo "Script path: "$script_path | tee -a $info'
      'echo "Running from: "$running_from | tee -a $info'
      ''
      'tc="/pipeline/teraconverter/teraconverter"'
      'pc2="/pipeline/teraconverter/paraconverter2.py"'
      ''
      'echo "Executing PARACONVERTER python script" | tee -a $info'
      
        'echo "eval nice -n $niceness mpirun -np $nrofProcs python $pc2 -' +
        '-np $nrofPyProcs --sfmt=\"$srcFormat\" --dfmt=\"$destFormat\" --' +
        'width=$boxW --height=$boxH --depth=$boxH -s=$inputFolder -d=$out' +
        'putFolder --resolutions=$resolutions 2>&1 | tee -a $info"'
      ''
      
        'eval nice -n $niceness mpirun -np $nrofProcs python $pc2 --np $n' +
        'rofPyProcs --sfmt=\"$srcFormat\" --dfmt=\"$destFormat\" --width=' +
        '$boxW --height=$boxH --depth=$boxH -s=$inputFolder -d=$outputFol' +
        'der --resolutions=$resolutions 2>&1 | tee -a $info'
      ''
      'echo "This job ended on: "`date` | tee -a $info')
    TabOrder = 2
    Visible = False
    WordWrap = False
  end
end
