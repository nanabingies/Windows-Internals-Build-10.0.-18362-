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

char __fastcall MmIsAddressValidEx(unsigned __int64 VirtualAddress);

__int64 MmIsAddressValid(void* BaseAddress)
{
  return MmIsAddressValidEx((unsigned __int64)BaseAddress);
}


char __fastcall MmIsAddressValidEx(unsigned __int64 VirtualAddress){
    PTE _pte; 
    PDE _pde;  
    PDPTE _pdpte;
    PML4E _pml4e;

    if (((VirtualAddress >> 0x2f) + 1) <= 1){

    }

    return 1;
}