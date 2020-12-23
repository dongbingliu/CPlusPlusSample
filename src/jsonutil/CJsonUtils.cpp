/**
 * <pre>
 *     @ author : dongbingliu(柳洞兵)
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2020/12/23
 *     @ desc   :
 *     version: 1.0
 * </pre>
 */
#include <cstdio>
#include <string>
#include <ctype.h>
#include <rapidjson/document.h>
#include "CJsonUtils.h"

using namespace std;
using namespace rapidjson;

//静态空值对象，用于构造空值的const CJobject对象
static Value gNullValue(kNullType);

/****************************************************
 * CJson的对象类
 ***************************************************/
CJsonUtils::CJsonUtils() : m_bRoot(true), m_pDoc(new Document()), m_pValue(new Value(kObjectType))
{

}

CJsonUtils::CJsonUtils(Document* pDoc, Value* pValue) : m_bRoot(false), m_pDoc(pDoc), m_pValue(pValue)
{
}

CJsonUtils::CJsonUtils(const CJsonUtils& other) : m_bRoot(false), m_pDoc(other.m_pDoc), m_pValue(other.m_pValue)
{
}

CJsonUtils::~CJsonUtils()
{
    if (true == m_bRoot)
    {
        delete m_pDoc;
        delete m_pValue;
    }
}

CJsonUtils& CJsonUtils::operator=(const CJsonUtils& Other)
{
    m_pValue->CopyFrom(*Other.m_pValue, m_pDoc->GetAllocator());
    return *this;
}

bool CJsonUtils::Parse(const char* strJsonText)
{
    if (false == m_bRoot)
        return false;

    m_pDoc->Parse(strJsonText);
    if (kParseErrorNone != m_pDoc->GetParseError())
        return false;

    *m_pValue = m_pDoc->Move();
    return true;
}

bool CJsonUtils::Parse(const string& strJsonText)
{
    return Parse(strJsonText.c_str());
}

string CJsonUtils::GetJsonText() const
{
    StringBuffer stBuffer(0, 256);
    Writer<StringBuffer> stWriter(stBuffer);
    m_pValue->Accept(stWriter);

    return string(stBuffer.GetString(), stBuffer.GetSize());
}

bool CJsonUtils::IsObject() const
{
    switch (m_pValue->GetType())
    {
        case kStringType:
        case kNumberType:
        case kTrueType:
        case kFalseType:
            return false;

        default:
            return true;
    }
}

bool CJsonUtils::IsString() const
{
    return m_pValue->IsString();
}

bool CJsonUtils::IsNumber() const
{
    return m_pValue->IsNumber();
}

bool CJsonUtils::IsStringNumber() const
{
    if (false == IsString())
        return false;

    const char* cch = m_pValue->GetString();
    if ('-' == *cch)
        ++cch;

    int iDotCount = 0;
    for (; *cch != 0; ++cch)
    {
        if (0 == isdigit(*cch))
        {
            if ('.' != *cch)
                return false;

            ++iDotCount;
            if (1 < iDotCount)
                return false;
        }
    }

    return true;
}

bool CJsonUtils::IsInt32() const
{
    return m_pValue->IsInt();
}

bool CJsonUtils::IsInt64() const
{
    return m_pValue->IsInt64();
}

bool CJsonUtils::IsUint32() const
{
    return m_pValue->IsUint();
}

bool CJsonUtils::IsUint64() const
{
    return m_pValue->IsUint64();
}

bool CJsonUtils::IsDouble() const
{
    return m_pValue->IsDouble();
}

bool CJsonUtils::IsExists(const char* strKey) const
{
    return m_pValue->HasMember(strKey);
}

bool CJsonUtils::IsExists(const std::string& strKey) const
{
    return IsExists(strKey.c_str());
}

CJsonUtils CJsonUtils::operator[](const char* strKey)
{
    Value::MemberIterator iter = m_pValue->FindMember(strKey);
    if (m_pValue->MemberEnd() == iter)
    {
        Value tKey(strKey, m_pDoc->GetAllocator());
        Value tValue(kObjectType);
        m_pValue->AddMember(tKey, tValue, m_pDoc->GetAllocator());

        iter = m_pValue->FindMember(strKey);
    }

    return CJsonUtils(m_pDoc, &iter->value);
}

CJsonUtils CJsonUtils::operator[](const string& strKey)
{
    Value::MemberIterator iter = m_pValue->FindMember(strKey.c_str());
    if (m_pValue->MemberEnd() == iter)
    {
        Value tKey(strKey.c_str(), strKey.length(), m_pDoc->GetAllocator());
        Value tValue(kObjectType);
        m_pValue->AddMember(tKey, tValue, m_pDoc->GetAllocator());

        iter = m_pValue->FindMember(strKey.c_str());
    }

    return CJsonUtils(m_pDoc, &iter->value);
}

const CJsonUtils CJsonUtils::operator[](const char* strKey) const
{
    Value::MemberIterator iter = m_pValue->FindMember(strKey);
    if (m_pValue->MemberEnd() == iter)
    {
        return CJsonUtils(m_pDoc, &gNullValue);
    }

    return CJsonUtils(m_pDoc, &iter->value);
}

const CJsonUtils CJsonUtils::operator[](const std::string& strKey) const
{
    return operator[](strKey.c_str());
}

int32_t CJsonUtils::ArrayCount() const
{
    if (false == m_pValue->IsArray())
        return -1;

    return m_pValue->Size();
}

CJsonUtils CJsonUtils::operator[](int32_t iArrayIndex)
{
    if (false == m_pValue->IsArray())
        m_pValue->SetArray();

    int32_t iSize = m_pValue->Size();
    for (int32_t i = iSize; i < iArrayIndex + 1; ++i)
    {
        Value tValue(kObjectType);
        m_pValue->PushBack(tValue, m_pDoc->GetAllocator());
    }

    Value& tValue = (*m_pValue)[iArrayIndex];
    return CJsonUtils(m_pDoc, &tValue);
}

const CJsonUtils CJsonUtils::operator[](int32_t iArrayIndex) const
{
    if (false == m_pValue->IsArray())
        return CJsonUtils(m_pDoc, &gNullValue);

    if ((SizeType)iArrayIndex >= m_pValue->Size())
        return CJsonUtils(m_pDoc, &gNullValue);

    Value& tValue = (*m_pValue)[iArrayIndex];
    return CJsonUtils(m_pDoc, &tValue);
}

CJsonUtils& CJsonUtils::operator=(const char* strValue)
{
    m_pValue->SetString(strValue, m_pDoc->GetAllocator());
    return *this;
}

CJsonUtils& CJsonUtils::operator=(const std::string& strValue)
{
    m_pValue->SetString(strValue.c_str(), strValue.length(), m_pDoc->GetAllocator());
    return *this;
}

CJsonUtils& CJsonUtils::operator=(int32_t iValue)
{
    m_pValue->SetInt(iValue);
    return *this;
}

CJsonUtils& CJsonUtils::operator=(int64_t i64Value)
{
    m_pValue->SetInt64(i64Value);
    return *this;
}

CJsonUtils& CJsonUtils::operator=(uint32_t uValue)
{
    m_pValue->SetUint(uValue);
    return *this;
}

CJsonUtils& CJsonUtils::operator=(uint64_t u64Value)
{
    m_pValue->SetUint64(u64Value);
    return *this;
}

CJsonUtils& CJsonUtils::operator=(double dValue)
{
    m_pValue->SetDouble(dValue);
    return *this;
}

CJsonUtils::operator string() const
{
    if (true == m_pValue->IsString())
    {
        return string(m_pValue->GetString(), m_pValue->GetStringLength());
    }
    else if (m_pValue->IsInt())
    {
        char szBuf[64] = {0};
        snprintf(szBuf, sizeof(szBuf), "%d", m_pValue->GetInt());
        return szBuf;
    }
    else if (m_pValue->IsInt64())
    {
        char szBuf[64] = {0};
        snprintf(szBuf, sizeof(szBuf), "%jd", m_pValue->GetInt64());
        return szBuf;
    }
    else if (m_pValue->IsUint())
    {
        char szBuf[64] = {0};
        snprintf(szBuf, sizeof(szBuf), "%u", m_pValue->GetUint());
        return szBuf;
    }
    else if (true == m_pValue->IsUint64())
    {
        char szBuf[64] = {0};
        snprintf(szBuf, sizeof(szBuf), "%ju", m_pValue->GetUint64());
        return szBuf;
    }
    else if (true == m_pValue->IsDouble())
    {
        char szBuf[64] = {0};
        snprintf(szBuf, sizeof(szBuf), "%g", m_pValue->GetDouble());
        return szBuf;
    }
    else
    {
        return GetJsonText();
    }
}

CJsonUtils::operator int32_t() const
{
    return ConvertToNumber<int32_t>(atoi, 0);
}

CJsonUtils::operator uint32_t() const
{
    return ConvertToNumber<uint32_t>(atoi, 0);
}

CJsonUtils::operator int64_t() const
{
    return ConvertToNumber<int64_t>(atoll, 0L);
}

CJsonUtils::operator uint64_t() const
{
    return ConvertToNumber<uint64_t>(atoll, 0L);
}

CJsonUtils::operator double() const
{
    return ConvertToNumber<double>(atof, 0.0);
}

template<typename _TYPE_, typename _CONVERT_FUNC_, typename _DEF_VAL>
_TYPE_ CJsonUtils::ConvertToNumber(_CONVERT_FUNC_ pFunc, _DEF_VAL tDefValue) const
{
    if (true == m_pValue->IsString())
    {
        return pFunc(m_pValue->GetString());
    }
    else if (true == m_pValue->IsInt())
    {
        return m_pValue->GetInt();
    }
    else if (true == m_pValue->IsInt64())
    {
        return m_pValue->GetInt64();
    }
    else if (true == m_pValue->IsUint())
    {
        return m_pValue->GetUint();
    }
    else if (true == m_pValue->IsUint64())
    {
        return m_pValue->GetUint64();
    }
    else if (true == m_pValue->IsDouble())
    {
        return m_pValue->GetDouble();
    }
    else
    {
        return tDefValue;
    }
}

/****************************************************
 * 流模式Json生成类
 ***************************************************/
JsonWriter::JsonWriter() : m_Buffer(0, 256), m_Writer(m_Buffer)
{
    m_Writer.StartObject();
}

JsonWriter::~JsonWriter()
{

}

string JsonWriter::GetJsonText()
{
    if (true == m_strJsonText.empty())
    {
        m_Writer.EndObject();
        m_strJsonText.assign(m_Buffer.GetString(), m_Buffer.GetSize());
    }

    return m_strJsonText;
}

void JsonWriter::SetAttrib(const char* strKey, const char* strValue)
{
    m_Writer.Key(strKey);
    m_Writer.String(strValue);
}

void JsonWriter::SetAttrib(const std::string& strKey, const char* strValue)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.String(strValue);
}

void JsonWriter::SetAttrib(const char* strKey, const std::string& strValue)
{
    m_Writer.Key(strKey);
    m_Writer.String(strValue.c_str(), strValue.length(), true);
}

void JsonWriter::SetAttrib(const std::string& strKey, const std::string& strValue)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.String(strValue.c_str(), strValue.length(), true);
}

void JsonWriter::SetAttrib(const char* strKey, int32_t iValue)
{
    m_Writer.Key(strKey);
    m_Writer.Int(iValue);
}

void JsonWriter::SetAttrib(const string& strKey, int32_t iValue)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.Int(iValue);
}

void JsonWriter::SetAttrib(const char* strKey, int64_t i64Value)
{
    m_Writer.Key(strKey);
    m_Writer.Int64(i64Value);
}

void JsonWriter::SetAttrib(const string& strKey, int64_t i64Value)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.Int64(i64Value);
}

void JsonWriter::SetAttrib(const char* strKey, uint32_t uValue)
{
    m_Writer.Key(strKey);
    m_Writer.Uint(uValue);
}

void JsonWriter::SetAttrib(const string& strKey, uint32_t uValue)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.Uint(uValue);
}

void JsonWriter::SetAttrib(const char* strKey, uint64_t u64Value)
{
    m_Writer.Key(strKey);
    m_Writer.Uint64(u64Value);
}

void JsonWriter::SetAttrib(const string& strKey, uint64_t u64Value)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.Uint64(u64Value);
}

void JsonWriter::SetAttrib(const char* strKey, double dValue)
{
    m_Writer.Key(strKey);
    m_Writer.Double(dValue);
}

void JsonWriter::SetAttrib(const string& strKey, double dValue)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.Double(dValue);
}

void JsonWriter::ChildBegin(const char* strKey)
{
    m_Writer.Key(strKey);
    m_Writer.StartObject();
}

void JsonWriter::ChildBegin(const std::string& strKey)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.StartObject();
}

void JsonWriter::ChildEnd()
{
    m_Writer.EndObject();
}

void JsonWriter::ArrayBegin(const char* strKey)
{
    m_Writer.Key(strKey);
    m_Writer.StartArray();
}

void JsonWriter::ArrayBegin(const string& strKey)
{
    m_Writer.Key(strKey.c_str(), strKey.length(), true);
    m_Writer.StartArray();
}

void JsonWriter::ArrayEnd()
{
    m_Writer.EndArray();
}

void JsonWriter::ArraySetValue(const char* strValue)
{
    m_Writer.String(strValue);
}

void JsonWriter::ArraySetValue(const std::string& strValue)
{
    m_Writer.String(strValue.c_str(), strValue.length(), true);
}

void JsonWriter::ArraySetValue(int32_t iValue)
{
    m_Writer.Int(iValue);
}

void JsonWriter::ArraySetValue(int64_t i64Value)
{
    m_Writer.Int64(i64Value);
}

void JsonWriter::ArraySetValue(uint32_t uValue)
{
    m_Writer.Uint(uValue);
}

void JsonWriter::ArraySetValue(uint64_t u64Value)
{
    m_Writer.Uint64(u64Value);
}

void JsonWriter::ArraySetValue(double dValue)
{
    m_Writer.Double(dValue);
}
