================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : MFCSingleToolBar Project Overview
===============================================================================

The application wizard has created this MFCSingleToolBar application for
you.  This application not only demonstrates the basics of using the Microsoft
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your MFCSingleToolBar application.

MFCSingleToolBar.vcxproj
    This is the main project file for VC++ projects generated using an application wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    application wizard.

MFCSingleToolBar.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

MFCSingleToolBar.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CMFCSingleToolBarApp application class.

MFCSingleToolBar.cpp
    This is the main application source file that contains the application
    class CMFCSingleToolBarApp.

MFCSingleToolBar.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\MFCSingleToolBar.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file MFCSingleToolBar.rc.

res\MFCSingleToolBar.rc2
    This file contains resources that are not edited by Microsoft
    Visual C++. You should place all resources not editable by
    the resource editor in this file.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    Windows Explorer Style: The project will include a Windows Explorer-like
    interface, with two frames.

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

LeftView.h, LeftView.cpp
    These files contain the left frame class CLeftView, which is derived from
    CTreeView.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in MFCSingleToolBar.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

The application wizard creates one document type and one view:

MFCSingleToolBarDoc.h, MFCSingleToolBarDoc.cpp - the document
    These files contain your CMFCSingleToolBarDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CMFCSingleToolBarDoc::Serialize).

MFCSingleToolBarView.h, MFCSingleToolBarView.cpp - the view of the document
    These files contain your CMFCSingleToolBarView class.
    CMFCSingleToolBarView objects are used to view CMFCSingleToolBarDoc objects.





/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named MFCSingleToolBar.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need
to redistribute the MFC DLLs. If your application is in a language
other than the operating system's locale, you will also have to
redistribute the corresponding localized resources MFC100XXX.DLL.
For more information on both of these topics, please see the section on
redistributing Visual C++ applications in MSDN documentation.

/////////////////////////////////////////////////////////////////////////////
