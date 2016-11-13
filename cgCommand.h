// cgCommand.h: interface for the cgCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGCOMMAND_H__B62835C9_9955_4DE4_AD3F_4F6C3FB0FCB4__INCLUDED_)
#define AFX_CGCOMMAND_H__B62835C9_9955_4DE4_AD3F_4F6C3FB0FCB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"
#include <vector> //����
using namespace std;

enum CommandType
{
	NEW,DELE,MOVE,COLORMODY,FILLCOLORMODY
};

class cgCommand
{
public:
	cgObject* pObj;

	CommandType commandType;//0:����1:ɾ��2:�ƶ�3:�޸���ɫ4:�޸������ɫ.����

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
