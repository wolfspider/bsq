#![recursion_limit = "4096"]

use cpp::*;

cpp! {{
#include <iostream>
#include "bsqruntime.h"
}}
pub fn bsq() {
let name = std::ffi::CString::new("BSQ Finished Executing").unwrap();
let name_ptr = name.as_ptr();
let r = unsafe {
cpp!([name_ptr as "const char *"] -> u32 as "int32_t" {

    using namespace BSQ;

/*main decl*/
    try {
    BSQRefScope _scope_I20I;
    std::cout << diagnostic_format(((Value)nsmain__mainI79I(_scope_I20I))) << "\n";
    std::cout << name_ptr << std::endl;
    fflush(stdout);
    return 0;
  } catch (BSQAbort& abrt) HANDLE_BSQ_ABORT(abrt);
    })
};
assert_eq!(r, 0);
}
