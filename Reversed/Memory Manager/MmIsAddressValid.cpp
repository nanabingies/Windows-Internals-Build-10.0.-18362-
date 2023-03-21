char __fastcall MmIsAddressValidEx(unsigned __int64 VirtualAddress);

__int64 MmIsAddressValid(void* BaseAddress)
{
  return MmIsAddressValidEx((unsigned __int64)BaseAddress);
}

