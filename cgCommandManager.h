// cgCommandManager.h: interface for the cgCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGCOMMANDMANAGER_H__B8FE4F6C_16FF_4092_A9C4_976DD8F06484__INCLUDED_)
#define AFX_CGCOMMANDMANAGER_H__B8FE4F6C_16FF_4092_A9C4_976DD8F06484__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cgObject.h"
#include <vector> //容器
using namespace std;

enum CommandType
{
	NEW,DELE,MOVE,COLORMODY,FILLCOLORMODY
};

class cgCommand
{
public:
	cgObject* pObj;

	CommandType commandType;//0:生成1:删除2:移动3:修改颜色4:修改填充颜色.。。

	float dx;
	float dy;
	
	float cR;
	float cG;
	float cb;
};

class cgCommandManager  
{
public:
	cgCommandManager();
	virtual ~cgCommandManager();

	void AddUndo(cgCommand c);
	void AddRedo(cgCommand c);

	void Undo(vector<cgObject*>& list);
	void Redo(vector<cgObject*>& list);

	BOOL IsUndoEmpty(){return !m_undo.size();}
	BOOL IsRedoEmpty(){return !m_redo.size();}

	void ClearRedo();
private:
	vector<cgCommand> m_undo;
	vector<cgCommand> m_redo;
};

#endif // !defined(AFX_CGCOMMANDMANAGER_H__B8FE4F6C_16FF_4092_A9C4_976DD8F06484__INCLUDED_)
