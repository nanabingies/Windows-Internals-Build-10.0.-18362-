
#include <ntifs.h>
#include <ntddk.h>

__int64 __fastcall PsCreateSystemThreadEx(__int64, __int64, _OBJECT_ATTRIBUTES*, __int64, CLIENT_ID*,
    __int64, __int64, __int64*, __int64*);

__int64 __fastcall PsCreateSystemThread(
    int ThreadHandle,
    int DesiredAccess,
    _OBJECT_ATTRIBUTES* ObjectAttributes,
    int ProcessHandle,
    CLIENT_ID* ClientId,
    __int64 StartRoutine,
    __int64 StartContext)
{
    return PsCreateSystemThreadEx(
        ThreadHandle,
        DesiredAccess,
        ObjectAttributes,
        ProcessHandle,
        ClientId,
        StartRoutine,
        StartContext,
        0i64,
        0i64);
}

__int64 __fastcall PsCreateSystemThreadEx(
    __int64 ThreadHandle,
    int DesiredAccess,
    _OBJECT_ATTRIBUTES* Param_ObjectAttributes,
    __int64 ProcessHandle,
    CLIENT_ID* ClientId,
    __int64 StartRoutine,
    __int64 StartContext,
    __int64* a8,
    __int64* a9) {

    char _v12; // r13
    __int64 _v14; // rbx
    __int64 *_v10; // r14
    __int128 _v20; // xmm0
    __int128 var_F0[0x3];
    int _v21;
    CLIENT_ID* _v25 = ClientId;
    _OBJECT_ATTRIBUTES* _oa;
    __int64 _procHandle = ProcessHandle;
    int var_290 = DesiredAccess;
    __int64 var_278 = ThreadHandle;
    ULONG var_22C[0xF8];
    CHAR _v30[0x1F0];
    ULONG SystemProcess; // rsi
    __int64 _v24; // [rsp+78h] [rbp-88h] BYREF
    __int64 _v28; // [rsp+C0h] [rbp-40h] BYREF
    __int64 _v29;
    __int64 _v13;
    PEPROCESS Eprocess;

    memset(&_v30, 0, sizeof(_v30));
    memset(&_oa, 0, sizeof(_oa));
    _v28 = _v29 = 0;

    if (KeGetCurrentIrql() >= DISPATCH_LEVEL) {
        KeBugCheckEx(IRQL_UNEXPECTED_VALUE, (KeGetCurrentIrql() << 0x10) | 4, NULL, NULL, NULL);
        DbgBreakPoint();
    }

    _v12 = 0;
    if (ProcessHandle) {
        _v13 = sub_1405EFC80(ProcessHandle, 2, PsProcessType, 0, 'rCsP', (__int64)&_v24, 0i64, 0i64);
        if (!NT_SUCCESS(_v13)) {
            return _v13;
        }
        _v12 = 1;
        Eprocess = (PEPROCESS)_v24;
    }
    else {      // According to msdn
                // ProcessHandle should be NULL for a driver-created thread. 
                // Use the NtCurrentProcess macro, defined in Ntddk.h, to specify the current process.
        Eprocess = (PEPROCESS)((PUCHAR)nt!PspSystemPartition + 0x68);
    }

    SystemProcess = *(ULONG*)((PUCHAR)Eprocess + 0x6FC);  // Eprocess->SystemProcess
    if ((SystemProcess & 0x1000) != 0) {      // PAGE_SIZE aligned
        if (a8) {
            goto LABEL_17;
        }
        if (!a9) {
            LONG _long = InterlockedExchangeAdd((volatile LONG*)&nt!PspSystemThreadAssignment, 1);
            _long += 1;
            USHORT g_count = KeQueryActiveGroupCount();
            _v10 = &_v28;
            _long /= g_count;
            _v29 = 0;
            _v28 = nt!KeActiveProcessors[0];
        }

        if (_v10) {
        LABEL_17:
            _v20 = _v10;
            _v21 = 0x1000;
            var_22C[0] = 0x1000;
            var_F0[0] = _v20;
        }
        else {
            _v21 = var_22C[0];
        }

        if (a9) {
            var_22C[0] = _v21 | 0x4000;
        }
    }

    if (Param_ObjectAttributes) {
        _oa = Param_ObjectAttributes;
    }
    else {
        InitializeObjectAttributes(_oa, NULL, 200, NULL, NULL);
    }

    _v13 = nt!PspCreateThread(ThreadHandle,
        DesiredAccess,
        &_oa,
        0,
        SystemProcess,
        (unsigned __int64)var_22C & -(__int64)((SystemProcess & 0x1000) != 0),
        ClientId,
        0i64,
        0i64,
        0,
        StartRoutine,
        StartContext,
        0i64);

    if (_v12) {
        ObDereferenceObjectWithTag(Eprocess, 'rCsP');
    }

    return _v13;
}
