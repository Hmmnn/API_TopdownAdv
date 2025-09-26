#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
    Release();
}

void CBmpMgr::InsertBmp(const TCHAR* _pKey, const TCHAR* _pFilePath)
{
    auto iter = find_if(m_BmpMap.begin(), m_BmpMap.end(), tagFinder(_pKey));

    if (iter != m_BmpMap.end())
        return;

    CMyBmp* Temp = new CMyBmp;
    Temp->LoadBmp(_pFilePath);

    m_BmpMap.insert({ _pKey, Temp });
}

HDC CBmpMgr::FindBmp(const TCHAR* _pKey)
{
    auto iter = find_if(m_BmpMap.begin(), m_BmpMap.end(), tagFinder(_pKey));

    if (iter == m_BmpMap.end())
        return nullptr;

    return (*iter).second->GetMemDC();
}

void CBmpMgr::Release()
{
    for_each(m_BmpMap.begin(), m_BmpMap.end(), [](auto& pair) 
    {
        if (pair.second)
        {
            delete pair.second;
            pair.second = nullptr;
        }
    });

    m_BmpMap.clear();
}
