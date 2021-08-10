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
  static BSQString STR__3;
  static BSQString STR__4;
  static BSQString STR__5;
  static BSQString STR__6;
  static BSQString STR__7;
  static BSQString STR__8;





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
#pragma clang diagnostic ignored "-Wpessimizing-move"
BSQString Runtime::STR__0("", 1);
  BSQString Runtime::STR__1("block", 1);
  BSQString Runtime::STR__2("yld", 1);
  BSQString Runtime::STR__3("tick", 1);
  BSQString Runtime::STR__4("detach", 1);
  BSQString Runtime::STR__5("new", 1);
  BSQString Runtime::STR__6("BSQ TapeDeck", 1);
  BSQString Runtime::STR__7("Home", 1);
  BSQString Runtime::STR__8("Wagner", 1);
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
class Boxed_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I;
class nscore__map_k_nsmain__event__v_nscore__int_I11I;
class nsmain__tapedeckI26I;

/*type decls*/
class nscore__mapentry_k_nsmain__event__v_nscore__int_I16I
{
public:
    BSQEnum nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I;
    int64_t nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I;

    nscore__mapentry_k_nsmain__event__v_nscore__int_I16I() { ; }
    nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(BSQEnum key, int64_t value) : nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I(key), nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I(value) { ; }
    nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(const nscore__mapentry_k_nsmain__event__v_nscore__int_I16I& src) = default;
    nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I&& src) = default;

    nscore__mapentry_k_nsmain__event__v_nscore__int_I16I& operator=(const nscore__mapentry_k_nsmain__event__v_nscore__int_I16I& src) = default;
    nscore__mapentry_k_nsmain__event__v_nscore__int_I16I& operator=(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I&& src) = default;

    std::string display() const;

};struct RCIncFunctor_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I{
  inline nscore__mapentry_k_nsmain__event__v_nscore__int_I16I operator()(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I tt) const
  {
    
    return tt;
  }
};

struct RCDecFunctor_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I{
  inline void operator()(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I tt) const
  {
    ;    
;
  }
};

struct RCReturnFunctor_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I{
  inline void operator()(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I& tt, BSQRefScope& scope) const
  {
    ;    
;
  }
};

struct DisplayFunctor_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I{
  std::string operator()(const nscore__mapentry_k_nsmain__event__v_nscore__int_I16I& tt) const
  {
    return tt.display();  }
};

class nscore__map_k_nsmain__event__v_nscore__int_I11I : public BSQMap<BSQEnum, RCDecFunctor_BSQEnum, DisplayFunctor_BSQEnum, LessFunctor_BSQEnum, EqualFunctor_BSQEnum, int64_t, RCDecFunctor_int64_t, DisplayFunctor_int64_t>
{
public:
nscore__map_k_nsmain__event__v_nscore__int_I11I(MIRNominalTypeEnum ntype) : BSQMap<BSQEnum, RCDecFunctor_BSQEnum, DisplayFunctor_BSQEnum, LessFunctor_BSQEnum, EqualFunctor_BSQEnum, int64_t, RCDecFunctor_int64_t, DisplayFunctor_int64_t>(ntype) { ; }
nscore__map_k_nsmain__event__v_nscore__int_I11I(MIRNominalTypeEnum ntype, std::vector<MEntry<BSQEnum, int64_t>>&& vals) : BSQMap<BSQEnum, RCDecFunctor_BSQEnum, DisplayFunctor_BSQEnum, LessFunctor_BSQEnum, EqualFunctor_BSQEnum, int64_t, RCDecFunctor_int64_t, DisplayFunctor_int64_t>(ntype, std::move(vals)) { ; }
virtual ~nscore__map_k_nsmain__event__v_nscore__int_I11I() { ; }
};

class Boxed_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I : public BSQBoxedObject<nscore__mapentry_k_nsmain__event__v_nscore__int_I16I, RCDecFunctor_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I>
{
public:
    Boxed_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(const nscore__mapentry_k_nsmain__event__v_nscore__int_I16I& bval) : BSQBoxedObject(MIRNominalTypeEnum::nscore__mapentry_k_nsmain__event__v_nscore__int_I16I, bval) { ; }
    std::string display() const;

};
class nsmain__tapedeckI26I : public BSQObject
{
public:
    BSQString* nsmain__tapedeck_nameI21I;
    BSQString* nsmain__tapedeck_locationI22I;
    int64_t nsmain__tapedeck_ageI23I;
    BSQString* nsmain__tapedeck_musicI24I;
    BSQBool nsmain__tapedeck_stereoI25I;

    nsmain__tapedeckI26I(BSQString* name, BSQString* location, int64_t age, BSQString* music, BSQBool stereo) : BSQObject(MIRNominalTypeEnum::nsmain__tapedeckI26I), nsmain__tapedeck_nameI21I(name), nsmain__tapedeck_locationI22I(location), nsmain__tapedeck_ageI23I(age), nsmain__tapedeck_musicI24I(music), nsmain__tapedeck_stereoI25I(stereo) { ; }
    virtual ~nsmain__tapedeckI26I() { ; }

    virtual void destroy() { BSQRef::decrementDirect(this->nsmain__tapedeck_nameI21I); BSQRef::decrementDirect(this->nsmain__tapedeck_locationI22I); BSQRef::decrementDirect(this->nsmain__tapedeck_musicI24I); }

    std::string display() const;
};

/*ephemeral decls*/
class __nscore__int__nscore__int__I78I
{
public:
    int64_t entry_0;
    int64_t entry_1;

    __nscore__int__nscore__int__I78I() { ; }

    __nscore__int__nscore__int__I78I(int64_t e0, int64_t e1) : entry_0(e0), entry_1(e1) { ; }

    __nscore__int__nscore__int__I78I(const __nscore__int__nscore__int__I78I& src) = default;
    __nscore__int__nscore__int__I78I(__nscore__int__nscore__int__I78I&& src) = default;
    __nscore__int__nscore__int__I78I& operator=(const __nscore__int__nscore__int__I78I& src) = default;
    __nscore__int__nscore__int__I78I& operator=(__nscore__int__nscore__int__I78I&& src) = default;
    std::string display() const
    {
        BSQRefScope _scope_I15I;
        return std::string("(| ") + diagnostic_format(((Value)BSQ_ENCODE_VALUE_TAGGED_INT(this->entry_0))) + std::string(", ") + diagnostic_format(((Value)BSQ_ENCODE_VALUE_TAGGED_INT(this->entry_1))) + std::string(" |)");
    }

    void processForCallReturn(BSQRefScope& scope)
    {
            }
};

/*forward vable decls*/


/*forward function decls*/
BSQBool nsmain__gettapedeck__preI48I(BSQString* nameI43I, BSQString* locationI44I, int64_t ageI45I, BSQString* musicI46I, BSQBool stereoI47I);
BSQBool nsmain__tapedeck___invariant_directI72I(BSQString* _nameI67I, BSQString* _locationI68I, int64_t _ageI69I, BSQString* _musicI70I, BSQBool _stereoI71I);
BSQBool nsmain__tapedeck____invariantI73I(BSQString* _nameI67I, BSQString* _locationI68I, int64_t _ageI69I, BSQString* _musicI70I, BSQBool _stereoI71I);
nsmain__tapedeckI26I* nsmain__gettapedeckI76I(BSQString* nameI43I, BSQString* locationI44I, int64_t ageI45I, BSQString* musicI46I, BSQBool stereoI47I, BSQRefScope& $callerscope$);
__nscore__int__nscore__int__I78I nsmain__mktimeI79I(int64_t tI77I, BSQRefScope& $callerscope$);
BSQEnum nsmain__event__createI81I(int64_t valueI80I);
BSQEnum nsmain__event__detach__consI82I();
BSQEnum nsmain__event__new__consI83I();
BSQEnum nsmain__event__tick__consI84I();
BSQEnum nsmain__event__yld__consI85I();
BSQEnum nsmain__event__block__consI86I();
BSQEnum nsmain__event__unblock__consI87I();
BSQEnum nsmain__event__schedule__consI88I();
BSQEnum nsmain__event__entry__consI89I();
BSQEnum nsmain__event__exit__consI90I();
BSQEnum nsmain__event__balance__consI91I();
BSQBool nscore__map__s_has_key_k_nsmain__event__v_nscore__int_I94I(nscore__map_k_nsmain__event__v_nscore__int_I11I* mI92I, BSQEnum keyI93I);
BSQBool nscore__map__get_k_nsmain__event__v_nscore__int___preI96I(nscore__map_k_nsmain__event__v_nscore__int_I11I* _thisI95I, BSQEnum keyI93I);
int64_t nscore__map__s_at_val_k_nsmain__event__v_nscore__int_I97I(nscore__map_k_nsmain__event__v_nscore__int_I11I* mI92I, BSQEnum keyI93I);
int64_t nscore__map__get_k_nsmain__event__v_nscore__int_I98I(nscore__map_k_nsmain__event__v_nscore__int_I11I* _thisI95I, BSQEnum keyI93I);
BSQString* nsmain__handlerI100I(BSQEnum eventI99I, BSQRefScope& $callerscope$);
BSQString* nsmain__mainI142I(BSQRefScope& $callerscope$);

/*typecheck decls*/


/*vable decls*/


/*function decls*/
std::string nscore__mapentry_k_nsmain__event__v_nscore__int_I16I::display() const
    {
        BSQRefScope _scope_I15I;
        return std::string("NSCore::MapEntry<K=NSMain::Event, V=NSCore::Int>{ ") + diagnostic_format(((Value)BSQ_NEW_ADD_SCOPE(_scope_I15I, Boxed_BSQEnum, MIRNominalTypeEnum::nsmain__eventI12I, RCIncFunctor_BSQEnum{}(this->nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I)))) + std::string(", ") + diagnostic_format(((Value)BSQ_ENCODE_VALUE_TAGGED_INT(this->nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I))) + std::string(" }");
    }
std::string Boxed_nscore__mapentry_k_nsmain__event__v_nscore__int_I16I::display() const {return this->bval.display(); }
std::string nsmain__tapedeckI26I::display() const
    {
        BSQRefScope _scope_I15I;
        return std::string("NSMain::TapeDeck{ ") + diagnostic_format(((Value)this->nsmain__tapedeck_nameI21I)) + std::string(", ") + diagnostic_format(((Value)this->nsmain__tapedeck_locationI22I)) + std::string(", ") + diagnostic_format(((Value)BSQ_ENCODE_VALUE_TAGGED_INT(this->nsmain__tapedeck_ageI23I))) + std::string(", ") + diagnostic_format(((Value)this->nsmain__tapedeck_musicI24I)) + std::string(", ") + diagnostic_format(((Value)BSQ_ENCODE_VALUE_BOOL(this->nsmain__tapedeck_stereoI25I))) + std::string(" }");
    }
BSQBool nsmain__gettapedeck__preI48I(BSQString* nameI43I, BSQString* locationI44I, int64_t ageI45I, BSQString* musicI46I, BSQBool stereoI47I)
{
    BSQRefScope _scope_I15I;
    BSQBool $$return, _tmp_4I49I, _tmp_3I50I, _tmp_7I51I, _tmp_3_1I52I, _tmp_3_2I53I, _tmp_2I54I, _tmp_10I55I, _tmp_2_1I56I, _tmp_2_2I57I, _tmp_1I58I, _tmp_13I59I, _tmp_1_1I60I, _tmp_1_2I61I, _tmp_0I62I, _tmp_16I63I, _tmp_0_1I64I, _tmp_0_2I65I, ___ir_ret__I66I;

    _tmp_4I49I = !EqualFunctor_BSQString{}(nameI43I, (&Runtime::STR__0));
    if(_tmp_4I49I) {goto Llogic_rest_5;} else {goto Llogic_shortcircuit_4;}

Llogic_shortcircuit_4:
    _tmp_3I50I = BSQFALSE;
    _tmp_3_2I53I = _tmp_3I50I;
    goto Llogic_done_3;

Llogic_rest_5:
    _tmp_7I51I = !EqualFunctor_BSQString{}(locationI44I, (&Runtime::STR__0));
    _tmp_3_1I52I = _tmp_7I51I;
    _tmp_3_2I53I = _tmp_3_1I52I;
    goto Llogic_done_3;

Llogic_done_3:
    if(_tmp_3_2I53I) {goto Llogic_rest_8;} else {goto Llogic_shortcircuit_7;}

Llogic_shortcircuit_7:
    _tmp_2I54I = BSQFALSE;
    _tmp_2_2I57I = _tmp_2I54I;
    goto Llogic_done_6;

Llogic_rest_8:
    _tmp_10I55I = !EqualFunctor_int64_t{}(ageI45I, 0);
    _tmp_2_1I56I = _tmp_10I55I;
    _tmp_2_2I57I = _tmp_2_1I56I;
    goto Llogic_done_6;

Llogic_done_6:
    if(_tmp_2_2I57I) {goto Llogic_rest_11;} else {goto Llogic_shortcircuit_10;}

Llogic_shortcircuit_10:
    _tmp_1I58I = BSQFALSE;
    _tmp_1_2I61I = _tmp_1I58I;
    goto Llogic_done_9;

Llogic_rest_11:
    _tmp_13I59I = !EqualFunctor_BSQString{}(musicI46I, (&Runtime::STR__0));
    _tmp_1_1I60I = _tmp_13I59I;
    _tmp_1_2I61I = _tmp_1_1I60I;
    goto Llogic_done_9;

Llogic_done_9:
    if(_tmp_1_2I61I) {goto Llogic_rest_14;} else {goto Llogic_shortcircuit_13;}

Llogic_shortcircuit_13:
    _tmp_0I62I = BSQFALSE;
    _tmp_0_2I65I = _tmp_0I62I;
    goto Llogic_done_12;

Llogic_rest_14:
    _tmp_16I63I = !EqualFunctor_BSQBool{}(stereoI47I, BSQFALSE);
    _tmp_0_1I64I = _tmp_16I63I;
    _tmp_0_2I65I = _tmp_0_1I64I;
    goto Llogic_done_12;

Llogic_done_12:
    ___ir_ret__I66I = _tmp_0_2I65I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQBool nsmain__tapedeck___invariant_directI72I(BSQString* _nameI67I, BSQString* _locationI68I, int64_t _ageI69I, BSQString* _musicI70I, BSQBool _stereoI71I)
{
    BSQRefScope _scope_I15I;
    BSQBool $$return, _tmp_4I49I, _tmp_3I50I, _tmp_7I51I, _tmp_3_1I52I, _tmp_3_2I53I, _tmp_2I54I, _tmp_10I55I, _tmp_2_1I56I, _tmp_2_2I57I, _tmp_1I58I, _tmp_13I59I, _tmp_1_1I60I, _tmp_1_2I61I, _tmp_0I62I, _tmp_16I63I, _tmp_0_1I64I, _tmp_0_2I65I, ___ir_ret__I66I;

    _tmp_4I49I = !EqualFunctor_BSQString{}(_nameI67I, (&Runtime::STR__0));
    if(_tmp_4I49I) {goto Llogic_rest_5;} else {goto Llogic_shortcircuit_4;}

Llogic_shortcircuit_4:
    _tmp_3I50I = BSQFALSE;
    _tmp_3_2I53I = _tmp_3I50I;
    goto Llogic_done_3;

Llogic_rest_5:
    _tmp_7I51I = !EqualFunctor_BSQString{}(_locationI68I, (&Runtime::STR__0));
    _tmp_3_1I52I = _tmp_7I51I;
    _tmp_3_2I53I = _tmp_3_1I52I;
    goto Llogic_done_3;

Llogic_done_3:
    if(_tmp_3_2I53I) {goto Llogic_rest_8;} else {goto Llogic_shortcircuit_7;}

Llogic_shortcircuit_7:
    _tmp_2I54I = BSQFALSE;
    _tmp_2_2I57I = _tmp_2I54I;
    goto Llogic_done_6;

Llogic_rest_8:
    _tmp_10I55I = !EqualFunctor_int64_t{}(_ageI69I, 0);
    _tmp_2_1I56I = _tmp_10I55I;
    _tmp_2_2I57I = _tmp_2_1I56I;
    goto Llogic_done_6;

Llogic_done_6:
    if(_tmp_2_2I57I) {goto Llogic_rest_11;} else {goto Llogic_shortcircuit_10;}

Llogic_shortcircuit_10:
    _tmp_1I58I = BSQFALSE;
    _tmp_1_2I61I = _tmp_1I58I;
    goto Llogic_done_9;

Llogic_rest_11:
    _tmp_13I59I = !EqualFunctor_BSQString{}(_musicI70I, (&Runtime::STR__0));
    _tmp_1_1I60I = _tmp_13I59I;
    _tmp_1_2I61I = _tmp_1_1I60I;
    goto Llogic_done_9;

Llogic_done_9:
    if(_tmp_1_2I61I) {goto Llogic_rest_14;} else {goto Llogic_shortcircuit_13;}

Llogic_shortcircuit_13:
    _tmp_0I62I = BSQFALSE;
    _tmp_0_2I65I = _tmp_0I62I;
    goto Llogic_done_12;

Llogic_rest_14:
    _tmp_16I63I = !EqualFunctor_BSQBool{}(_stereoI71I, BSQFALSE);
    _tmp_0_1I64I = _tmp_16I63I;
    _tmp_0_2I65I = _tmp_0_1I64I;
    goto Llogic_done_12;

Llogic_done_12:
    ___ir_ret__I66I = _tmp_0_2I65I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQBool nsmain__tapedeck____invariantI73I(BSQString* _nameI67I, BSQString* _locationI68I, int64_t _ageI69I, BSQString* _musicI70I, BSQBool _stereoI71I)
{
    BSQRefScope _scope_I15I;
    BSQBool $$return, _tmp_0I62I, _tmp_0_1I64I, ___ir_ret__I66I, ___ir_ret___1I74I, ___ir_ret___2I75I;

    _tmp_0I62I = BSQTRUE;
    _tmp_0_1I64I = nsmain__tapedeck___invariant_directI72I(_nameI67I, _locationI68I, _ageI69I, _musicI70I, _stereoI71I);
    if(_tmp_0_1I64I) {goto next_4;} else {goto failure_3;}

failure_3:
    ___ir_ret__I66I = _tmp_0_1I64I;
    ___ir_ret___2I75I = ___ir_ret__I66I;
    goto returnassign;

next_4:
    ___ir_ret___1I74I = _tmp_0_1I64I;
    ___ir_ret___2I75I = ___ir_ret___1I74I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret___2I75I;
    goto exit;

exit:
    return $$return;
}

nsmain__tapedeckI26I* nsmain__gettapedeckI76I(BSQString* nameI43I, BSQString* locationI44I, int64_t ageI45I, BSQString* musicI46I, BSQBool stereoI47I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I15I;
    BSQBool _tmp_0I62I, _tmp_7I51I;
    nsmain__tapedeckI26I* $$return; nsmain__tapedeckI26I* _tmp_1I58I; nsmain__tapedeckI26I* ___ir_ret__I66I;

    _tmp_0I62I = nsmain__gettapedeck__preI48I(nameI43I, locationI44I, ageI45I, musicI46I, stereoI47I);
    if(_tmp_0I62I) {goto preok_4;} else {goto prefail_3;}

prefail_3:
    BSQ_ABORT("Fail pre-condition", "tapedeck.bsq", 34);

preok_4:
    _tmp_1I58I = BSQ_NEW_ADD_SCOPE(_scope_I15I, nsmain__tapedeckI26I, INC_REF_DIRECT(BSQString, nameI43I), INC_REF_DIRECT(BSQString, locationI44I), ageI45I, INC_REF_DIRECT(BSQString, musicI46I), stereoI47I);
    _tmp_7I51I = nsmain__tapedeck____invariantI73I(_tmp_1I58I->nsmain__tapedeck_nameI21I, _tmp_1I58I->nsmain__tapedeck_locationI22I, _tmp_1I58I->nsmain__tapedeck_ageI23I, _tmp_1I58I->nsmain__tapedeck_musicI24I, _tmp_1I58I->nsmain__tapedeck_stereoI25I);
    if(_tmp_7I51I) {goto invariantok_5;} else {goto invariantfail_6;}

invariantfail_6:
    BSQ_ABORT("Invariant Failure", "tapedeck.bsq", 35);

invariantok_5:
    ___ir_ret__I66I = _tmp_1I58I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

__nscore__int__nscore__int__I78I nsmain__mktimeI79I(int64_t tI77I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I15I;
    int64_t _tmp_0I62I, ___ir_ret__I66I;
    __nscore__int__nscore__int__I78I $$return; __nscore__int__nscore__int__I78I _tmp_4I49I;

    if(__builtin_add_overflow(tI77I, 4, &_tmp_0I62I) || INT_OOF_BOUNDS(_tmp_0I62I)) { BSQ_ABORT("Int Overflow", "tapedeck.bsq", 49); }
    tI77I = _tmp_0I62I;
    ___ir_ret__I66I = tI77I;
    goto returnassign;

returnassign:
    _tmp_4I49I = __nscore__int__nscore__int__I78I{___ir_ret__I66I, tI77I};
    $$return = _tmp_4I49I;
    goto exit;

exit:
    ($$return).processForCallReturn($callerscope$);
    return $$return;
}

BSQEnum nsmain__event__createI81I(int64_t valueI80I) { 
    BSQRefScope _scope_I15I;
    auto $$return = BSQEnum{ (uint32_t)valueI80I, MIRNominalTypeEnum::nsmain__eventI12I };
    
    return $$return;
 }

BSQEnum nsmain__event__detach__consI82I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(1);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__new__consI83I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(0);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__tick__consI84I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(2);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__yld__consI85I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(3);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__block__consI86I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(4);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__unblock__consI87I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(5);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__schedule__consI88I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(6);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__entry__consI89I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(7);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__exit__consI90I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(8);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQEnum nsmain__event__balance__consI91I()
{
    BSQRefScope _scope_I15I;
    BSQEnum $$return; BSQEnum _tmp_0I62I; BSQEnum ___ir_ret__I66I;

    _tmp_0I62I = nsmain__event__createI81I(9);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQBool nscore__map__s_has_key_k_nsmain__event__v_nscore__int_I94I(nscore__map_k_nsmain__event__v_nscore__int_I11I* mI92I, BSQEnum keyI93I) { 
    BSQRefScope _scope_I15I;
    auto $$return = mI92I->hasKey(keyI93I);
    
    return $$return;
 }

BSQBool nscore__map__get_k_nsmain__event__v_nscore__int___preI96I(nscore__map_k_nsmain__event__v_nscore__int_I11I* _thisI95I, BSQEnum keyI93I)
{
    BSQRefScope _scope_I15I;
    BSQBool $$return, _tmp_0I62I, ___ir_ret__I66I;

    _tmp_0I62I = nscore__map__s_has_key_k_nsmain__event__v_nscore__int_I94I(_thisI95I, keyI93I);
    ___ir_ret__I66I = _tmp_0I62I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

int64_t nscore__map__s_at_val_k_nsmain__event__v_nscore__int_I97I(nscore__map_k_nsmain__event__v_nscore__int_I11I* mI92I, BSQEnum keyI93I) { 
    BSQRefScope _scope_I15I;
    auto $$return = mI92I->getValue(keyI93I);
    
    return $$return;
 }

int64_t nscore__map__get_k_nsmain__event__v_nscore__int_I98I(nscore__map_k_nsmain__event__v_nscore__int_I11I* _thisI95I, BSQEnum keyI93I)
{
    BSQRefScope _scope_I15I;
    BSQBool _tmp_0I62I;
    int64_t $$return, _tmp_1I58I, ___ir_ret__I66I;

    _tmp_0I62I = nscore__map__get_k_nsmain__event__v_nscore__int___preI96I(_thisI95I, keyI93I);
    if(_tmp_0I62I) {goto preok_4;} else {goto prefail_3;}

prefail_3:
    BSQ_ABORT("Fail pre-condition", "/usr/home/basilisk/tapedeck-player/tapedeck/BosqueLanguage/impl/bin/core/cpp/map.bsq", 94);

preok_4:
    _tmp_1I58I = nscore__map__s_at_val_k_nsmain__event__v_nscore__int_I97I(_thisI95I, keyI93I);
    ___ir_ret__I66I = _tmp_1I58I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    return $$return;
}

BSQString* nsmain__handlerI100I(BSQEnum eventI99I, BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I15I;
    BSQBool _tmp_37I116I, _tmp_35I117I, _tmp_39I118I, _tmp_35_1I119I, _tmp_42I120I, _tmp_40I121I, _tmp_44I122I, _tmp_40_1I123I, _tmp_47I124I, _tmp_45I125I, _tmp_49I126I, _tmp_45_1I127I, _tmp_52I128I, _tmp_50I129I, _tmp_54I130I, _tmp_50_1I131I, _tmp_57I132I, _tmp_55I133I, _tmp_59I134I, _tmp_55_1I135I;
    int64_t _tmp_32I115I;
    BSQEnum _tmp_2I54I; BSQEnum _tmp_5I101I; BSQEnum _tmp_8I102I; BSQEnum _tmp_11I103I; BSQEnum _tmp_14I104I; BSQEnum _tmp_17I105I; BSQEnum _tmp_20I106I; BSQEnum _tmp_23I108I; BSQEnum _tmp_26I110I; BSQEnum _tmp_29I112I;
    BSQString* $$return; BSQString* _tmp_31I136I; BSQString* _tmp_31_1I137I; BSQString* _tmp_31_2I138I; BSQString* _tmp_31_3I139I; BSQString* _tmp_31_4I140I; BSQString* _tmp_31_5I141I; BSQString* ___ir_ret__I66I;
    nscore__map_k_nsmain__event__v_nscore__int_I11I* _tmp_0I62I; nscore__map_k_nsmain__event__v_nscore__int_I11I* evtmapI114I;
    nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_1I58I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_4I49I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_7I51I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_10I55I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_13I59I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_16I63I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_19I107I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_22I109I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_25I111I; nscore__mapentry_k_nsmain__event__v_nscore__int_I16I _tmp_28I113I;

    _tmp_2I54I = nsmain__event__new__consI83I();
    _tmp_1I58I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_2I54I, 1));
    _tmp_5I101I = nsmain__event__detach__consI82I();
    _tmp_4I49I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_5I101I, 2));
    _tmp_8I102I = nsmain__event__tick__consI84I();
    _tmp_7I51I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_8I102I, 3));
    _tmp_11I103I = nsmain__event__yld__consI85I();
    _tmp_10I55I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_11I103I, 4));
    _tmp_14I104I = nsmain__event__block__consI86I();
    _tmp_13I59I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_14I104I, 5));
    _tmp_17I105I = nsmain__event__unblock__consI87I();
    _tmp_16I63I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_17I105I, 6));
    _tmp_20I106I = nsmain__event__schedule__consI88I();
    _tmp_19I107I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_20I106I, 7));
    _tmp_23I108I = nsmain__event__entry__consI89I();
    _tmp_22I109I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_23I108I, 8));
    _tmp_26I110I = nsmain__event__exit__consI90I();
    _tmp_25I111I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_26I110I, 9));
    _tmp_29I112I = nsmain__event__balance__consI91I();
    _tmp_28I113I = std::move(nscore__mapentry_k_nsmain__event__v_nscore__int_I16I(_tmp_29I112I, 10));
    _tmp_0I62I = BSQ_NEW_ADD_SCOPE(_scope_I15I, nscore__map_k_nsmain__event__v_nscore__int_I11I, MIRNominalTypeEnum::nscore__map_k_nsmain__event__v_nscore__int_I11I, BSQMap<BSQEnum, RCDecFunctor_BSQEnum, DisplayFunctor_BSQEnum, LessFunctor_BSQEnum, EqualFunctor_BSQEnum, int64_t, RCDecFunctor_int64_t, DisplayFunctor_int64_t>::processSingletonMapInit<RCIncFunctor_BSQEnum, RCIncFunctor_int64_t>({ MEntry<BSQEnum, int64_t>{_tmp_1I58I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_1I58I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_4I49I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_4I49I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_7I51I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_7I51I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_10I55I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_10I55I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_13I59I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_13I59I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_16I63I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_16I63I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_19I107I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_19I107I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_22I109I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_22I109I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_25I111I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_25I111I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I},MEntry<BSQEnum, int64_t>{_tmp_28I113I.nscore__mapentry_k_nsmain__event__v_nscore__int__keyI13I, _tmp_28I113I.nscore__mapentry_k_nsmain__event__v_nscore__int__valueI14I} }));
    evtmapI114I = _tmp_0I62I;
    _tmp_32I115I = nscore__map__get_k_nsmain__event__v_nscore__int_I98I(evtmapI114I, eventI99I);
    _tmp_37I116I = true;
    if(_tmp_37I116I) {goto match0_sceq_7;} else {goto Lswitchexp_0next_4;}

match0_sceq_7:
    _tmp_35I117I = BSQTRUE;
    _tmp_39I118I = EqualFunctor_int64_t{}(_tmp_32I115I, 1);
    _tmp_35_1I119I = _tmp_39I118I;
    if(_tmp_39I118I) {goto match0_test_8;} else {goto match0_scfill_6;}

match0_test_8:
    goto match0_scfill_6;

match0_scfill_6:
    if(_tmp_35_1I119I) {goto Lswitchexp_0action_5;} else {goto Lswitchexp_0next_4;}

Lswitchexp_0next_4:
    _tmp_42I120I = true;
    if(_tmp_42I120I) {goto match1_sceq_12;} else {goto Lswitchexp_1next_9;}

match1_sceq_12:
    _tmp_40I121I = BSQTRUE;
    _tmp_44I122I = EqualFunctor_int64_t{}(_tmp_32I115I, 2);
    _tmp_40_1I123I = _tmp_44I122I;
    if(_tmp_44I122I) {goto match0_test_13;} else {goto match1_scfill_11;}

match0_test_13:
    goto match1_scfill_11;

match1_scfill_11:
    if(_tmp_40_1I123I) {goto Lswitchexp_1action_10;} else {goto Lswitchexp_1next_9;}

Lswitchexp_1next_9:
    _tmp_47I124I = true;
    if(_tmp_47I124I) {goto match2_sceq_17;} else {goto Lswitchexp_2next_14;}

match2_sceq_17:
    _tmp_45I125I = BSQTRUE;
    _tmp_49I126I = EqualFunctor_int64_t{}(_tmp_32I115I, 3);
    _tmp_45_1I127I = _tmp_49I126I;
    if(_tmp_49I126I) {goto match0_test_18;} else {goto match2_scfill_16;}

match0_test_18:
    goto match2_scfill_16;

match2_scfill_16:
    if(_tmp_45_1I127I) {goto Lswitchexp_2action_15;} else {goto Lswitchexp_2next_14;}

Lswitchexp_2next_14:
    _tmp_52I128I = true;
    if(_tmp_52I128I) {goto match3_sceq_22;} else {goto Lswitchexp_3next_19;}

match3_sceq_22:
    _tmp_50I129I = BSQTRUE;
    _tmp_54I130I = EqualFunctor_int64_t{}(_tmp_32I115I, 4);
    _tmp_50_1I131I = _tmp_54I130I;
    if(_tmp_54I130I) {goto match0_test_23;} else {goto match3_scfill_21;}

match0_test_23:
    goto match3_scfill_21;

match3_scfill_21:
    if(_tmp_50_1I131I) {goto Lswitchexp_3action_20;} else {goto Lswitchexp_3next_19;}

Lswitchexp_3next_19:
    _tmp_57I132I = true;
    if(_tmp_57I132I) {goto match4_sceq_27;} else {goto Lswitchexp_4next_24;}

match4_sceq_27:
    _tmp_55I133I = BSQTRUE;
    _tmp_59I134I = EqualFunctor_int64_t{}(_tmp_32I115I, 5);
    _tmp_55_1I135I = _tmp_59I134I;
    if(_tmp_59I134I) {goto match0_test_28;} else {goto match4_scfill_26;}

match0_test_28:
    goto match4_scfill_26;

match4_scfill_26:
    if(_tmp_55_1I135I) {goto Lswitchexp_4action_25;} else {goto Lswitchexp_4next_24;}

Lswitchexp_4next_24:
    BSQ_ABORT("exhaustive", "tapedeck.bsq", 104);

Lswitchexp_4action_25:
    _tmp_31I136I = (&Runtime::STR__1);
    _tmp_31_5I141I = _tmp_31I136I;
    goto Lswitchexp_done_3;

Lswitchexp_3action_20:
    _tmp_31_1I137I = (&Runtime::STR__2);
    _tmp_31_5I141I = _tmp_31_1I137I;
    goto Lswitchexp_done_3;

Lswitchexp_2action_15:
    _tmp_31_2I138I = (&Runtime::STR__3);
    _tmp_31_5I141I = _tmp_31_2I138I;
    goto Lswitchexp_done_3;

Lswitchexp_1action_10:
    _tmp_31_3I139I = (&Runtime::STR__4);
    _tmp_31_5I141I = _tmp_31_3I139I;
    goto Lswitchexp_done_3;

Lswitchexp_0action_5:
    _tmp_31_4I140I = (&Runtime::STR__5);
    _tmp_31_5I141I = _tmp_31_4I140I;
    goto Lswitchexp_done_3;

Lswitchexp_done_3:
    ___ir_ret__I66I = _tmp_31_5I141I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}

BSQString* nsmain__mainI142I(BSQRefScope& $callerscope$)
{
    BSQRefScope _scope_I15I;
    int64_t tvI144I, _tmp_7I51I, _tmp_10I55I, tv_1I146I, timeI147I;
    __nscore__int__nscore__int__I78I _tmp_9I145I;
    BSQEnum _tmp_12I148I;
    BSQString* $$return; BSQString* _tmp_11I103I; BSQString* valI149I; BSQString* _tmp_18I150I; BSQString* ___ir_ret__I66I;
    nsmain__tapedeckI26I* _tmp_0I62I; nsmain__tapedeckI26I* hometapedeckI143I;

    _tmp_0I62I = nsmain__gettapedeckI76I((&Runtime::STR__6), (&Runtime::STR__7), 3, (&Runtime::STR__8), BSQTRUE, _scope_I15I);
    hometapedeckI143I = _tmp_0I62I;
    tvI144I = 123456;
    _tmp_9I145I = nsmain__mktimeI79I(tvI144I, _scope_I15I);
    _tmp_7I51I = _tmp_9I145I.entry_0;
    _tmp_10I55I = _tmp_9I145I.entry_1;
    tv_1I146I = _tmp_10I55I;
    timeI147I = _tmp_7I51I;
    _tmp_12I148I = nsmain__event__detach__consI82I();
    _tmp_11I103I = nsmain__handlerI100I(_tmp_12I148I, _scope_I15I);
    valI149I = _tmp_11I103I;
    { std::cout << diagnostic_format(((Value)valI149I)) << "\n"; }
    { std::cout << diagnostic_format(((Value)BSQ_ENCODE_VALUE_TAGGED_INT(timeI147I))) << "\n"; }
    { std::cout << diagnostic_format(((Value)hometapedeckI143I)) << "\n"; }
    _tmp_18I150I = hometapedeckI143I->nsmain__tapedeck_nameI21I;
    ___ir_ret__I66I = _tmp_18I150I;
    goto returnassign;

returnassign:
    $$return = ___ir_ret__I66I;
    goto exit;

exit:
    $callerscope$.callReturnDirect($$return);
    return $$return;
}
#pragma clang diagnostic pop
}

