#pragma once

#include "CADShape.h"
#include "GYSingleInstanceMacro.h"

class CCADStorage
{
public:
  SINGLE_INSTANCE(CCADStorage)

  CList<CCADShape *, CCADShape *> m_lstShapes;  //�������е��Ѵ�����״

private:
  CCADStorage();
  virtual ~CCADStorage();
};

