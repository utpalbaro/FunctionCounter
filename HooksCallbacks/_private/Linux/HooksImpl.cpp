#include "../../HooksCallback.h"

extern "C" {
    void __cyg_profile_func_enter (void *this_fn,
                                void *call_site)
    {
        onFunctionEnter(this_fn);
    }

    void __cyg_profile_func_exit  (void *this_fn,
                                void *call_site)
    {
        onFunctionExit(this_fn);
    }
}