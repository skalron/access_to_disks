object IndexForm: TIndexForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1057#1080#1075#1085#1072#1090#1091#1088#1085#1099#1081' '#1087#1086#1080#1089#1082' PDF '#1080' BMP'
  ClientHeight = 439
  ClientWidth = 426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PrintLabel: TLabel
    Left = 24
    Top = 382
    Width = 225
    Height = 49
    AutoSize = False
    WordWrap = True
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 24
    Top = 167
    Width = 377
    Height = 209
    Header.AutoSizeIndex = -1
    Header.Font.Charset = DEFAULT_CHARSET
    Header.Font.Color = clWindowText
    Header.Font.Height = -11
    Header.Font.Name = 'Tahoma'
    Header.Font.Style = []
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowTreeLines, toThemeAware, toUseBlendedImages]
    OnGetText = VirtualStringTree1GetText
    Columns = <
      item
        Position = 0
        Width = 114
        WideText = #1053#1086#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072
      end
      item
        Position = 1
        Width = 144
        WideText = #1053#1072#1081#1076#1077#1085#1085#1072#1103' '#1089#1080#1075#1085#1072#1090#1091#1088#1072
      end
      item
        Position = 2
        Width = 108
        WideText = #1056#1072#1089#1096#1080#1088#1077#1085#1080#1077' '#1092#1072#1081#1083#1072
      end>
  end
  object EditPath: TEdit
    Left = 24
    Top = 32
    Width = 225
    Height = 21
    TabOrder = 1
    Text = '\\.\F:'
  end
  object LaunchButton: TButton
    Left = 25
    Top = 72
    Width = 137
    Height = 33
    Caption = #1047#1072#1087#1091#1089#1082
    TabOrder = 2
    OnClick = LaunchButtonClick
  end
  object StopButton: TButton
    Left = 192
    Top = 72
    Width = 137
    Height = 33
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1087#1086#1080#1089#1082
    TabOrder = 3
    OnClick = StopButtonClick
  end
  object ProgressBar: TProgressBar
    Left = 24
    Top = 121
    Width = 377
    Height = 24
    TabOrder = 4
  end
  object ClearButton: TButton
    Left = 263
    Top = 392
    Width = 138
    Height = 33
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 5
    OnClick = ClearButtonClick
  end
end
