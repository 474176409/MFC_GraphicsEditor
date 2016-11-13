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
		//�ͷ�ͼԪָ�룿
		//

		m_redo.erase(m_redo.begin());// ɾ��
	}
}

void cgCommandManager::Undo(vector<cgObject*>& list)
{
	if (!m_undo.size()) return;
	cgCommand c;

	int top = m_undo.size() - 1;
	c = m_undo[top];//ȡջ��
	m_undo.erase(m_undo.begin()+top);// ɾ��
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
	c = m_redo[top];//ȡջ��
	m_redo.erase(m_redo.begin()+top);// ɾ��
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
