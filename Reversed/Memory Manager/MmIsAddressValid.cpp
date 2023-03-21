
typedef struct _PTE_HIERARCHY
{
    /*PTE PageTableEntry;
    PDE PageDirectoryEntry;
    PDPTE PageDirectoryPointerTableEntry;
	PML4E PageMapLevel4Entry;*/
    __int64 PageTableEntry;
    __int64 PageDirectoryEntry;
    __int64 PageDirectoryPointerTableEntry;
	__int64 PageMapLevel4Entry;
}PTE_HIERARCHY, * PPTE_HIERARCHY;

char __fastcall MmIsAddressValidEx(unsigned __int64 VirtualAddress);

__int64 MmIsAddressValid(PVOID BaseAddress)
{
  return MmIsAddressValidEx((unsigned __int64)BaseAddress);
}


char __fastcall MmIsAddressValidEx(unsigned __int64 VirtualAddress){
    

    __int64 index; // rdx
    unsigned __int64 v3; // r9
    __int64 v4; // rcx
    __int64 v6; // rax
    __int64 v7; // rax
    char v8; // r9
    __int64 v9; // [rsp+0h] [rbp-30h]
    __int64 _pml4eAddress; // [rsp+8h] [rbp-28h]
    __int64 _pdpteAddress; // [rsp+10h] [rbp-20h]
    __int64 _pdeAddress; // [rsp+18h] [rbp-18h]
    __int64 _pteAddress; // [rsp+20h] [rbp-10h]
    __int64 PteHierarchy[4];

    if (((VirtualAddress >> 0x2f) + 1) <= 1){
    
        // for detailed implementation, see MiFillPteHierarchy.cpp
        _pml4eAddress = ((VirtualAddress >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
        _pdpteAddress = (((unsigned __int64)_pml4eAddress >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
        _pdeAddress   = (((unsigned __int64)_pdpteAddress >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
        _pteAddress   = (((unsigned __int64)_pdeAddress >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;


        PteHierarchy[3] = _pml4eAddress;
        PteHierarchy[2] = _pdpteAddress;
        PteHierarchy[1] = _pdeAddress;
        PteHierarchy[0] = _pteAddress;

        index = 4i64;

        while (1){
            v3 = PteHierarchy[index--];
            index -= 1;
            v4 = *(__int64*)v3;

            if ( v3 >= 0xFFFFF6FB7DBED000ui64
                && v3 <= 0xFFFFF6FB7DBED7F8ui64
                && (MiFlags & 0xC00000) != 0
                && *(_BYTE *)(*(_QWORD *)(__readgsqword(0x188u) + 184) + 648i64) != 1 /*AddressPolicy*/) {

                    if ( (v4 & 1) == 0 )
                        return 0;

                    if ( (v4 & 0x20) == 0 || (v4 & 0x42) == 0 ) ) {
                        v6 = *(_QWORD *)(*(_QWORD *)(__readgsqword(0x188u) + 184) + 1544i64);
          
                    if ( v6 ) {
                        v7 = *(_QWORD *)(v6 + 8 * ((v3 >> 3) & 0x1FF));
                        v8 = v4 | 0x20;
                        if ( (v7 & 0x20) == 0 )
                            v8 = v4;

                        v4 = v8;

                        if ( (v7 & 0x42) != 0 )
                            v4 = v8 | 0x42;
                    }
                }

            }

            if ((v4 & 1) == 0) // Page Present?? == false
                return 0;

            if ( (v4 & 0x80u) != 0i64 )  // # large page enabled
                break;

            if ( index == 0x0 ) // already got to page pte
                return 1;
        }

        if ( (VirtualAddress < 0xFFFFF68000000000ui64) || (VirtualAddress > 0xFFFFF6FFFFFFFFFFui64) )
            return 1;
    }

    return 0;
}