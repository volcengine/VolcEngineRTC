//
//  BDThunk.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include "BDBase.h"
#include "BDPool.h"

extern BDPool pool;

#if defined(_M_IX86)

#pragma pack(push,1)
struct _bdthunk    //13
{
    DWORD  m_mov;
    DWORD  m_this;
    UCHAR  m_jmp;
    DWORD  m_relproc;

    bool Init(DWORD_PTR proc, void* pThis)
    {
        m_mov = 0x042444C7;
        m_this = PtrToUlong(pThis);
        m_jmp = 0xe9;
        m_relproc = DWORD((long long)proc - ((long long)this+sizeof(_bdthunk)));
        FlushInstructionCache(GetCurrentProcess(), this, sizeof(_bdthunk));            
        return true;
    }

    void* GetCodeAddress()
    {
        return this;
    }

    void* operator new(size_t size)
    {
        return pool.Alloc(16);
    }

    void operator delete(void* pThunk)
    {
        pool.Free(pThunk);
    }
};
#pragma pack(pop)

#else
#pragma pack(push,2)
struct _bdthunk    //22
{
    WORD RcxMov;
    unsigned long long RcxImm;
    WORD  RaxMov;
    unsigned long long RaxImm;
    WORD RaxJmp;
    
    bool Init(DWORD_PTR proc, void *pThis)
    {
        RcxMov = 0xb948;
        RcxImm = (ULONG64)pThis;
        RaxMov = 0xb848;
        RaxImm = (ULONG64)proc;
        RaxJmp = 0xe0ff;
        FlushInstructionCache(GetCurrentProcess(), this, sizeof(_bdthunk));
        return true;
    }
        
    void* GetCodeAddress()
    {
        return this;
    }
    
    void* operator new(size_t size)
    {
        return pool.Alloc(24);
    }
    
    void operator delete(void* pThunk)
    {
        pool.Free(pThunk);
    }
};
#pragma pack(pop)

#endif


// BDThunk
#pragma pack(push,8)
class BDThunk
{
public:
    _bdthunk *pThunk;

    BDThunk() 
    {
        pThunk = NULL;
    }

    ~BDThunk() 
    {
        if (pThunk)
        {
            delete pThunk;
        }
    }

    bool Init(DWORD_PTR proc, void *pThis)
    {
        if (pThunk == NULL)
        {
            pThunk = new _bdthunk;
            if (pThunk == NULL)
            {
                return false;
            }
        }
        return pThunk->Init(proc, pThis);
    }

    void* GetCodeAddress()
    {
        return pThunk->GetCodeAddress();
    }
};
#pragma pack(pop)
