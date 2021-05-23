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
            
            try {
                BSQ::BSQRefScope _scope_I19I;
                std::cout << BSQ::diagnostic_format(((BSQ::Value)BSQ::nsmain__mainI77I(_scope_I19I))) << "\n";
                std::cout << name_ptr << std::endl;
                fflush(stdout);
                return 0;
              } catch (BSQ::BSQAbort& abrt) HANDLE_BSQ_ABORT(abrt) 
        })
    };
    assert_eq!(r, 0)
}