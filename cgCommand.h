// cgCommand.h: interface for the cgCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGCOMMAND_H__B62835C9_9955_4DE4_AD3F_4F6C3FB0FCB4__INCLUDED_)
#define AFX_CGCOMMAND_H__B62835C9_9955_4DE4_AD3F_4F6C3FB0FCB4__INCLUDED_

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
	void AddUndo(cgCommand c);
	cgCommandManager();
	virtual ~cgCommandManager();
private:
	vector<cgCommand> m_undo;
	vector<cgCommand> m_redo;
};
#endif // !defined(AFX_CGCOMMAND_H__B62835C9_9955_4DE4_AD3F_4F6C3FB0FCB4__INCLUDED_)
