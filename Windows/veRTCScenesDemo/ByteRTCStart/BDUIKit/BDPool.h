//
//  BDPool.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once


class BDPool
{
public:
    BDPool(unsigned int ulUnitNum = 180, unsigned int ulUnitSize = 24, unsigned int rwx = PAGE_EXECUTE_READWRITE)
    {
        m_pMemBlock = NULL;
        m_pAllocatedMemBlock = NULL;
        m_pFreeMemBlock = NULL;
        m_ulBlockSize = (ulUnitNum * (ulUnitSize + sizeof(struct _Unit)));
        m_ulUnitSize = ulUnitSize;

        m_pMemBlock = ::VirtualAlloc(NULL, m_ulBlockSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        if (NULL != m_pMemBlock)
        {
            for (unsigned int i = 0; i < ulUnitNum; i++)
            {
                struct _Unit* pCurUnit = (struct _Unit*)((char*)m_pMemBlock + i * (ulUnitSize + sizeof(struct _Unit)));

                pCurUnit->pPrev = NULL;
                pCurUnit->pNext = m_pFreeMemBlock;

                if (NULL != m_pFreeMemBlock)
                {
                    m_pFreeMemBlock->pPrev = pCurUnit;
                }
                m_pFreeMemBlock = pCurUnit;
            }
        }
    }

    ~BDPool()
    {
        ::VirtualFree(m_pMemBlock, 0, MEM_RELEASE);
    }

    void* Alloc(unsigned int ulSize, bool bUseMemPool = true)
    {
        if (ulSize > m_ulUnitSize || false == bUseMemPool ||
            NULL == m_pMemBlock || NULL == m_pFreeMemBlock)
        {
            return malloc(ulSize);
        }

        //Now FreeList is not empty
        struct _Unit* pCurUnit = m_pFreeMemBlock;

        m_pFreeMemBlock = pCurUnit->pNext;
        if (NULL != m_pFreeMemBlock)
        {
            m_pFreeMemBlock->pPrev = NULL;
        }

        pCurUnit->pNext = m_pAllocatedMemBlock;

        if (NULL != m_pAllocatedMemBlock)
        {
            m_pAllocatedMemBlock->pPrev = pCurUnit;
        }
        m_pAllocatedMemBlock = pCurUnit;

        return (void*)((char*)pCurUnit + sizeof(struct _Unit));
    }

    void Free(void* p)
    {
        if (m_pMemBlock < p && p < (void*)((char*)m_pMemBlock + m_ulBlockSize))
        {
            struct _Unit* pCurUnit = (struct _Unit*)((char*)p - sizeof(struct _Unit));

            m_pAllocatedMemBlock = pCurUnit->pNext;
            if (NULL != m_pAllocatedMemBlock)
            {
                m_pAllocatedMemBlock->pPrev = NULL;
            }

            pCurUnit->pNext = m_pFreeMemBlock;
            if (NULL != m_pFreeMemBlock)
            {
                m_pFreeMemBlock->pPrev = pCurUnit;
            }

            m_pFreeMemBlock = pCurUnit;
        }
        else
        {
            free(p);
        }
    }

    bool InPool(void* p)
    {
        if (m_pMemBlock < p && p < (void*)((char*)m_pMemBlock + m_ulBlockSize))
        {
            return true;
        }
        return false;
    }

private:
    struct _Unit
    {
        struct _Unit* pPrev, * pNext;
    };

    struct _Unit* m_pAllocatedMemBlock;
    struct _Unit* m_pFreeMemBlock;

public:
    void* m_pMemBlock;
    unsigned int m_ulUnitSize;
    unsigned int m_ulBlockSize;
};
