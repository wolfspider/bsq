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
  static BSQString STR__10;
  static BSQString STR__1;
  static BSQString STR__2;
  static BSQString STR__3;
  static BSQString STR__4;
  static BSQString STR__5;
  static BSQString STR__6;
  static BSQString STR__7;
  static BSQString STR__8;
  static BSQString STR__9;





//%%EPHEMERAL_LIST_DECLARE
};
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

namespace BSQ
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
BSQString Runtime::STR__0("", 1);
  BSQString Runtime::STR__1(" ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", 1);
  BSQString Runtime::STR__10("Command Entered: ", 1);
  BSQString Runtime::STR__2("█   ▄▄     ▄▄   █", 1);
  BSQString Runtime::STR__3("█  █  █▀▀▀█  █  █", 1);
  BSQString Runtime::STR__4("█   ▀▀▀   ▀▀▀   █", 1);
  BSQString Runtime::STR__5("█ ▄▀▀▀▀▀▀▀▀▀▀▀▄ █", 1);
  BSQString Runtime::STR__6("▀▄█▄█▄▄▄▄▄▄▄█▄█▄▀", 1);
  BSQString Runtime::STR__7("TapeDeck version 0.1", 1);
  BSQString Runtime::STR__8("--------------------", 1);
  BSQString Runtime::STR__9("Enter Command:", 1);
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
class nsmain__consoleI19I;

/*type decls*/
class nscore__list_t_nscore__string_I10I : public BSQList<BSQString*, RCDecFunctor_BSQString, DisplayFunctor_BSQString>
{
public:
nscore__list_t_nscore__string_I10I(MIRNominalTypeEnum ntype) : BSQList<BSQString*, RCDecFunctor_BSQString, DisplayFunctor_BSQString>(ntype) { ; }
nscore__list_t_nscore__string_I10I(MIRNominalTypeEnum ntype, std::vector<BSQString*>&& vals) : BSQList<BSQString*, RCDecFunctor_BSQString, DisplayFunctor_BSQString>(ntype, std::move(vals)) { ; }
virtual ~nscore__list_t_nscore__string_I10I() { ; }
};

class nsmain__consoleI19I : public BSQObject
{
public:
    BSQString* nsmain__console_stdinI16I;
    BSQString* nsmain__console_stdoutI17I;
    nscore__list_t_nscore__string_I10I* nsmain__console_logI18I;

    nsmain__consoleI19I(BSQString* stdin, BSQString* stdout, nscore__list_t_nscore__string_I10I* log) : BSQObject(MIRNominalTypeEnum::nsmain__consoleI19I), nsmain__console_stdinI16I(stdin), nsmain__console_stdoutI17I(stdout), nsmain__console_logI18I(log) { ; }
    virtual ~nsmain__consoleI19I() { ; }

    virtual void destroy() { BSQRef::decrementDirect(this->nsmain__console_stdinI16I); BSQRef::decrementDirect(this->nsmain__console_stdoutI17I); BSQRef::decrementDirect(this->nsmain__console_logI18I); }

    std::string display() const;
};

/*ephemeral decls*/


/*forward vable decls*/


/*forward function decls*/
BSQString* nsmain__console_____consI37I(BSQRefScope& $callerscope$);
BSQRecord nsmain__console__createI39I(BSQRefScope& $callerscope$);
nscore__list_t_nscore__string_I10I* nsmain__console__log__consI43I(BSQRefScope& $callerscope$);
BSQString* nscore__string__s_writelineI45I(BSQString* sI44I, BSQRefScope& $callerscope$);
BSQString* nscore__string__writelineI48I(BSQString* _thisI46I, BSQString* msgI47I, BSQRefScope& $callerscope$);
nsmain__consoleI19I* nsmain__console__writelineI49I(nsmain__consoleI19I* _thisI46I, BSQString* msgI47I, BSQRefScope& $callerscope$);
BSQString* nscore__string__s_readlineI53I(BSQString* sI44I, BSQRefScope& $callerscope$);
BSQString* nscore__string__readlineI54I(BSQString* _thisI46I, BSQRefScope& $callerscope$);
nsmain__consoleI19I* nsmain__console__readlineI55I(nsmain__consoleI19I* _thisI46I, BSQRefScope& $callerscope$);
nscore__list_t_nscore__string_I10I* nscore__list__s_append_t_nscore__string_I60I(nscore__list_t_nscore__string_I10I* lI58I, nscore__list_t_nscore__string_I10I* lpI59I, BSQRefScope& $callerscope$);
nscore__list_t_nscore__string_I10I* nscore__list__append_t_nscore__string_I61I(nscore__list_t_nscore__string_I10I* _thisI46I, nscore__list_t_nscore__string_I10I* lI58I, BSQRefScope& $callerscope$);
nsmain__consoleI19I* nsmain__console__logI62I(nsmain__consoleI19I* _thisI46I, BSQRefScope& $callerscope$);
int64_t nscore__list__s_size_t_nscore__string_I66I(nscore__list_t_nscore__string_I10I* lI58I);
BSQBool nscore__list__front_t_nscore__string___preI67I(nscore__list_t_nscore__string_I10I* _thisI46I);
BSQString* nscore__list__s_unsafe_get_t_nscore__string_I69I(nscore__list_t_nscore__string_I10I* lI58I, int64_t iI68I, BSQRefScope& $callerscope$);
BSQString* nscore__list__front_t_nscore__string_I70I(nscore__list_t_nscore__string_I10I* _thisI46I, BSQRefScope& $callerscope$);
BSQString* nscore__string__s_concatI72I(nscore__list_t_nscore__string_I10I* s1I71I, BSQRefScope& $callerscope$);
BSQString* nscore__string__concatI74I(nscore__list_t_nscore__string_I10I* argsI73I, BSQRefScope& $callerscope$);
BSQString* nsmain__mainI79I(BSQRefScope& $callerscope$);

/*typecheck decls*/


/*vable decls*/


/*function decls*/
std::string nsmain__consoleI19I::display() const
    {
        BSQRefScope _scope_I20I;
        return std::string("NSMain::Console{ ") + diagnostic_format(((Value)this->nsmain__console_stdinI16I)) + std::string(", ") + diagnostic_format(((Value)this->nsmain__console_stdoutI17I)) + std::string(", ") + diagnostic_format(((Value)this->nsmain__console_logI18I)) + std::string(" }");
    }
BSQString* nsmain__console_____consI37I(BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQString* $$return; BSQString* ___ir_ret__I38I;

    ___ir_ret__I38I = (&Runtime::STR__0);
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQRecord nsmain__console__createI39I(BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQRecord $$return; BSQRecord _tmp_0I42I; BSQRecord ___ir_ret__I38I;
    BSQString* _tmp_1I40I; BSQString* _tmp_2I41I;

    _tmp_1I40I = nsmain__console_____consI37I(_scope_I20I);
    _tmp_2I41I = nsmain__console_____consI37I(_scope_I20I);
    _tmp_0I42I = BSQRecord::createFromSingle<(DATA_KIND_CLEAR_FLAG | DATA_KIND_POD_FLAG | DATA_KIND_API_FLAG)>({ std::make_pair(MIRPropertyEnum::stdin, ((Value)_tmp_1I40I)), std::make_pair(MIRPropertyEnum::stdout, ((Value)_tmp_2I41I)) });
    ___ir_ret__I38I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    RCReturnFunctor_BSQRecord{}($$return, $callerscope$);
    return $$return;
}

nscore__list_t_nscore__string_I10I* nsmain__console__log__consI43I(BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    nscore__list_t_nscore__string_I10I* $$return; nscore__list_t_nscore__string_I10I* _tmp_0I42I; nscore__list_t_nscore__string_I10I* ___ir_ret__I38I;

    _tmp_0I42I = BSQ_NEW_ADD_SCOPE(_scope_I20I, nscore__list_t_nscore__string_I10I, MIRNominalTypeEnum::nscore__list_t_nscore__string_I10I);
    ___ir_ret__I38I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQString* nscore__string__s_writelineI45I(BSQString* sI44I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I20I;
    std::string str = std::string(sI44I->sdata.cbegin(), sI44I->sdata.cend()); std::cout << str << "\n"; auto $$return = BSQ_NEW_NO_RC(BSQString, std::move(str));
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__string__writelineI48I(BSQString* _thisI46I, BSQString* msgI47I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQString* $$return; BSQString* _tmp_0I42I; BSQString* ___ir_ret__I38I;

    _tmp_0I42I = nscore__string__s_writelineI45I(msgI47I, _scope_I20I);
    ___ir_ret__I38I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

nsmain__consoleI19I* nsmain__console__writelineI49I(nsmain__consoleI19I* _thisI46I, BSQString* msgI47I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQString* _tmp_5I50I; BSQString* _tmp_7I51I; BSQString* _tmp_8I52I;
    nsmain__consoleI19I* $$return; nsmain__consoleI19I* _tmp_2I41I; nsmain__consoleI19I* ___ir_ret__I38I;

    _tmp_5I50I = _thisI46I->nsmain__console_stdinI16I;
    _tmp_7I51I = nsmain__console_____consI37I(_scope_I20I);
    _tmp_8I52I = nscore__string__writelineI48I(_tmp_7I51I, msgI47I, _scope_I20I);
    _tmp_2I41I = BSQ_NEW_ADD_SCOPE(_scope_I20I, nsmain__consoleI19I, INC_REF_DIRECT(BSQString, _tmp_5I50I), INC_REF_DIRECT(BSQString, _tmp_8I52I), INC_REF_DIRECT(nscore__list_t_nscore__string_I10I, _thisI46I->nsmain__console_logI18I));
    ___ir_ret__I38I = _tmp_2I41I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQString* nscore__string__s_readlineI53I(BSQString* sI44I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I20I;
    std::string str; std::getline(std::cin, str); auto $$return = BSQ_NEW_NO_RC(BSQString, std::move(str));
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__string__readlineI54I(BSQString* _thisI46I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQString* $$return; BSQString* _tmp_0I42I; BSQString* ___ir_ret__I38I;

    _tmp_0I42I = nscore__string__s_readlineI53I(_thisI46I, _scope_I20I);
    ___ir_ret__I38I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

nsmain__consoleI19I* nsmain__console__readlineI55I(nsmain__consoleI19I* _thisI46I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQString* _tmp_5I50I; BSQString* _tmp_6I56I; BSQString* _tmp_9I57I;
    nsmain__consoleI19I* $$return; nsmain__consoleI19I* _tmp_2I41I; nsmain__consoleI19I* ___ir_ret__I38I;

    _tmp_5I50I = _thisI46I->nsmain__console_stdinI16I;
    _tmp_6I56I = nscore__string__readlineI54I(_tmp_5I50I, _scope_I20I);
    _tmp_9I57I = _thisI46I->nsmain__console_stdoutI17I;
    _tmp_2I41I = BSQ_NEW_ADD_SCOPE(_scope_I20I, nsmain__consoleI19I, INC_REF_DIRECT(BSQString, _tmp_6I56I), INC_REF_DIRECT(BSQString, _tmp_9I57I), INC_REF_DIRECT(nscore__list_t_nscore__string_I10I, _thisI46I->nsmain__console_logI18I));
    ___ir_ret__I38I = _tmp_2I41I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

nscore__list_t_nscore__string_I10I* nscore__list__s_append_t_nscore__string_I60I(nscore__list_t_nscore__string_I10I* lI58I, nscore__list_t_nscore__string_I10I* lpI59I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I20I;
    auto $$return = BSQListOps<nscore__list_t_nscore__string_I10I, BSQString*, RCIncFunctor_BSQString, RCDecFunctor_BSQString, DisplayFunctor_BSQString>::list_append(lI58I, lpI59I);
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

nscore__list_t_nscore__string_I10I* nscore__list__append_t_nscore__string_I61I(nscore__list_t_nscore__string_I10I* _thisI46I, nscore__list_t_nscore__string_I10I* lI58I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    nscore__list_t_nscore__string_I10I* $$return; nscore__list_t_nscore__string_I10I* _tmp_0I42I; nscore__list_t_nscore__string_I10I* ___ir_ret__I38I;

    _tmp_0I42I = nscore__list__s_append_t_nscore__string_I60I(_thisI46I, lI58I, _scope_I20I);
    ___ir_ret__I38I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

nsmain__consoleI19I* nsmain__console__logI62I(nsmain__consoleI19I* _thisI46I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQString* _tmp_3I63I;
    nscore__list_t_nscore__string_I10I* _tmp_0I42I; nscore__list_t_nscore__string_I10I* feedI64I; nscore__list_t_nscore__string_I10I* _tmp_9I57I; nscore__list_t_nscore__string_I10I* _tmp_10I65I;
    nsmain__consoleI19I* $$return; nsmain__consoleI19I* _tmp_6I56I; nsmain__consoleI19I* ___ir_ret__I38I;

    _tmp_3I63I = _thisI46I->nsmain__console_stdinI16I;
    _tmp_0I42I = BSQ_NEW_ADD_SCOPE(_scope_I20I, nscore__list_t_nscore__string_I10I, MIRNominalTypeEnum::nscore__list_t_nscore__string_I10I, { INC_REF_DIRECT(BSQString, _tmp_3I63I) });
    feedI64I = _tmp_0I42I;
    _tmp_9I57I = _thisI46I->nsmain__console_logI18I;
    _tmp_10I65I = nscore__list__append_t_nscore__string_I61I(_tmp_9I57I, feedI64I, _scope_I20I);
    _tmp_6I56I = BSQ_NEW_ADD_SCOPE(_scope_I20I, nsmain__consoleI19I, INC_REF_DIRECT(BSQString, _thisI46I->nsmain__console_stdinI16I), INC_REF_DIRECT(BSQString, _thisI46I->nsmain__console_stdoutI17I), INC_REF_DIRECT(nscore__list_t_nscore__string_I10I, _tmp_10I65I));
    ___ir_ret__I38I = _tmp_6I56I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

int64_t nscore__list__s_size_t_nscore__string_I66I(nscore__list_t_nscore__string_I10I* lI58I) { 
    BSQRefScope _scope_I20I;
    auto $$return = (int64_t)(lI58I->entries.size());
    
    return $$return;
 }

BSQBool nscore__list__front_t_nscore__string___preI67I(nscore__list_t_nscore__string_I10I* _thisI46I)
{
    BSQRefScope _scope_I20I;
    BSQBool $$return, _tmp_0I42I, ___ir_ret__I38I;
    int64_t _tmp_1I40I;

    _tmp_1I40I = nscore__list__s_size_t_nscore__string_I66I(_thisI46I);
    _tmp_0I42I = !EqualFunctor_int64_t{}(_tmp_1I40I, 0);
    ___ir_ret__I38I = _tmp_0I42I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    return $$return;
}

BSQString* nscore__list__s_unsafe_get_t_nscore__string_I69I(nscore__list_t_nscore__string_I10I* lI58I, int64_t iI68I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I20I;
    auto $$return = lI58I->entries[iI68I];
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__list__front_t_nscore__string_I70I(nscore__list_t_nscore__string_I10I* _thisI46I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQBool _tmp_0I42I;
    BSQString* $$return; BSQString* _tmp_1I40I; BSQString* ___ir_ret__I38I;

    _tmp_0I42I = nscore__list__front_t_nscore__string___preI67I(_thisI46I);
    if(_tmp_0I42I) {goto preok_4;} else {goto prefail_3;}

prefail_3:
    BSQ_ABORT("Fail pre-condition", "/usr/home/basilisk/tapedeck-player/tapedeck/BosqueLanguage/impl/bin/core/cpp/list.bsq", 100);

preok_4:
    _tmp_1I40I = nscore__list__s_unsafe_get_t_nscore__string_I69I(_thisI46I, 0, _scope_I20I);
    ___ir_ret__I38I = _tmp_1I40I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQString* nscore__string__s_concatI72I(nscore__list_t_nscore__string_I10I* s1I71I, BSQRefScope& $callerscope$) { 
    BSQRefScope _scope_I20I;
    std::string acc; for(auto iter = s1I71I->entries.cbegin(); iter != s1I71I->entries.cend(); ++iter) { acc.append((*iter)->sdata); }; auto $$return = BSQ_NEW_NO_RC(BSQString, std::move(acc));
    $callerscope$.callReturnDirect($$return);
    return $$return;
 }

BSQString* nscore__string__concatI74I(nscore__list_t_nscore__string_I10I* argsI73I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQBool _tmp_0I42I, _tmp_5I50I;
    int64_t _tmp_1I40I, _tmp_6I56I;
    BSQString* $$return; BSQString* _tmp_11I75I; BSQString* ___ir_ret__I38I; BSQString* _tmp_9I57I; BSQString* ___ir_ret___1I76I; BSQString* ___ir_ret___2I77I; BSQString* ___ir_ret___3I78I;

    _tmp_1I40I = nscore__list__s_size_t_nscore__string_I66I(argsI73I);
    _tmp_0I42I = EqualFunctor_int64_t{}(_tmp_1I40I, 0);
    if(_tmp_0I42I) {goto Lifstmt_0true_4;} else {goto Lifstmt_0false_5;}

Lifstmt_0false_5:
    _tmp_6I56I = nscore__list__s_size_t_nscore__string_I66I(argsI73I);
    _tmp_5I50I = EqualFunctor_int64_t{}(_tmp_6I56I, 1);
    if(_tmp_5I50I) {goto Lifstmt_1true_6;} else {goto Lifstmt_1false_7;}

Lifstmt_1false_7:
    _tmp_11I75I = nscore__string__s_concatI72I(argsI73I, _scope_I20I);
    ___ir_ret__I38I = _tmp_11I75I;
    ___ir_ret___3I78I = ___ir_ret__I38I;
    goto returnassign;

Lifstmt_1true_6:
    _tmp_9I57I = nscore__list__front_t_nscore__string_I70I(argsI73I, _scope_I20I);
    ___ir_ret___1I76I = _tmp_9I57I;
    ___ir_ret___3I78I = ___ir_ret___1I76I;
    goto returnassign;

Lifstmt_0true_4:
    ___ir_ret___2I77I = (&Runtime::STR__0);
    ___ir_ret___3I78I = ___ir_ret___2I77I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret___3I78I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQString* nsmain__mainI79I(BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I20I;
    BSQRecord _tmp_1I40I;
    BSQString* $$return; BSQString* _tmp_2I41I; BSQString* _tmp_3I63I; BSQString* _tmp_41I101I; BSQString* _tmp_36I103I; BSQString* ___ir_ret__I38I;
    nscore__list_t_nscore__string_I10I* _tmp_4I80I; nscore__list_t_nscore__string_I10I* _tmp_40I100I; nscore__list_t_nscore__string_I10I* _tmp_42I102I;
    nsmain__consoleI19I* _tmp_0I42I; nsmain__consoleI19I* ccI81I; nsmain__consoleI19I* _tmp_5I50I; nsmain__consoleI19I* cc_1I82I; nsmain__consoleI19I* _tmp_8I52I; nsmain__consoleI19I* cc_2I83I; nsmain__consoleI19I* _tmp_11I75I; nsmain__consoleI19I* cc_3I84I; nsmain__consoleI19I* _tmp_14I85I; nsmain__consoleI19I* cc_4I86I; nsmain__consoleI19I* _tmp_17I87I; nsmain__consoleI19I* cc_5I88I; nsmain__consoleI19I* _tmp_20I89I; nsmain__consoleI19I* cc_6I90I; nsmain__consoleI19I* _tmp_23I91I; nsmain__consoleI19I* cc_7I92I; nsmain__consoleI19I* _tmp_26I93I; nsmain__consoleI19I* cc_8I94I; nsmain__consoleI19I* _tmp_29I95I; nsmain__consoleI19I* cc_9I96I; nsmain__consoleI19I* _tmp_34I97I; nsmain__consoleI19I* _tmp_35I98I; nsmain__consoleI19I* cc_10I99I;

    _tmp_1I40I = nsmain__console__createI39I(_scope_I20I);
    _tmp_2I41I = BSQ_GET_VALUE_PTR(_tmp_1I40I.atFixed<MIRPropertyEnum::stdin>(), BSQString);
    _tmp_3I63I = BSQ_GET_VALUE_PTR(_tmp_1I40I.atFixed<MIRPropertyEnum::stdout>(), BSQString);
    _tmp_4I80I = nsmain__console__log__consI43I(_scope_I20I);
    _tmp_0I42I = BSQ_NEW_ADD_SCOPE(_scope_I20I, nsmain__consoleI19I, INC_REF_DIRECT(BSQString, _tmp_2I41I), INC_REF_DIRECT(BSQString, _tmp_3I63I), INC_REF_DIRECT(nscore__list_t_nscore__string_I10I, _tmp_4I80I));
    ccI81I = _tmp_0I42I;
    _tmp_5I50I = nsmain__console__writelineI49I(ccI81I, (&Runtime::STR__1), _scope_I20I);
    cc_1I82I = _tmp_5I50I;
    _tmp_8I52I = nsmain__console__writelineI49I(cc_1I82I, (&Runtime::STR__2), _scope_I20I);
    cc_2I83I = _tmp_8I52I;
    _tmp_11I75I = nsmain__console__writelineI49I(cc_2I83I, (&Runtime::STR__3), _scope_I20I);
    cc_3I84I = _tmp_11I75I;
    _tmp_14I85I = nsmain__console__writelineI49I(cc_3I84I, (&Runtime::STR__4), _scope_I20I);
    cc_4I86I = _tmp_14I85I;
    _tmp_17I87I = nsmain__console__writelineI49I(cc_4I86I, (&Runtime::STR__5), _scope_I20I);
    cc_5I88I = _tmp_17I87I;
    _tmp_20I89I = nsmain__console__writelineI49I(cc_5I88I, (&Runtime::STR__6), _scope_I20I);
    cc_6I90I = _tmp_20I89I;
    _tmp_23I91I = nsmain__console__writelineI49I(cc_6I90I, (&Runtime::STR__7), _scope_I20I);
    cc_7I92I = _tmp_23I91I;
    _tmp_26I93I = nsmain__console__writelineI49I(cc_7I92I, (&Runtime::STR__8), _scope_I20I);
    cc_8I94I = _tmp_26I93I;
    _tmp_29I95I = nsmain__console__writelineI49I(cc_8I94I, (&Runtime::STR__9), _scope_I20I);
    cc_9I96I = _tmp_29I95I;
    _tmp_34I97I = nsmain__console__readlineI55I(cc_9I96I, _scope_I20I);
    _tmp_35I98I = nsmain__console__logI62I(_tmp_34I97I, _scope_I20I);
    cc_10I99I = _tmp_35I98I;
    _tmp_40I100I = cc_10I99I->nsmain__console_logI18I;
    _tmp_41I101I = nscore__list__front_t_nscore__string_I70I(_tmp_40I100I, _scope_I20I);
    _tmp_42I102I = BSQ_NEW_ADD_SCOPE(_scope_I20I, nscore__list_t_nscore__string_I10I, MIRNominalTypeEnum::nscore__list_t_nscore__string_I10I, { INC_REF_DIRECT(BSQString, (&Runtime::STR__10)), INC_REF_DIRECT(BSQString, _tmp_41I101I) });
    _tmp_36I103I = nscore__string__concatI74I(_tmp_42I102I, _scope_I20I);
    ___ir_ret__I38I = _tmp_36I103I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I38I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
#pragma clang diagnostic pop
}
}

