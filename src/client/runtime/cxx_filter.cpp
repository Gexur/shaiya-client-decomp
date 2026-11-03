#include "cxx_filter.h"
#include "cxx_dispatch.h"

extern "C" {
__declspec(dllimport) OriginalUnhandledFilter
    __attribute__((stdcall)) SetUnhandledExceptionFilter(OriginalUnhandledFilter);
OriginalUnhandledFilter dat_0224ee60 = nullptr;
}

extern "C" int32_t __attribute__((stdcall)) fun_005d29ec(OriginalExceptionPointers* pointers) {
    OriginalExceptionRecord* exception = pointers->record;
    if (exception->code == 0xe06d7363u && exception->parameter_count == 3 &&
        (exception->parameters[0] == 0x19930520u || exception->parameters[0] == 0x19930521u))
        fun_005d292f();
    if (dat_0224ee60 != nullptr && fun_005dc93f(reinterpret_cast<void*>(dat_0224ee60)) != 0)
        return dat_0224ee60(pointers);
    return 0;
}

extern "C" int32_t fun_005d2a3a() {
    dat_0224ee60 = SetUnhandledExceptionFilter(fun_005d29ec);
    return 0;
}

extern "C" OriginalUnhandledFilter fun_005d2a4d() {
    return SetUnhandledExceptionFilter(dat_0224ee60);
}
