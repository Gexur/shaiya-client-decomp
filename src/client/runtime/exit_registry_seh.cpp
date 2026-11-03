#include "exit_registry.h"

extern "C" OriginalExitCallback fun_005ccf28(OriginalExitCallback callback) {
    fun_005cdfc9();
    OriginalExitCallback result;
    __try {
        result = fun_005cce80(callback);
    } __finally {
        fun_005ccf5a();
    }
    return result;
}
