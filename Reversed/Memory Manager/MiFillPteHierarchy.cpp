struct typedef struct _PML4E
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
static_assert(sizeof(PML4E) == sizeof(PVOID), "Size mismatch, only 64-bit supported.");

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
static_assert(sizeof(PDPTE) == sizeof(PVOID), "Size mismatch, only 64-bit supported.");

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
static_assert(sizeof(PDE) == sizeof(PVOID), "Size mismatch, only 64-bit supported.");

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
static_assert(sizeof(PTE) == sizeof(PVOID), "Size mismatch, only 64-bit supported.");

typedef struct _PTE_HIERARCHY
{
	PPTE PageTableEntry;
	PPDE PageDirectoryEntry;
	PPDPTE PageDirectoryPointerTableEntry;
	PPML4E PageMapLevel4Entry;
}PTE_HIERARCHY, * PPTE_HIERARCHY;

uintptr_t __fastcall MiFillPteHierarchy(PVOID BaseAddress, PPTE_HIERARCHY PteHierarchy) {
  PPTE _pte; 
  PPDE _pde; 
  uintptr_t Result; 
  PPDPTE _pdpte;
  PPML4E _pml4e;

  _pte = (PPTE)((((uintptr_t)BaseAddress >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64);
  PteHierarchy->PageTableEntry = _pte;

  _pde = (PPDE)((((uintptr_t)_pte >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64);
  PteHierarchy->PageDirectoryEntry = _pde;

  Result = 0xFFFFF68000000000ui64;

  _pdpte = (PPDPTE)((((uintptr_t)_pde >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64);
  PteHierarchy->PageDirectoryPointerTableEntry = _pdpte;

  _pml4e = (PPML4E)((((uintptr_t)_pdpte >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64);
  PteHierarchy->PageMapLevel4Entry = _pml4e;
  
  return Result;
}