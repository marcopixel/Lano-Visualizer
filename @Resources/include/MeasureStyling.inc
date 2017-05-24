[MeasureSetDynamicColors]
Measure=Calc
Formula=#EnableDynamicColors#
IfBelowValue=1
IfBelowAction=[!DisableMeasure MeasureGetCoverColor][!DisableMeasure MeasureCoverColor]
IfEqualValue=1
IfEqualAction=[!EnableMeasure MeasureGetCoverColor][!EnableMeasure MeasureCoverColor]
IfAboveValue=1
IfAboveAction=[!EnableMeasure MeasureGetCoverColor][!EnableMeasure MeasureCoverColor]
UpdateDivider=-1

[MeasureClipSongInformation]
Measure=Calc
Formula=#ClipSongInformation#
IfEqualValue=1
IfEqualAction=[!SetOption MeterTrack W "((#BarWidth#+#BarGap#)*(#BarCount#)*#ScaleVisualizer#)-[MeterArtist:W]"]
UpdateDivider=-1

[MeasureSetMediaPlayer]
Measure=String
String=#PlayerName#
IfMatch=Spotify
IfMatchAction=[!WriteKeyValue Variables MPMode Spotify "#@#variables.ini"]
IfMatch2=GPMDP
IfMatchAction2=[!WriteKeyValue Variables MPMode GPMDP "#@#variables.ini"]
IfNotMatchAction=[!WriteKeyValue Variables MPMode NowPlaying "#@#variables.ini"]
UpdateDivider=-1

[MeasureStaticColor]
Measure=String
String=#Color#
UpdateDivider=-1

[MeasureStaticColorText]
Measure=String
String=#TextColor#
UpdateDivider=-1

[MeasureGetCoverColor]
Measure=Plugin
Plugin=Chameleon
Type=File
Path=[MeasureCover]

[MeasureCoverColor]
Measure=Plugin
Plugin=Chameleon
Parent=MeasureGetCoverColor
Format=Dec
Color=Background1
Substitute="":"#Color#"
OnChangeAction=[!UpdateMeasure "CalcColors"]

[CalcColors]
Measure=Calc
IfConditionMode=1
IfCondition= (#EnableDynamicColors# = 0) && (#DisableDynamicFontColors# = 1)
IfTrueAction=[!SetVariable Color "[MeasureStaticColor]"]
IfCondition2= (#EnableDynamicColors# = 1) && (#DisableDynamicFontColors# = 1)
IfTrueAction2=[!SetVariable Color "[MeasureCoverColor]"]
IfCondition3= (#EnableDynamicColors# = 0) && (#DisableDynamicFontColors# = 0)
IfTrueAction3=[!SetVariable Color "[MeasureStaticColor]"][!SetVariable TextColor "[MeasureStaticColor]"]
IfCondition4= (#EnableDynamicColors# = 1) && (#DisableDynamicFontColors# = 0)
IfTrueAction4=[!SetVariable Color "[MeasureCoverColor]"][!SetVariable TextColor "[MeasureCoverColor]"]
UpdateDivider=-1
