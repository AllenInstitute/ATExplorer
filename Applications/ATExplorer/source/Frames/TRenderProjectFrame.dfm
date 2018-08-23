object RenderProjectFrame: TRenderProjectFrame
  Left = 0
  Top = 0
  Width = 972
  Height = 862
  TabOrder = 0
  object ControlsPC: TPageControl
    Left = 0
    Top = 0
    Width = 439
    Height = 862
    ActivePage = TabSheet7
    Align = alLeft
    TabOrder = 0
    object TabSheet7: TTabSheet
      Caption = 'Project'
      object mLeftPanel: TPanel
        Left = 0
        Top = 0
        Width = 385
        Height = 834
        Align = alLeft
        TabOrder = 0
        object ScrollBox1: TScrollBox
          Left = 1
          Top = 1
          Width = 287
          Height = 832
          Align = alClient
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 0
          object GroupBox1: TGroupBox
            Left = 0
            Top = 0
            Width = 266
            Height = 185
            Align = alTop
            Caption = 'Project Selection'
            TabOrder = 0
            DesignSize = (
              266
              185)
            object Label1: TLabel
              Left = 16
              Top = 22
              Width = 32
              Height = 13
              Caption = 'Owner'
            end
            object Label2: TLabel
              Left = 17
              Top = 74
              Width = 34
              Height = 13
              Caption = 'Project'
            end
            object Label3: TLabel
              Left = 17
              Top = 127
              Width = 31
              Height = 13
              Caption = 'Stacks'
            end
            object OwnerCB: TComboBox
              Left = 17
              Top = 38
              Width = 207
              Height = 21
              Style = csDropDownList
              Anchors = [akLeft, akTop, akRight]
              TabOrder = 0
            end
            object ProjectCB: TComboBox
              Left = 16
              Top = 93
              Width = 208
              Height = 21
              Style = csDropDownList
              Anchors = [akLeft, akTop, akRight]
              DropDownCount = 25
              TabOrder = 1
            end
            object StackCB: TComboBox
              Left = 17
              Top = 146
              Width = 224
              Height = 21
              Hint = 'Test'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 2
              Text = 'StackCB'
            end
          end
          object GroupBox5: TGroupBox
            Left = 0
            Top = 680
            Width = 266
            Height = 197
            Align = alBottom
            Caption = 'Extra'
            TabOrder = 1
            object RzSpinButtons1: TRzSpinButtons
              Left = 11
              Top = 124
              Width = 94
              Height = 25
              Delay = 15
              FocusControl = CustomImageRotationE
              Orientation = orHorizontal
              TabOrder = 0
            end
            object CustomImageRotationE: TFloatLabeledEdit
              Left = 17
              Top = 88
              Width = 96
              Height = 21
              EditLabel.Width = 80
              EditLabel.Height = 13
              EditLabel.Caption = 'Custom Rotation'
              TabOrder = 1
              Text = '0.0'
            end
            object ShowImageGridCB: TCheckBox
              Left = 17
              Top = 36
              Width = 122
              Height = 17
              TabOrder = 2
            end
          end
          object imageParasGB: TGroupBox
            Left = 0
            Top = 473
            Width = 266
            Height = 207
            Align = alTop
            Caption = 'Region of Interest (ROI)'
            TabOrder = 2
            object mScaleE: TFloatLabeledEdit
              Left = 16
              Top = 34
              Width = 50
              Height = 21
              EditLabel.Width = 25
              EditLabel.Height = 13
              EditLabel.Caption = 'Scale'
              TabOrder = 0
              Text = '0.0500'
              Value = 0.050000000000000000
            end
            object mResetButton: TButton
              Left = 144
              Top = 120
              Width = 135
              Height = 79
              Caption = 'Reset to Layer Bounds'
              TabOrder = 5
              WordWrap = True
            end
            object Width: TIntegerLabeledEdit
              Left = 17
              Top = 122
              Width = 49
              Height = 21
              EditLabel.Width = 28
              EditLabel.Height = 13
              EditLabel.Caption = 'Width'
              TabOrder = 3
              Text = '12000'
              Value = 12000
            end
            object Height: TIntegerLabeledEdit
              Left = 88
              Top = 122
              Width = 50
              Height = 21
              EditLabel.Width = 31
              EditLabel.Height = 13
              EditLabel.Caption = 'Height'
              TabOrder = 4
              Text = '32000'
              Value = 32000
            end
            object XCoordE: TIntegerLabeledEdit
              Left = 17
              Top = 76
              Width = 49
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'X'
              TabOrder = 1
              Text = '8000'
              Value = 8000
            end
            object YCoordE: TIntegerLabeledEdit
              Left = 88
              Top = 76
              Width = 50
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'Y'
              TabOrder = 2
              Text = '3200'
              Value = 3200
            end
            object MaxIntensityE: TIntegerLabeledEdit
              Left = 157
              Top = 34
              Width = 66
              Height = 21
              EditLabel.Width = 66
              EditLabel.Height = 13
              EditLabel.Caption = 'Max Intensity'
              TabOrder = 6
              Text = '65535'
              Value = 65535
            end
            object MinIntensityE: TIntegerLabeledEdit
              Left = 85
              Top = 34
              Width = 66
              Height = 21
              EditLabel.Width = 62
              EditLabel.Height = 13
              EditLabel.Caption = 'Min Intensity'
              TabOrder = 7
              Text = '0'
            end
            object ScaleConstantE: TFloatLabeledEdit
              Left = 160
              Top = 76
              Width = 103
              Height = 21
              EditLabel.Width = 101
              EditLabel.Height = 13
              EditLabel.Caption = 'Extra Scale Constant'
              TabOrder = 8
              Text = '1.0000'
              Value = 1.000000000000000000
            end
          end
          object GroupBox9: TGroupBox
            Left = 0
            Top = 185
            Width = 266
            Height = 288
            Align = alTop
            Caption = 'ROI'#39's'
            TabOrder = 3
            object ROI_CB: TCheckListBox
              Left = 2
              Top = 15
              Width = 262
              Height = 230
              Align = alClient
              ItemHeight = 13
              TabOrder = 0
            end
            object Panel4: TPanel
              Left = 2
              Top = 245
              Width = 262
              Height = 41
              Align = alBottom
              TabOrder = 1
              object Button1: TButton
                Left = 15
                Top = 6
                Width = 75
                Height = 25
                Caption = 'Refresh'
                TabOrder = 0
              end
            end
          end
        end
        object ZsPanel: TPanel
          Left = 288
          Top = 1
          Width = 96
          Height = 832
          Align = alRight
          TabOrder = 1
          object Zs_GB: TGroupBox
            Left = 1
            Top = 1
            Width = 94
            Height = 332
            Align = alClient
            Caption = 'Sections'
            TabOrder = 0
            object mZs: TCheckListBox
              Left = 2
              Top = 15
              Width = 90
              Height = 315
              Align = alClient
              ItemHeight = 13
              TabOrder = 0
            end
          end
          object CacheGB: TGroupBox
            Left = 1
            Top = 693
            Width = 94
            Height = 138
            Align = alBottom
            Caption = 'Local Cache'
            TabOrder = 1
            object FetchSelectedZsBtn: TButton
              Left = 5
              Top = 19
              Width = 86
              Height = 50
              Caption = 'Generate'
              TabOrder = 0
            end
            object ClearCacheBtn: TButton
              Left = 5
              Top = 75
              Width = 86
              Height = 50
              Caption = 'Clear'
              TabOrder = 1
            end
          end
          object GroupBox2: TGroupBox
            Left = 1
            Top = 513
            Width = 94
            Height = 180
            Align = alBottom
            Caption = 'Other'
            TabOrder = 2
            object OtherCB: TCheckListBox
              Left = 2
              Top = 15
              Width = 90
              Height = 163
              Align = alClient
              ItemHeight = 13
              TabOrder = 0
            end
          end
          object GroupBox7: TGroupBox
            Left = 1
            Top = 333
            Width = 94
            Height = 180
            Align = alBottom
            Caption = 'Stacks'
            TabOrder = 3
            object StacksCB: TCheckListBox
              Left = 2
              Top = 15
              Width = 90
              Height = 163
              Align = alClient
              ItemHeight = 13
              TabOrder = 0
            end
          end
        end
      end
    end
    object TransformsTab: TTabSheet
      Caption = 'Transforms'
      ImageIndex = 1
      inline TAffineTransformationFrame1: TAffineTransformationFrame
        Left = 0
        Top = 0
        Width = 431
        Height = 834
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 431
        ExplicitHeight = 834
        inherited GroupBox1: TGroupBox
          Width = 431
          ExplicitWidth = 431
          inherited RenderClientScriptsFolderE: TSTDStringLabeledEdit
            EditLabel.ExplicitWidth = 130
          end
          inherited RenderHostPortE: TIntegerLabeledEdit
            EditLabel.ExplicitWidth = 51
          end
        end
        inherited Panel2: TPanel
          Width = 431
          Height = 665
          ExplicitWidth = 431
          ExplicitHeight = 665
          inherited StacksGB: TGroupBox
            Height = 663
            ExplicitHeight = 663
            inherited StacksForProjectCB: TCheckListBox
              Height = 640
              ExplicitHeight = 640
            end
          end
          inherited GroupBox2: TGroupBox
            Width = 244
            Height = 663
            ExplicitWidth = 244
            ExplicitHeight = 663
            DesignSize = (
              244
              663)
            inherited TranslateYE: TIntegerLabeledEdit
              Visible = False
            end
            inherited TranslateXE: TIntegerLabeledEdit
              Visible = False
            end
            inherited ExecuteBtn: TButton
              Left = 18
              ExplicitLeft = 18
            end
            inherited ProgressBar1: TProgressBar
              Top = 645
              Width = 240
              ExplicitLeft = 2
              ExplicitTop = 645
              ExplicitWidth = 240
            end
          end
        end
      end
    end
    object TabSheet8: TTabSheet
      Caption = 'Volume Creation'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object ScriptsPC: TPageControl
        Left = 0
        Top = 329
        Width = 431
        Height = 318
        ActivePage = TabSheet6
        Align = alClient
        TabOrder = 0
        object TabSheet6: TTabSheet
          Caption = 'Stack Creation'
          ExplicitLeft = 0
          ExplicitTop = 0
          ExplicitWidth = 0
          ExplicitHeight = 0
        end
      end
      object StackGenerationGB: TGroupBox
        Left = 0
        Top = 0
        Width = 431
        Height = 329
        Align = alTop
        Caption = 'Stack Output Settings'
        TabOrder = 1
        object Label4: TLabel
          Left = 15
          Top = 155
          Width = 55
          Height = 13
          Caption = 'Image type'
        end
        object BoundsCB: TPropertyCheckBox
          Left = 15
          Top = 132
          Width = 97
          Height = 17
          Caption = 'Static Bounds'
          Checked = True
          Enabled = False
          State = cbChecked
          TabOrder = 0
          Value = True
        end
        object CreateTIFFStackCB: TPropertyCheckBox
          Left = 13
          Top = 267
          Width = 212
          Height = 17
          Caption = 'Create TIFFSTACK (max size ~ 4GB)'
          TabOrder = 1
        end
        object DeleteTempTiffsCB: TPropertyCheckBox
          Left = 29
          Top = 290
          Width = 146
          Height = 17
          Caption = 'Delete temporary TIFFS'
          Enabled = False
          TabOrder = 2
        end
        object PadFileNamesWithZeroesCB: TPropertyCheckBox
          Left = 13
          Top = 244
          Width = 178
          Height = 17
          Caption = 'Pad File Names with Zeroes'
          Checked = True
          Enabled = False
          State = cbChecked
          TabOrder = 3
          Value = True
        end
        object SubFolder1: TSTDStringLabeledEdit
          Left = 15
          Top = 93
          Width = 182
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 13
          EditLabel.Caption = 'Subfolder 1'
          TabOrder = 4
          Text = 'Test'
          Value = 'Test'
        end
        object VolumesFolder: TSTDStringLabeledEdit
          Left = 15
          Top = 42
          Width = 182
          Height = 21
          EditLabel.Width = 93
          EditLabel.Height = 13
          EditLabel.Caption = 'Output Root Folder'
          TabOrder = 5
          Text = '/nas4/volumes'
          Value = '/nas4/volumes'
        end
        object VolumesScaleE: TFloatLabeledEdit
          Left = 15
          Top = 218
          Width = 145
          Height = 21
          EditLabel.Width = 25
          EditLabel.Height = 13
          EditLabel.Caption = 'Scale'
          TabOrder = 6
          Text = '0.5000'
          Value = 0.500000000000000000
        end
        object ImageTypeCB: TComboBox
          Left = 15
          Top = 174
          Width = 145
          Height = 21
          Style = csDropDownList
          ItemIndex = 1
          TabOrder = 7
          Text = '16 bit'
          Items.Strings = (
            '24 bit (RGB)'
            '16 bit'
            '8 bit')
        end
      end
      object BashScriptMemo: TMemo
        Left = 49
        Top = 327
        Width = 336
        Height = 273
        Lines.Strings = (
          '#! /bin/bash'
          'args=("$@")'
          'nrOfSections=${args[0]}'
          'sections_str=${args[1]}'
          'rootOutPutFolder=${args[2]}'
          'customFolder=${args[3]}'
          'stack=${args[4]}'
          'owner=${args[5]}'
          'proj=${args[6]}'
          'scale=${args[7]}'
          'create_tiff_stack=${args[8]}'
          'delete_individual_tiffs=${args[9]}'
          'z_batch_size=${args[10]}'
          'max_number_of_jobs=${args[11]}'
          'job_niceness=${args[12]}'
          'imageType=${args[13]}'
          'padFileNamesWithZeroes=${args[14]}'
          'use_bounds=${args[15]}'
          'bounds=${args[16]}'
          ''
          'fmt='#39'tiff'#39
          'filter='#39'false'#39
          'baseDataURL='#39'http://ibs-forrestc-ux1:8988/render-ws/v1'#39
          ''
          '#Write run info to file'
          'info=$rootOutPutFolder/$customFolder/$stack"_info.txt"'
          'echo "This job was started on: "`date` > $info'
          'echo "Owner: "$owner >> $info'
          'echo "Project: "$proj >> $info'
          'echo "StackName: "$stack >> $info'
          'echo "Outputfolder: "$customFolder >> $info'
          'echo "Custom Output Folder: "$stack >> $info'
          'echo "Scale: "$scale >> $info'
          'echo "Format: "$fmt >> $info'
          'echo "Filter: "$filter >> $info'
          'echo "BaseDataURL: "$baseDataURL >> $info'
          'echo "Using static bounds: "$use_bounds >> $info'
          'echo "Number of Z'#39's: "$nrOfSections >> $info'
          'echo "Create tiffstack: "$create_tiff_stack >> $info'
          
            'echo "Delete individual TIFFs: "$delete_individual_tiffs >> $inf' +
            'o'
          'echo "Z Batch Size: "$z_batch_size >> $info'
          'echo "Max number of jobs: "$max_number_of_jobs >> $info'
          'echo "Job niceness: "$job_niceness >> $info'
          'echo "Zs: "$sections_str >> $info'
          'echo "Image type (bits): "$imageType >> $info'
          
            'echo "Pad Filenames with Zeroes: "$padFileNamesWithZeroes >> $in' +
            'fo'
          'if [ "$use_bounds"  == "true" ]; then'
          '   echo "Using bounds:" $bounds >> $info'
          'fi'
          ''
          '#JAVA CLIENT SETTINGS'
          '#Class path'
          
            'classpath='#39' /nas4/getVolume/render/render-ws-java-client/target/' +
            'render-ws-java-client-2.0.1-SNAPSHOT-standalone.jar'#39
          ''
          '#Java class'
          'jc='#39'org.janelia.render.client.RenderSectionClient'#39
          'script_name=`basename "$0"`'
          'script_path="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"'
          'running_from=`pwd -P`'
          ''
          '#echo "This script file name is:"$script_name'
          '#echo "Located in folder: "$script_path'
          '#echo "Running from folder: "$running_from'
          ''
          'mkdir -p $rootOutPutFolder/$customFolder/$stack'
          ''
          
            '#Create job inputs =============================================' +
            '='
          'echo "Parsing z'#39's"'
          'read -r -a sections <<<"$sections_str"'
          'for ((i=0; i<${#sections[@]}; i+=z_batch_size)); do'
          '  current_pieces=( "${sections[@]:i:z_batch_size}" )'
          '  z_batch+=( "${current_pieces[*]}" )'
          '  #echo $i'
          '  if (( $i > $nrOfSections ))'
          '  then'
          '     break'
          '  fi'
          'done'
          ''
          'echo "Starting jobs"'
          'jobs=0'
          'for ((i=0; i<${#z_batch[@]}; i+=1)); do'
          '    jobs=$jobs+1'
          '    echo "Starting job# $i"'
          '    echo ${z_batch[$i]}'
          ''
          '    if [ "$use_bounds"  == "false" ]; then'
          
            '        java_args="  -cp $classpath $jc --stack $stack --rootDir' +
            'ectory $rootOutPutFolder --customOutputFolder '
          
            '$customFolder --customSubFolder $stack --scale $scale --owner $o' +
            'wner --padFileNamesWithZeroes '
          '$padFileNamesWithZeroes'
          
            '--imageType $imageType --doFilter false --fillWithNoise false --' +
            'baseDataUrl $baseDataURL --format $fmt --project $proj'
          '${z_batch[$i]}"'
          '    else'
          
            '        java_args="  -cp $classpath $jc --stack $stack --rootDir' +
            'ectory $rootOutPutFolder --customOutputFolder '
          
            '$customFolder --customSubFolder $stack --scale $scale --owner $o' +
            'wner --padFileNamesWithZeroes '
          '$padFileNamesWithZeroes'
          
            '--imageType $imageType --doFilter false --fillWithNoise false --' +
            'baseDataUrl $baseDataURL --format $fmt --project $proj'
          '${z_batch[$i]}'
          '--bounds $bounds"'
          '    fi'
          '    eval nice -n $job_niceness java $java_args &'
          '    if (( $jobs >= $max_number_of_jobs ))'
          '    then'
          '      echo "Waiting for jobs to finish..."'
          '      wait'
          '      jobs=0'
          '    fi'
          'done'
          ''
          '#Wait for the jobs to finish..'
          'FAIL=0'
          'for job in `jobs -p`'
          'do'
          'echo $job'
          '    wait $job || let "FAIL+=1"'
          'done'
          ''
          'if [ "$create_tiff_stack"  == "true" ]; then'
          '  #Create a tiff stack here'
          
            '  stackFileName=$rootOutPutFolder/$customFolder/$stack"_stack.ti' +
            'ff"'
          '  echo "Creating stack file: "$stackFileName >> $info'
          ''
          '  #Empty outpurfile'
          '  > $stackFileName'
          ''
          '  for file in $rootOutPutFolder/$customFolder/$stack/*.tiff; do'
          #9'echo $file >> $info'
          #9'nice -n $job_niceness tiffcp -a $file $stackFileName'
          '  done'
          ''
          '  if [ "$delete_individual_tiffs"  == "true" ]; then'
          
            '        for file in $rootOutPutFolder/$customFolder/$stack/*.tif' +
            'f; do'
          '                echo "Removing file: $file" >> $info'
          '                rm $file'
          '          done'
          '  fi'
          'fi'
          ''
          ''
          'if [ "$FAIL" == "0" ];'
          'then'
          
            'echo "===============  FINISHED STACK CREATION SCRIPT ==========' +
            '===="'
          'else'
          'echo "FAIL! ($FAIL)"'
          'fi'
          'echo "mxplutx"'
          'echo "This job ended on: "`date` >> $info')
        ReadOnly = True
        TabOrder = 2
        Visible = False
        WordWrap = False
      end
      object MultiStackCreationGB: TGroupBox
        Left = 0
        Top = 329
        Width = 431
        Height = 318
        Align = alClient
        Caption = 'Select Stacks'
        TabOrder = 3
        object StacksForProjectCB: TCheckListBox
          AlignWithMargins = True
          Left = 2
          Top = 76
          Width = 424
          Height = 237
          Margins.Left = 0
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
        end
        object GroupBox3: TGroupBox
          Left = 2
          Top = 15
          Width = 427
          Height = 58
          Align = alTop
          Caption = 'Filters'
          TabOrder = 1
          object CustomFilterCB: TPropertyCheckBox
            Left = 13
            Top = 24
            Width = 80
            Height = 17
            Caption = 'Custom'
            TabOrder = 0
          end
          object CustomFilterE: TEdit
            Left = 83
            Top = 24
            Width = 121
            Height = 21
            TabOrder = 1
            Text = 'ALI'
          end
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 647
        Width = 431
        Height = 187
        Align = alBottom
        TabOrder = 4
        object JobCreationGB: TGroupBox
          Left = 1
          Top = 1
          Width = 429
          Height = 185
          Align = alClient
          Caption = 'Server Job Creation'
          TabOrder = 0
          DesignSize = (
            429
            185)
          object ZBatchSizeE: TIntegerLabeledEdit
            Left = 16
            Top = 32
            Width = 105
            Height = 21
            EditLabel.Width = 58
            EditLabel.Height = 13
            EditLabel.Caption = 'Z Batch Size'
            TabOrder = 0
            Text = '10'
            Value = 10
          end
          object MaxNumberOfRemoteJobsE: TIntegerLabeledEdit
            Left = 16
            Top = 76
            Width = 105
            Height = 21
            EditLabel.Width = 104
            EditLabel.Height = 13
            EditLabel.Caption = 'Number of jobs (max)'
            TabOrder = 1
            Text = '10'
            Value = 10
          end
          object NicenessE: TIntegerLabeledEdit
            Left = 16
            Top = 120
            Width = 97
            Height = 21
            Hint = '-20 is highest priority and 19 is lowest priority'
            EditLabel.Width = 99
            EditLabel.Height = 13
            EditLabel.Caption = 'Niceness (-20 -> 19)'
            TabOrder = 2
            Text = '0'
          end
          object Run: TButton
            Left = 296
            Top = 40
            Width = 119
            Height = 129
            Anchors = [akTop, akRight]
            Caption = 'Run'
            TabOrder = 3
          end
        end
      end
    end
    object TabSheet9: TTabSheet
      Caption = 'Settings'
      ImageIndex = 3
      object GroupBox4: TGroupBox
        Left = 0
        Top = 70
        Width = 431
        Height = 179
        Align = alTop
        Caption = 'Render Service Settings'
        TabOrder = 0
        DesignSize = (
          431
          179)
        object BaseURLE: TSTDStringLabeledEdit
          Left = 13
          Top = 42
          Width = 328
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          EditLabel.Width = 45
          EditLabel.Height = 13
          EditLabel.Caption = 'Base URL'
          TabOrder = 0
          Text = 'http://localhost'
          Value = 'http://localhost'
        end
        object TestRenderServiceBtn: TButton
          Left = 347
          Top = 40
          Width = 75
          Height = 25
          Anchors = [akTop, akRight]
          Caption = 'Test'
          TabOrder = 1
        end
        object maxTileSpecsToRenderE: TIntegerLabeledEdit
          Left = 16
          Top = 144
          Width = 121
          Height = 21
          EditLabel.Width = 121
          EditLabel.Height = 13
          EditLabel.Caption = 'Max # of Tiles To Render'
          TabOrder = 2
          Text = '150'
          Value = 150
        end
        object RenderPort: TIntegerLabeledEdit
          Left = 16
          Top = 88
          Width = 121
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 13
          EditLabel.Caption = 'RenderPort'
          TabOrder = 3
          Text = '80'
          Value = 80
        end
      end
      object TestSSHGB: TGroupBox
        Left = 0
        Top = 0
        Width = 431
        Height = 70
        Align = alTop
        Caption = 'Remote Command'
        TabOrder = 1
        DesignSize = (
          431
          70)
        object CMDButton: TButton
          Left = 391
          Top = 24
          Width = 27
          Height = 25
          Anchors = [akTop, akRight]
          Caption = '->'
          TabOrder = 0
        end
        object mCMD: TEdit
          Left = 16
          Top = 26
          Width = 369
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 1
          Text = 'ls'
        end
      end
      inline TSSHFrame1: TSSHFrame
        Left = 0
        Top = 249
        Width = 431
        Height = 160
        Align = alTop
        TabOrder = 2
        ExplicitTop = 249
        ExplicitWidth = 431
        ExplicitHeight = 160
      end
    end
  end
  object ZsPopUpMenu: TPopupMenu
    Left = 448
    Top = 104
    object Checkrange1: TMenuItem
      Caption = 'Select/Unselect Z'#39's'
    end
    object CheckAll1: TMenuItem
      Caption = 'Check All'
    end
    object UncheckAll1: TMenuItem
      Caption = 'Uncheck All'
    end
    object CopyValidZs1: TMenuItem
      Caption = 'Copy Numbers'
    end
    object CreateTiffStack1: TMenuItem
    end
  end
  object StacksPopupMenu: TPopupMenu
    Left = 431
    Top = 444
    object CreateMaxIntensityProjection1: TMenuItem
    end
  end
  object CreateCacheTimer: TTimer
    Interval = 150
    Left = 48
    Top = 440
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
    Left = 24
    Top = 728
  end
end
