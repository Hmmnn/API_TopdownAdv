#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
    ZeroMemory(m_KeyStates, sizeof(m_KeyStates));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::KeyDown(int _key)
{
    if ((GetAsyncKeyState(_key) & 0x8000) && !m_KeyStates[_key])
    {
        m_KeyStates[_key] = !m_KeyStates[_key];
        return true;
    }

    for (size_t i = 0; i < KEY_MAX; ++i)
    {
        if (!(GetAsyncKeyState(i) & 0x8000) && m_KeyStates[i])
            m_KeyStates[i] = !m_KeyStates[i];
    }

    return false;
}

bool CKeyMgr::KeyUp(int _key)
{
    if (!(GetAsyncKeyState(_key) & 0x8000) && m_KeyStates[_key])
    {
        m_KeyStates[_key] = !m_KeyStates[_key];
        return true;
    }

    for (size_t i = 0; i < KEY_MAX; ++i)
    {
        if ((GetAsyncKeyState(i) & 0x8000) && !m_KeyStates[i])
            m_KeyStates[i] = !m_KeyStates[i];
    }

    return false;
}

bool CKeyMgr::KeyPressing(int _key)
{
    if (GetAsyncKeyState(_key))
        return true;

    return false;
}
