typedef struct _PTE_HIERARCHY
{
	uintptr_t PageTableEntry;
	uintptr_t PageDirectoryEntry;
	uintptr_t PageDirectoryPointerTableEntry;
	uintptr_t PageMapLevel4Entry;
}PTE_HIERARCHY, * PPTE_HIERARCHY;

unsigned __int64 __fastcall MiVaToPfn(unsigned __int64 BaseAddress) {
    PTE_HIERARCHY PteHierarchy;
    __int64 v2; // rdx
    __int64 v3; // r9
    __int64 v4; // rax
    unsigned __int64 v5; // r9
    int v6; // r10d
    __int64 v7; // rcx
    unsigned __int64 v8; // rbx
    __int16 v9; // ax
    __int64 v10; // rax
    __int64 v14; // [rsp+58h] [rbp+10h] BYREF

    memset(PteHierarchy, 0x00, sizeof(PTE_HIERARCHY));
    MiFillPteHierarchy(BaseAddress, &PteHierarchy);

    v3 = 4i64;
    do {
        // first gets pml4e, ptpte, pde then pte
        v4 = MI_READ_PTE_LOCK_FREE(*(_QWORD *)&PteHierarchy[v3]); 
        v14 = v4;
    } while ( v3 && (v4 & 0x80u) == 0i64 ); // break if large page present ?

    // if large page is present, v14 will be contents of the page entry
    v5 = ((unsigned __int64)sub_14006E5E0(&v14, v2) >> 12) & 0xFFFFFFFFFi64;

    if ( v6 ) {
        v7 = 1i64;
        v8 = BaseAddress >> 12;
        
        do {
            v9 = v8;
            v8 >>= 9;
            v10 = v7 * (v9 & 0x1FF);
            v7 <<= 9;
            v5 += v10;
            --v6;
        } while ( v6 );
    }

    return v5;
}


__int64 __fastcall MI_READ_PTE_LOCK_FREE(unsigned __int64 a1)
{
  __int64 result; // rax
  __int64 v2; // rdx
  __int64 v3; // r8
  __int64 v4; // rcx

  result = *(_QWORD *)a1;
  if ( a1 >= 0xFFFFF6FB7DBED000ui64
    && a1 <= 0xFFFFF6FB7DBED7F8ui64
    && (dword_140573380 & 0xC00000) != 0
    && *(_BYTE *)(*(_QWORD *)(__readgsqword(0x188u) + 0xB8) + 0x288i64) != 1
    && (result & 1) != 0
    && ((result & 0x20) == 0 || (result & 0x42) == 0) )
  {
    v2 = *(_QWORD *)(*(_QWORD *)(__readgsqword(0x188u) + 0xB8) + 0x608i64);
    if ( v2 )
    {
      v3 = result | 0x20;
      v4 = *(_QWORD *)(v2 + 8 * ((a1 >> 3) & 0x1FF));
      if ( (v4 & 0x20) == 0 )
        v3 = result;
      result = v3;
      if ( (v4 & 0x42) != 0 )
        return v3 | 0x42;
    }
  }
  return result;
}