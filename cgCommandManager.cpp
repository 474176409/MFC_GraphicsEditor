// cgCommandManager.cpp: implementation of the cgCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgCommandManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgCommandManager::cgCommandManager()
{

}

cgCommandManager::~cgCommandManager()
{

}

void cgCommandManager::AddUndo(cgCommand c)
{
	m_undo.push_back(c);
}

void cgCommandManager::AddRedo(cgCommand c)
{
	m_redo.push_back(c);;
}

void cgCommandManager::ClearRedo()
{
	while(m_redo.size())
	{
		cgCommand c = m_redo[0];
		//ÊÍ·ÅÍ¼ÔªÖ¸Õë£¿
		//

		m_redo.erase(m_redo.begin());// É¾³ý
	}
}

void cgCommandManager::Undo(vector<cgObject*>& list)
{
	if (!m_undo.size()) return;
	cgCommand c;

	int top = m_undo.size() - 1;
	c = m_undo[top];//È¡Õ»¶¥
	m_undo.erase(m_undo.begin()+top);// É¾³ý
	AddRedo(c);

	switch (c.commandType)
	{
	case DELE:
		c.pObj->SetStatus(Drawing);
		list.push_back(c.pObj);
		break;
	case NEW:
		for(int i=0; i<list.size(); i++)
		{
			if (list[i] == c.pObj)
			{
				list.erase(list.begin()+i);
				return;
			}
		}
		break;
	}
}
void cgCommandManager::Redo(vector<cgObject*>& list)
{
	if (!m_redo.size()) return;
	cgCommand c;

	int top = m_redo.size() - 1;
	c = m_redo[top];//È¡Õ»¶¥
	m_redo.erase(m_redo.begin()+top);// É¾³ý
	AddUndo(c);
	int i;

	switch (c.commandType)
	{
	case DELE:
		for(i=0; i<list.size(); i++)
		{
			if (list[i] == c.pObj)
			{
				list.erase(list.begin()+i);
				return;
			}
		}
		break;
	case NEW:
		c.pObj->SetStatus(Drawing);
		list.push_back(c.pObj);
		break;
	}
}
