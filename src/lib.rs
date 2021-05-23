#![recursion_limit = "4096"]

use cpp::*;

cpp! {{
    #include <iostream>
    #include "bsqruntime.h"

    namespace BSQ
    {

        BSQString* nsmain__mainI77I(BSQRefScope& $callerscope$)
        {
            int val = 32;
            int *v = &val;
            //returns void
            rust!(xx___1 [v : &mut i32 as "int*"] { *v = 43; } );
            
            BSQRefScope _scope_I19I;
            BSQRecord _tmp_2I44I;
            BSQString* $$return; BSQString* _tmp_3I45I; BSQString* _tmp_4I46I; BSQString* _tmp_11I72I; BSQString* _tmp_15I78I; BSQString* _tmp_7I52I; BSQString* ___ir_ret__I37I;
            nscore__list_t_nscore__string_I10I* _tmp_16I79I;
            nsmain__consoleI18I* _tmp_1I63I; nsmain__consoleI18I* _tmp_0I42I; nsmain__consoleI18I* consoleI54I;

            _tmp_2I44I = nsmain__console__readlineI43I(_scope_I19I);
            _tmp_3I45I = BSQ_GET_VALUE_PTR(_tmp_2I44I.atFixed<MIRPropertyEnum::stdin>(), BSQString);
            _tmp_4I46I = BSQ_GET_VALUE_PTR(_tmp_2I44I.atFixed<MIRPropertyEnum::stdout>(), BSQString);
            _tmp_1I63I = BSQ_NEW_ADD_SCOPE(_scope_I19I, nsmain__consoleI18I, INC_REF_DIRECT(BSQString, _tmp_3I45I), INC_REF_DIRECT(BSQString, _tmp_4I46I));
            _tmp_0I42I = nsiterate__steps_s_nsmain__console__input_bsq_25_0_I58I(_tmp_1I63I, 10, _scope_I19I);
            consoleI54I = _tmp_0I42I;
            _tmp_11I72I = consoleI54I->nsmain__console_stdinI16I;
            _tmp_15I78I = consoleI54I->nsmain__console_stdoutI17I;
            _tmp_16I79I = BSQ_NEW_ADD_SCOPE(_scope_I19I, nscore__list_t_nscore__string_I10I, MIRNominalTypeEnum::nscore__list_t_nscore__string_I10I, { INC_REF_DIRECT(BSQString, (&Runtime::STR__1)), INC_REF_DIRECT(BSQString, _tmp_11I72I), INC_REF_DIRECT(BSQString, (&Runtime::STR__2)), INC_REF_DIRECT(BSQString, _tmp_15I78I) });
            _tmp_7I52I = nscore__string__concatI70I(_tmp_16I79I, _scope_I19I);
            ___ir_ret__I37I = _tmp_7I52I;
            goto returnassign;

        returnassign:
            $$return = ___ir_ret__I37I;
            goto exit;

        exit:
            $callerscope$.callReturnDirect($$return);
            return $$return;
        }
    }
}}


pub fn bsq() {
    let name = std::ffi::CString::new("BSQ Finished Executing").unwrap();
    let name_ptr = name.as_ptr();
    let r = unsafe {
        cpp!([name_ptr as "const char *"] -> u32 as "int32_t" {
            
            int val = 32;
            int *v = &val;
            //returns void
            rust!(xx___1 [v : &mut i32 as "int*"] { *v = 43; } );
            
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