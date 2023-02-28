PIO_WORKITEM __fastcall IoAllocateWorkItem(__int64 DeviceObject)
{
  IO_WORKITEM* IoWorkItem; // rax

  IoWorkItem = IopVerifierExAllocatePool(0x200i64, 0x58i64);
  if ( IoWorkItem )
  {
    *(_QWORD *)(IoWorkItem + 0x38) = 0i64;      // # struct _ETHREAD* WorkOnBehalfThread; 
    *(_QWORD *)(IoWorkItem + 0x28) = DeviceObject;// # IoObject
    *(_DWORD *)(IoWorkItem + 0x40) = 1;         // # Type
    *(_QWORD *)IoWorkItem = 0i64;               // # WorkItem.List.Flink
    *(_QWORD *)(IoWorkItem + 0x10) = IopProcessWorkItem;// # WorkItem.WorkerRoutine -> Callback 
    *(_QWORD *)(IoWorkItem + 0x18) = IoWorkItem;// # WorkItem.Parameter
  }
  return IoWorkItem;
}
