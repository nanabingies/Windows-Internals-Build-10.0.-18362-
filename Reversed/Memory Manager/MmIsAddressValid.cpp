typedef struct _PML4E
{
	union
	{
		struct
		{
			ULONG64 Present : 1;             
			ULONG64 ReadWrite : 1;           
			ULONG64 UserSupervisor : 1;      
			ULONG64 PageWriteThrough : 1;    
			ULONG64 PageCacheDisable : 1;    
			ULONG64 Accessed : 1;            
			ULONG64 Ignored1 : 1;
			ULONG64 PageSize : 1;            
			ULONG64 Ignored2 : 4;
			ULONG64 PageFrameNumber : 36;    
			ULONG64 Reserved : 4;
			ULONG64 Ignored3 : 11;
			ULONG64 ExecuteDisable : 1;      
		};
		ULONG64 Value;
	};
} PML4E, * PPML4E;

typedef struct _PDPTE
{
	union
	{
		struct
		{
			ULONG64 Present : 1;              
			ULONG64 ReadWrite : 1;            
			ULONG64 UserSupervisor : 1;       
			ULONG64 PageWriteThrough : 1;     
			ULONG64 PageCacheDisable : 1;     
			ULONG64 Accessed : 1;             
			ULONG64 Ignored1 : 1;
			ULONG64 PageSize : 1;             
			ULONG64 Ignored2 : 4;
			ULONG64 PageFrameNumber : 36;     
			ULONG64 Reserved : 4;
			ULONG64 Ignored3 : 11;
			ULONG64 ExecuteDisable : 1;       
		};
		ULONG64 Value;
	};
} PDPTE, * PPDPTE;

typedef struct _PDE
{
	union
	{
		struct
		{
			ULONG64 Present : 1;             
			ULONG64 ReadWrite : 1;           
			ULONG64 UserSupervisor : 1;      
			ULONG64 PageWriteThrough : 1;    
			ULONG64 PageCacheDisable : 1;    
			ULONG64 Accessed : 1;            
			ULONG64 Ignored1 : 1;
			ULONG64 PageSize : 1;            
			ULONG64 Ignored2 : 4;
			ULONG64 PageFrameNumber : 36;    
			ULONG64 Reserved : 4;
			ULONG64 Ignored3 : 11;
			ULONG64 ExecuteDisable : 1;      
		};
		ULONG64 Value;
	};
} PDE, * PPDE;

typedef struct _PTE
{
	union
	{
		struct
		{
			ULONG64 Present : 1;             
			ULONG64 ReadWrite : 1;           
			ULONG64 UserSupervisor : 1;      
			ULONG64 PageWriteThrough : 1;    
			ULONG64 PageCacheDisable : 1;    
			ULONG64 Accessed : 1;            
			ULONG64 Dirty : 1;               
			ULONG64 PageAccessType : 1;      
			ULONG64 Global : 1;              
			ULONG64 Ignored2 : 3;
			ULONG64 PageFrameNumber : 36;    
			ULONG64 Reserved : 4;
			ULONG64 Ignored3 : 7;
			ULONG64 ProtectionKey : 4;       
			ULONG64 ExecuteDisable : 1;      
		};
		ULONG64 Value;
	};
} PTE, * PPTE;

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

__int64 MmIsAddressValid(void* BaseAddress)
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
    __int64 _pml4e; // [rsp+8h] [rbp-28h]
    __int64 _pdpte; // [rsp+10h] [rbp-20h]
    __int64 _pde; // [rsp+18h] [rbp-18h]
    __int64 _pte; // [rsp+20h] [rbp-10h]
    __int64 PteHierarchy[4];

    if (((VirtualAddress >> 0x2f) + 1) <= 1){
    
        _pml4e = ((VirtualAddress >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
        _pdpte = (((unsigned __int64)_pml4e >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
        _pde   = (((unsigned __int64)_pdpte >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
        _pte   = (((unsigned __int64)_pde >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;


        PteHierarchy[3] = _pml4e;
        PteHierarchy[2] = _pdpte;
        PteHierarchy[1] = _pde;
        PteHierarchy[0] = _pte;

        index = 4i64;

        while (1){
            v3 = PteHierarchy[index];
            index -= 1;
            v4 = *(__int64*)v3;

            if ( v3 >= 0xFFFFF6FB7DBED000ui64
                && v3 <= 0xFFFFF6FB7DBED7F8ui64
                && (MiFlags & 0xC00000) != 0
                && *(_BYTE *)(*(_QWORD *)(KeGetPcr()->Prcb __readgsqword(0x188u) + 184) + 648i64) != 1 )
        }
    }

    return 1;
}