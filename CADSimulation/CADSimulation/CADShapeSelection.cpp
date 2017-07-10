#include "stdafx.h"
#include "CADShapeSelection.h"

#include "CADStorage.h"
#include "CADSimulation.h"
#include "CADSimulationView.h"


CCADShapeSelection::CCADShapeSelection()
{
  m_bIsSelectionDone = false;
}


CCADShapeSelection::~CCADShapeSelection()
{
}

CDC * CCADShapeSelection::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);
  //������
  CPen pen(PS_DASH, 1, RGB(0, 0, 0));
  CPen *pPenOld = pMemDC->SelectObject(&pen);

  CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
  CBrush *pBrushOld = pMemDC->SelectObject(pBrush);

  if (m_bIsSelectionDone == false)
  {
    pMemDC->Rectangle(m_objBeginPoint.x, m_objBeginPoint.y,
      m_objEndPoint.x, m_objEndPoint.y);
  }

  pMemDC->SelectObject(pPenOld);
  pMemDC->SelectObject(pBrushOld);

  //������ǻ������Ļ����Ͱ��Լ�
  if (m_bIsDrawingBackground == false)
  {
    CRect rcClient;
    GetClientRect(hWnd, &rcClient);
    pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pMemDC, 0, 0, SRCCOPY);
  }

  return 0;
}

int CCADShapeSelection::SaveThisShape(CPoint & objPoint)
{
  //�������ͼ�Σ����ǽ����������飨Ѱ�ұ��û��ó���ͼ�Σ�
  FindSelectedShapes();

  return 0;
}

extern CCADSimulationApp theApp;

int CCADShapeSelection::FindSelectedShapes()
{
  //��������,����ÿһ�������ͼ��
  CCADStorage *pStorage = GET_SINGLE(CCADStorage);

  POSITION pos = (pStorage->m_lstShapes).GetHeadPosition();
  while (pos)
  {
    CCADShape * pShape = (pStorage->m_lstShapes).GetNext(pos);

    if (pShape->IsSelected(&CRect(m_objBeginPoint, m_objEndPoint)) == TRUE)
    {
      theApp.m_lstSelectedShapes.AddTail(pShape);
      pShape->WhenSelected();
    }
  }

  m_bIsSelectionDone = true;

  return 0;
}
