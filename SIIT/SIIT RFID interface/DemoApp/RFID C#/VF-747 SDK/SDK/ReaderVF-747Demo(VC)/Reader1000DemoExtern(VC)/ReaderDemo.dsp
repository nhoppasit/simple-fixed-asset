# Microsoft Developer Studio Project File - Name="ReaderDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ReaderDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ReaderDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ReaderDemo.mak" CFG="ReaderDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ReaderDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ReaderDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ReaderDemo - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"ReaderDemo.exe"

!ELSEIF  "$(CFG)" == "ReaderDemo - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".//INC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"nafxcw.lib" /nodefaultlib:"libc.lib" /out:"ReaderDemo.exe" /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "ReaderDemo - Win32 Release"
# Name "ReaderDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "INC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\INC\containers.h
# End Source File
# Begin Source File

SOURCE=.\INC\EnumSerial.cpp
# End Source File
# Begin Source File

SOURCE=.\INC\EnumSerial.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ConnectReader.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBPAA9.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRubbish.cpp
# End Source File
# Begin Source File

SOURCE=.\EPCC1G2Test.cpp
# End Source File
# Begin Source File

SOURCE=.\ISO6BTest.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Progress.cpp
# End Source File
# Begin Source File

SOURCE=.\ReaderDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\ReaderDemo.rc
# End Source File
# Begin Source File

SOURCE=.\ReaderDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReaderDParam.cpp
# End Source File
# Begin Source File

SOURCE=.\ReaderModeS.cpp
# End Source File
# Begin Source File

SOURCE=.\ReaderParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\ReaderParameterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TK900Test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ConnectReader.h
# End Source File
# Begin Source File

SOURCE=.\DlgBPAA9.h
# End Source File
# Begin Source File

SOURCE=.\DlgRubbish.h
# End Source File
# Begin Source File

SOURCE=.\EPCC1G2Test.h
# End Source File
# Begin Source File

SOURCE=.\ISO6BTest.h
# End Source File
# Begin Source File

SOURCE=.\OutputTest.h
# End Source File
# Begin Source File

SOURCE=.\Progress.h
# End Source File
# Begin Source File

SOURCE=.\ReaderDemo.h
# End Source File
# Begin Source File

SOURCE=.\ReaderDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReaderDParam.h
# End Source File
# Begin Source File

SOURCE=.\ReaderModeS.h
# End Source File
# Begin Source File

SOURCE=.\ReaderParameter.h
# End Source File
# Begin Source File

SOURCE=.\ReaderParameterDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TK900Test.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\ReaderDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\ReaderDemo.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\R1100Chinese.ini
# End Source File
# Begin Source File

SOURCE=.\res\R1100English.ini
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
