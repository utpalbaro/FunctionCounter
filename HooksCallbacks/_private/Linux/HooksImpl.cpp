#include "../../HooksCallback.h"

extern "C" {
    void __cyg_profile_func_enter (void *this_fn,
                                void *call_site)
    {
        onFunctionEnter(call_site);
    }

    void __cyg_profile_func_exit  (void *this_fn,
                                void *call_site)
    {
        onFunctionExit(call_site);
    }
}