char __fastcall MmIsAddressValidEx(unsigned __int64 VirtualAddress);

__int64 MmIsAddressValid(PVOID BaseAddress)
{
  return MmIsAddressValidEx(BaseAddress);
}