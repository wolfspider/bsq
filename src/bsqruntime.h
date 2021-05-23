//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#include "common.h"
#include "bsqvalue.h"
#include "bsqkeyvalues.h"

#include "bsqcustom/bsqlist_decl.h"
#include "bsqcustom/bsqlist_ops.h"
//TODO: Stack defs here
//TODO: Queue defs here
#include "bsqcustom/bsqset_decl.h"
#include "bsqcustom/bsqset_ops.h"
#include "bsqcustom/bsqmap_decl.h"
#include "bsqcustom/bsqmap_ops.h"
#pragma clang diagnostic pop

#pragma once

#define GET_RC_OPS(TAG) (bsq_ops[GET_MIR_TYPE_POSITION(TAG)])

#define PARSER_INTERNAL_CHECK(C, M) { if(C) { printf("\"%s\" in %s on line %i\n", M, __FILE__, __LINE__); fflush(stdout); exit(1); } }
#define PARSER_PARSE_ERROR(M, P) BSQParseError(M, P->line, P->column, P->computeContext())

#define LEX_CFLOW(OP) if (OP) { return; }



namespace BSQ
{
class Runtime
{
public:
static BSQString STR__0;
static BSQString STR__1;
static BSQString STR__2;


//%%EPHEMERAL_LIST_DECLARE
};
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
BSQString Runtime::STR__0("", 1);
BSQString Runtime::STR__1("you entered: ", 1);
BSQString Runtime::STR__2(" and Bosque printed: ", 1);

std::string diagnostic_format(Value v)
{
    if(BSQ_IS_VALUE_NONE(v))
    {
        return std::string("none");
    }
    else if(BSQ_IS_VALUE_BOOL(v))
    {
        return BSQ_GET_VALUE_BOOL(v) ? std::string("true") : std::string("false");
    }
    else if(BSQ_IS_VALUE_TAGGED_INT(v))
    {
        return std::to_string(BSQ_GET_VALUE_TAGGED_INT(v));
    }
    else
    {
        BSQRef* vv = BSQ_GET_VALUE_PTR(v, BSQRef);
    
        auto rcategory = GET_MIR_TYPE_CATEGORY(vv->nominalType);
        switch(rcategory)
        {
            case MIRNominalTypeEnum_Category_BigInt:
                return DisplayFunctor_BSQBigInt{}(dynamic_cast<BSQBigInt*>(vv));
            case MIRNominalTypeEnum_Category_String:
                return DisplayFunctor_BSQString{}(dynamic_cast<BSQString*>(vv));
            case MIRNominalTypeEnum_Category_SafeString:
                return DisplayFunctor_BSQSafeString{}(dynamic_cast<BSQSafeString*>(vv));
            case MIRNominalTypeEnum_Category_StringOf:
                return DisplayFunctor_BSQStringOf{}(dynamic_cast<BSQStringOf*>(vv));
            case MIRNominalTypeEnum_Category_UUID:
                return DisplayFunctor_BSQUUID{}(dynamic_cast<Boxed_BSQUUID*>(vv)->bval);
            case MIRNominalTypeEnum_Category_LogicalTime:
                return DisplayFunctor_BSQLogicalTime{}(dynamic_cast<Boxed_BSQLogicalTime*>(vv)->bval);
            case MIRNominalTypeEnum_Category_CryptoHash:
                return DisplayFunctor_BSQCryptoHash{}(dynamic_cast<BSQCryptoHash*>(vv));
            case MIRNominalTypeEnum_Category_Enum:
                return DisplayFunctor_BSQEnum{}(dynamic_cast<Boxed_BSQEnum*>(vv)->bval);
            case MIRNominalTypeEnum_Category_IdKeySimple:
                return DisplayFunctor_BSQIdKeySimple{}(dynamic_cast<Boxed_BSQIdKeySimple*>(vv)->bval);
            case MIRNominalTypeEnum_Category_IdKeyCompound:
                return DisplayFunctor_BSQIdKeyCompound{}(dynamic_cast<Boxed_BSQIdKeyCompound*>(vv)->bval);
            case MIRNominalTypeEnum_Category_Float64:
                return DisplayFunctor_double{}(dynamic_cast<Boxed_double*>(vv)->bval);
            case MIRNominalTypeEnum_Category_ByteBuffer:
                return DisplayFunctor_BSQByteBuffer{}(dynamic_cast<BSQByteBuffer*>(vv));
            case MIRNominalTypeEnum_Category_Buffer:
                return DisplayFunctor_BSQBuffer{}(dynamic_cast<BSQBuffer*>(vv));
            case MIRNominalTypeEnum_Category_BufferOf:
                return DisplayFunctor_BSQBufferOf{}(dynamic_cast<BSQBufferOf*>(vv));
            case MIRNominalTypeEnum_Category_ISOTime:
                return DisplayFunctor_BSQISOTime{}(dynamic_cast<Boxed_BSQISOTime*>(vv)->bval);
            case MIRNominalTypeEnum_Category_Regex:
                return DisplayFunctor_BSQRegex{}(dynamic_cast<Boxed_BSQRegex*>(vv)->bval);
            case MIRNominalTypeEnum_Category_Tuple:
                return DisplayFunctor_BSQTuple{}(*dynamic_cast<BSQTuple*>(vv));
            case MIRNominalTypeEnum_Category_Record:
                return DisplayFunctor_BSQRecord{}(*dynamic_cast<BSQRecord*>(vv));
            default:
                return dynamic_cast<BSQObject*>(vv)->display();
        }
    }
}

/*forward type decls*/
class nscore__list_t_nscore__string_I10I;
class nsmain__consoleI18I;

/*type decls*/
class nscore__list_t_nscore__string_I10I : public BSQList<BSQString*, RCDecFunctor_BSQString, DisplayFunctor_BSQString>
{
public:
nscore__list_t_nscore__string_I10I(MIRNominalTypeEnum ntype) : BSQList<BSQString*, RCDecFunctor_BSQString, DisplayFunctor_BSQString>(ntype) { ; }
nscore__list_t_nscore__string_I10I(MIRNominalTypeEnum ntype, std::vector<BSQString*>&& vals) : BSQList<BSQString*, RCDecFunctor_BSQString, DisplayFunctor_BSQString>(ntype, std::move(vals)) { ; }
virtual ~nscore__list_t_nscore__string_I10I() { ; }
};

class nsmain__consoleI18I : public BSQObject
{
public:
    BSQString* nsmain__console_stdinI16I;
    BSQString* nsmain__console_stdoutI17I;

    nsmain__consoleI18I(BSQString* stdin, BSQString* stdout) : BSQObject(MIRNominalTypeEnum::nsmain__consoleI18I), nsmain__console_stdinI16I(stdin), nsmain__console_stdoutI17I(stdout) { ; }
    virtual ~nsmain__consoleI18I() { ; }

    virtual void destroy() { BSQRef::decrementDirect(this->nsmain__console_stdinI16I); BSQRef::decrementDirect(this->nsmain__console_stdoutI17I); }

    std::string display() const;
};

/*ephemeral decls*/


/*forward vable decls*/


/*forward function decls*/
BSQString* nsmain__console_____consI36I(BSQRefScope& $callerscope$);
BSQString* nscore__string__s_readlineI39I(BSQString* sI38I, BSQRefScope& $callerscope$);
BSQString* nscore__string__readlineI41I(BSQString* _thisI40I, BSQRefScope& $callerscope$);
BSQRecord nsmain__console__readlineI43I(BSQRefScope& $callerscope$);
BSQString* nscore__string__s_writelineI47I(BSQString* sI38I, BSQRefScope& $callerscope$);
BSQString* nscore__string__writelineI49I(BSQString* _thisI40I, BSQString* msgI48I, BSQRefScope& $callerscope$);
nsmain__consoleI18I* nsmain__console__writelineI50I(nsmain__consoleI18I* _thisI40I, BSQString* msgI48I, BSQRefScope& $callerscope$);
nsmain__consoleI18I* fn__input_bsq_25__573I55I(nsmain__consoleI18I* consoleI54I, BSQRefScope& $callerscope$);
nsmain__consoleI18I* nsiterate__steps_s_nsmain__console__input_bsq_25_0_I58I(nsmain__consoleI18I* initialI56I, int64_t kI57I, BSQRefScope& $callerscope$);
int64_t nscore__list__s_size_t_nscore__string_I61I(nscore__list_t_nscore__string_I10I* lI60I);
BSQBool nscore__list__front_t_nscore__string___preI62I(nscore__list_t_nscore__string_I10I* _thisI40I);
BSQString* nscore__list__s_unsafe_get_t_nscore__string_I65I(nscore__list_t_nscore__string_I10I* lI60I, int64_t iI64I, BSQRefScope& $callerscope$);
BSQString* nscore__list__front_t_nscore__string_I66I(nscore__list_t_nscore__string_I10I* _thisI40I, BSQRefScope& $callerscope$);
BSQString* nscore__string__s_concatI68I(nscore__list_t_nscore__string_I10I* s1I67I, BSQRefScope& $callerscope$);
BSQString* nscore__string__concatI70I(nscore__list_t_nscore__string_I10I* argsI69I, BSQRefScope& $callerscope$);
BSQString* nsmain__mainI77I(BSQRefScope& $callerscope$);

/*typecheck decls*/


/*vable decls*/


/*function decls*/
std::string nsmain__consoleI18I::display() const
    {
        BSQRefScope _scope_I19I;
        return std::string("NSMain::Console{ ") + diagnostic_format(((Value)this->nsmain__console_stdinI16I)) + std::string(", ") + diagnostic_format(((Value)this->nsmain__console_stdoutI17I)) + std::string(" }");
    }
BSQString* nsmain__console_____consI36I(BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQString* $$return; BSQString* ___ir_ret__I37I;

    ___ir_ret__I37I = (&Runtime::STR__0);
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQString* nscore__string__s_readlineI39I(BSQString* sI38I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I19I;
    char line[255]; scanf("%[^\n]s",line); std::string str(line); auto $$return = BSQ_NEW_NO_RC(BSQString, std::move(str));
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__string__readlineI41I(BSQString* _thisI40I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQString* $$return; BSQString* _tmp_0I42I; BSQString* ___ir_ret__I37I;

    _tmp_0I42I = nscore__string__s_readlineI39I(_thisI40I, _scope_I19I);
    ___ir_ret__I37I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQRecord nsmain__console__readlineI43I(BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQRecord $$return; BSQRecord _tmp_0I42I; BSQRecord ___ir_ret__I37I;
    BSQString* _tmp_2I44I; BSQString* _tmp_3I45I; BSQString* _tmp_4I46I;

    _tmp_2I44I = nsmain__console_____consI36I(_scope_I19I);
    _tmp_3I45I = nscore__string__readlineI41I(_tmp_2I44I, _scope_I19I);
    _tmp_4I46I = nsmain__console_____consI36I(_scope_I19I);
    _tmp_0I42I = BSQRecord::createFromSingle<(DATA_KIND_CLEAR_FLAG | DATA_KIND_POD_FLAG | DATA_KIND_API_FLAG)>({ std::make_pair(MIRPropertyEnum::stdin, ((Value)_tmp_3I45I)), std::make_pair(MIRPropertyEnum::stdout, ((Value)_tmp_4I46I)) });
    ___ir_ret__I37I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    RCReturnFunctor_BSQRecord{}($$return, $callerscope$);
    return $$return;
}

BSQString* nscore__string__s_writelineI47I(BSQString* sI38I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I19I;
    std::string str = std::string(sI38I->sdata.cbegin(), sI38I->sdata.cend()); std::cout << str << "\n"; auto $$return = BSQ_NEW_NO_RC(BSQString, std::move(str));
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__string__writelineI49I(BSQString* _thisI40I, BSQString* msgI48I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQString* $$return; BSQString* _tmp_0I42I; BSQString* ___ir_ret__I37I;

    _tmp_0I42I = nscore__string__s_writelineI47I(msgI48I, _scope_I19I);
    ___ir_ret__I37I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

nsmain__consoleI18I* nsmain__console__writelineI50I(nsmain__consoleI18I* _thisI40I, BSQString* msgI48I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQString* _tmp_5I51I; BSQString* _tmp_7I52I; BSQString* _tmp_8I53I;
    nsmain__consoleI18I* $$return; nsmain__consoleI18I* _tmp_2I44I; nsmain__consoleI18I* ___ir_ret__I37I;

    _tmp_5I51I = _thisI40I->nsmain__console_stdinI16I;
    _tmp_7I52I = nsmain__console_____consI36I(_scope_I19I);
    _tmp_8I53I = nscore__string__writelineI49I(_tmp_7I52I, msgI48I, _scope_I19I);
    _tmp_2I44I = BSQ_NEW_ADD_SCOPE(_scope_I19I, nsmain__consoleI18I, INC_REF_DIRECT(BSQString, _tmp_5I51I), INC_REF_DIRECT(BSQString, _tmp_8I53I));
    ___ir_ret__I37I = _tmp_2I44I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

nsmain__consoleI18I* fn__input_bsq_25__573I55I(nsmain__consoleI18I* consoleI54I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQString* _tmp_4I46I;
    nsmain__consoleI18I* $$return; nsmain__consoleI18I* _tmp_0I42I; nsmain__consoleI18I* ___ir_ret__I37I;

    _tmp_4I46I = consoleI54I->nsmain__console_stdinI16I;
    _tmp_0I42I = nsmain__console__writelineI50I(consoleI54I, _tmp_4I46I, _scope_I19I);
    ___ir_ret__I37I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

nsmain__consoleI18I* nsiterate__steps_s_nsmain__console__input_bsq_25_0_I58I(nsmain__consoleI18I* initialI56I, int64_t kI57I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I19I;
    BSQRefScope _lambda_scope_I59I(true); nsmain__consoleI18I* cacc = initialI56I; for(int64_t i = 0; i < kI57I; ++i) { nsmain__consoleI18I* nacc = [=, &_lambda_scope_I59I](nsmain__consoleI18I* $arg_0) -> nsmain__consoleI18I* { return fn__input_bsq_25__573I55I($arg_0, _lambda_scope_I59I); }(cacc); RCDecFunctor_BSQRef{}(cacc); cacc = nacc; } auto $$return = cacc;
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

int64_t nscore__list__s_size_t_nscore__string_I61I(nscore__list_t_nscore__string_I10I* lI60I) { 
    BSQRefScope _scope_I19I;
    auto $$return = (int64_t)(lI60I->entries.size());
    
    return $$return;
 }

BSQBool nscore__list__front_t_nscore__string___preI62I(nscore__list_t_nscore__string_I10I* _thisI40I)
{
    BSQRefScope _scope_I19I;
    BSQBool $$return, _tmp_0I42I, ___ir_ret__I37I;
    int64_t _tmp_1I63I;

    _tmp_1I63I = nscore__list__s_size_t_nscore__string_I61I(_thisI40I);
    _tmp_0I42I = !EqualFunctor_int64_t{}(_tmp_1I63I, 0);
    ___ir_ret__I37I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    return $$return;
}

BSQString* nscore__list__s_unsafe_get_t_nscore__string_I65I(nscore__list_t_nscore__string_I10I* lI60I, int64_t iI64I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I19I;
    auto $$return = lI60I->entries[iI64I];
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__list__front_t_nscore__string_I66I(nscore__list_t_nscore__string_I10I* _thisI40I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQBool _tmp_0I42I;
    BSQString* $$return; BSQString* _tmp_1I63I; BSQString* ___ir_ret__I37I;

    _tmp_0I42I = nscore__list__front_t_nscore__string___preI62I(_thisI40I);
    if(_tmp_0I42I) {goto preok_4;} else {goto prefail_3;}

prefail_3:
    BSQ_ABORT("Fail pre-condition", "/usr/home/basilisk/BosqueLanguage/impl/bin/core/cpp/list.bsq", 100);

preok_4:
    _tmp_1I63I = nscore__list__s_unsafe_get_t_nscore__string_I65I(_thisI40I, 0, _scope_I19I);
    ___ir_ret__I37I = _tmp_1I63I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I37I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQString* nscore__string__s_concatI68I(nscore__list_t_nscore__string_I10I* s1I67I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I19I;
    std::string acc; for(auto iter = s1I67I->entries.cbegin(); iter != s1I67I->entries.cend(); ++iter) { acc.append((*iter)->sdata); }; auto $$return = BSQ_NEW_NO_RC(BSQString, std::move(acc));
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__string__concatI70I(nscore__list_t_nscore__string_I10I* argsI69I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I19I;
    BSQBool _tmp_0I42I, _tmp_5I51I;
    int64_t _tmp_1I63I, _tmp_6I71I;
    BSQString* $$return; BSQString* _tmp_11I72I; BSQString* ___ir_ret__I37I; BSQString* _tmp_9I73I; BSQString* ___ir_ret___1I74I; BSQString* ___ir_ret___2I75I; BSQString* ___ir_ret___3I76I;

    _tmp_1I63I = nscore__list__s_size_t_nscore__string_I61I(argsI69I);
    _tmp_0I42I = EqualFunctor_int64_t{}(_tmp_1I63I, 0);
    if(_tmp_0I42I) {goto Lifstmt_0true_4;} else {goto Lifstmt_0false_5;}

Lifstmt_0false_5:
    _tmp_6I71I = nscore__list__s_size_t_nscore__string_I61I(argsI69I);
    _tmp_5I51I = EqualFunctor_int64_t{}(_tmp_6I71I, 1);
    if(_tmp_5I51I) {goto Lifstmt_1true_6;} else {goto Lifstmt_1false_7;}

Lifstmt_1false_7:
    _tmp_11I72I = nscore__string__s_concatI68I(argsI69I, _scope_I19I);
    ___ir_ret__I37I = _tmp_11I72I;
    ___ir_ret___3I76I = ___ir_ret__I37I;
    goto returnassign;

Lifstmt_1true_6:
    _tmp_9I73I = nscore__list__front_t_nscore__string_I66I(argsI69I, _scope_I19I);
    ___ir_ret___1I74I = _tmp_9I73I;
    ___ir_ret___3I76I = ___ir_ret___1I74I;
    goto returnassign;

Lifstmt_0true_4:
    ___ir_ret___2I75I = (&Runtime::STR__0);
    ___ir_ret___3I76I = ___ir_ret___2I75I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret___3I76I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

#pragma clang diagnostic pop

/*
class BSQParseError
{
public:
const char* msg;
const size_t line;
const std::string context;

BSQParseError(const char* msg, size_t line, size_t column, const std::string& context) : msg(msg), line(line), context(context) { ; }
};

enum APIFormatKind
{
    Invalid,

    Null,
    None,
    True,
    False,
    Int,
    BigInt,
    Float64,
    String,
    SafeString,
    ISOTime,
    UUID,
    LogicalTime,
    CryptoHash,
    Comma,
    Colon,
    Arrow,
    LBrack,
    RBrack,
    LBrace,
    RBrace,
    ListStart,
    ListEnd,
    MapStart,
    MapEnd,
    LParen,
    RParen,
    ResultOk,
    ResultErr,

    NAME_TOKEN,

    EOF_TOKEN,
    ERROR
};

template <BSQBufferEncoding enc, bool bmode>
class APITypeEncodingParser
{
public:
    APITypeEncodingParser(const std::string* data) { ; }

    std::string computeContext() { return "[INVALID]"; }

    APIFormatKind peekJSON() { return APIFormatKind::Invalid; }
    void pop() { ; }
    std::pair<const char*, const char*> read() { std::make_pair(nullptr, nullptr); }
};

class LexerRegexs
{
public:
    static std::regex whitespaceRe; 
    static std::regex commentRe;
    static std::regex intRe;
    static std::regex bigintRe;
    static std::regex floatRe;
    static std::regex stringRe;
    static std::regex typedStringRe;
    static std::regex isotimeRe;
    static std::regex uuidRe;
    static std::regex logicaltimeRe;
    static std::regex hashRe;

    static std::regex nameRe;

    static std::regex newlineRe;
};

template <bool bmode>
class APITypeEncodingParser<BSQBufferEncoding::UTF8, bmode>
{
private:
    const std::string* data;
    const char* pos;
    const char* max;

    APIFormatKind ctoken;
    const char* end;

    size_t line;

    void updateFilePos(const std::cmatch& m)
    {
        auto nl_begin = std::sregex_iterator(this->pos, this->pos + m.length(), LexerRegexs::newlineRe);
        auto nl_end = std::sregex_iterator();

        this->line += std::distance(nl_begin, nl_end);
    }

    void consumeWSAndComment() 
    {
        while(this->pos < this->max)
        {
            std::cmatch m;
            auto opos = this->pos;

            if (this->pos < this->max && std::regex_search(this->pos, this->max, m, LexerRegexs::whitespaceRe, std::regex_constants::match_continuous))
            {
                this->updateFilePos(m);
                this->pos += m.length();
            }

            if constexpr (bmode)
            {
                if (this->pos < this->max && std::regex_search(this->pos, this->max, m, LexerRegexs::commentRe, std::regex_constants::match_continuous))
                {
                    this->updateFilePos(m);
                    this->pos += m.length();
                }
            }

            if(this->pos == opos)
            {
                return;
            }
        }

        this->ctoken = APIFormatKind::EOF_TOKEN;
    }

    bool checkMatch(const std::regex& re, APIFormatKind token) 
    {
        std::cmatch m;
        bool mtch = std::regex_search(this->pos, this->max, m, LexerRegexs::whitespaceRe, std::regex_constants::match_continuous);
        if(mtch)
        {
            this->updateFilePos(m);

            this->ctoken = token;
            this->end = this->pos + m.length();
        }

        return mtch;
    }

    template <size_t n>
    bool checkLiteral(const char(&literal)[n], APIFormatKind token) 
    {
        bool mtch = (std::distance(this->pos, this->max) >= n) && std::equal(&literal, &literal + n, this->pos);
        if(mtch)
        {
            this->ctoken = token;
            this->end = this->pos + n;
        }

        return mtch;
    }

    void advance()
    {
        this->ctoken = APIFormatKind::Invalid;
        
        this->pos = this->end;
        this->end = nullptr;
    }

    void lexToken()
    {
        this->advance();
        this->consumeWSAndComment();

        if constexpr (bmode)
        {
            LEX_CFLOW(this->checkLiteral("none", APIFormatKind::None));
            LEX_CFLOW(this->checkLiteral("true", APIFormatKind::True));
            LEX_CFLOW(this->checkLiteral("false", APIFormatKind::False));

            LEX_CFLOW(this->checkMatch(LexerRegexs::intRe, APIFormatKind::Int));
            LEX_CFLOW(this->checkMatch(LexerRegexs::bigintRe, APIFormatKind::BigInt));
            LEX_CFLOW(this->checkMatch(LexerRegexs::floatRe, APIFormatKind::Float64));
            LEX_CFLOW(this->checkMatch(LexerRegexs::stringRe, APIFormatKind::String));
            LEX_CFLOW(this->checkMatch(LexerRegexs::typedStringRe, APIFormatKind::SafeString));
            LEX_CFLOW(this->checkMatch(LexerRegexs::isotimeRe, APIFormatKind::ISOTime));
            LEX_CFLOW(this->checkMatch(LexerRegexs::uuidRe, APIFormatKind::UUID));
            LEX_CFLOW(this->checkMatch(LexerRegexs::logicaltimeRe, APIFormatKind::LogicalTime));
            LEX_CFLOW(this->checkMatch(LexerRegexs::hashRe, APIFormatKind::CryptoHash));

            LEX_CFLOW(this->checkLiteral(",", APIFormatKind::Comma));
            LEX_CFLOW(this->checkLiteral(":", APIFormatKind::Colon));
            LEX_CFLOW(this->checkLiteral("=>", APIFormatKind::Arrow));

            LEX_CFLOW(this->checkLiteral("[", APIFormatKind::LBrack));
            LEX_CFLOW(this->checkLiteral("]", APIFormatKind::RBrack));
            LEX_CFLOW(this->checkLiteral("{", APIFormatKind::LBrace));
            LEX_CFLOW(this->checkLiteral("}", APIFormatKind::RBrace));

            LEX_CFLOW(this->checkLiteral("[|", APIFormatKind::ListStart));
            LEX_CFLOW(this->checkLiteral("|]", APIFormatKind::ListEnd));
            LEX_CFLOW(this->checkLiteral("{|", APIFormatKind::MapStart));
            LEX_CFLOW(this->checkLiteral("|}", APIFormatKind::MapEnd));
            LEX_CFLOW(this->checkLiteral("{|", APIFormatKind::MapStart));
            LEX_CFLOW(this->checkLiteral("|}", APIFormatKind::MapEnd));
            LEX_CFLOW(this->checkLiteral("(", APIFormatKind::LParen));
            LEX_CFLOW(this->checkLiteral(")", APIFormatKind::RParen));

            LEX_CFLOW(this->checkLiteral("ok(", APIFormatKind::ResultOk));
            LEX_CFLOW(this->checkLiteral("err(", APIFormatKind::ResultErr));

            LEX_CFLOW(this->checkMatch(LexerRegexs::nameRe, APIFormatKind::NAME_TOKEN));

            this->ctoken = APIFormatKind::ERROR;
        }
        else {
            LEX_CFLOW(this->checkLiteral("null", APIFormatKind::Null));
            LEX_CFLOW(this->checkLiteral("true", APIFormatKind::True));
            LEX_CFLOW(this->checkLiteral("false", APIFormatKind::False));

            LEX_CFLOW(this->checkMatch(LexerRegexs::intRe, APIFormatKind::Float64));
            LEX_CFLOW(this->checkMatch(LexerRegexs::floatRe, APIFormatKind::Float64));
            LEX_CFLOW(this->checkMatch(LexerRegexs::stringRe, APIFormatKind::String));

            LEX_CFLOW(this->checkLiteral(",", APIFormatKind::Comma));
            LEX_CFLOW(this->checkLiteral(":", APIFormatKind::Colon));

            LEX_CFLOW(this->checkLiteral("[", APIFormatKind::LBrack));
            LEX_CFLOW(this->checkLiteral("]", APIFormatKind::RBrack));
            LEX_CFLOW(this->checkLiteral("{", APIFormatKind::LBrace));
            LEX_CFLOW(this->checkLiteral("}", APIFormatKind::RBrace));

            this->ctoken = APIFormatKind::ERROR;
        }
    }

public:
    APITypeEncodingParser(const std::string* data) 
        : data(data), pos(data->c_str()), max(data->c_str() + data->size()), ctoken(APIFormatKind::Invalid), end(data->c_str()), line(1)
    { 
        this->lexToken();
    }

    std::string computeContext() 
    { 
        return "[INVALID]"; 
    }

    APIFormatKind peek() 
    {
        return this->ctoken;
    }

    void pop() 
    { 
        if(this->ctoken != APIFormatKind::EOF_TOKEN)
        {
            this->lexToken();
        }
    }

    std::pair<const char*, const char*> read() 
    {
        PARSER_INTERNAL_CHECK(this->ctoken != APIFormatKind::EOF_TOKEN && this->ctoken != APIFormatKind::ERROR, "BAD TOKEN");

        std::make_pair(this->pos, this->end); 
    }
};

template <BSQBufferEncoding enc, BSQBufferFormat fmt>
class APITypeParser
{
public:
    APITypeParser(const std::string* data) { ; }
};
*/
} // namespace BSQ
