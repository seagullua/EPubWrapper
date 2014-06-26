; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=ePUB to APK
AppVersion=1.0
DefaultDirName={pf}\ePUB to APK
DefaultGroupName=ePUB to APK
Compression=lzma2
SolidCompression=yes
OutputDir=Output
OutputBaseFilename=ePUB to APK Setup

[Languages]
Name: uk; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Files]
Source: "..\external\*"; Excludes: ".git"; DestDir: "{app}\external";  Flags: ignoreversion recursesubdirs
Source: "prebuilt\*"; Excludes: ".git"; DestDir: "{app}";  Flags: ignoreversion recursesubdirs
Source: "..\EpubWrapperAndroid\bin\release\ePUB To APK.exe" ; DestDir: "{app}"

[Icons]
Name: "{group}\ePUB to APK"; Filename: "{app}\ePUB to APK.exe"
Name: "{commondesktop}\ePUB to APK"; Filename: "{app}\ePUB to APK.exe"

[Run]
Filename: "{app}\ePUB to APK.exe"; Parameters: "icon"