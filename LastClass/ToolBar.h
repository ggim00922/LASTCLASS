//ToolBar.h

#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <afxwin.h>
typedef signed long int  Long;
class ToolBarProcess;
class LastClass;
class ClassDiagramForm;
class ToolBar {
public:
	ToolBar();
	ToolBar(const ToolBar& source);
	 ~ToolBar();
	void MakeToolBar(HWND hWndParent);
	void MakeAnotherToolBar(HWND hWndParent);
	void ButtonSelected(UINT parm_control_id,LastClass *lastClass,ClassDiagramForm *classDiagramForm,CDC *cdc);
};

#endif // _ToolBar_H
