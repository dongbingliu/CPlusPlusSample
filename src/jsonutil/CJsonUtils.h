
/**
 * <pre>
 *     @ author : dongbingliu(柳洞兵)
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2020/12/23
 *     @ desc   :
 *     version: 1.0
 * </pre>
 */

#ifndef CJSON_H
#define	CJSON_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"


/**
 * Json对象类，封装Json操作的插入等方法
 * 使用范例如下：
 * CJsonUtils json;
 * json["a"] = "a";
 * json["b"] = "123";
 * json["c"] = 123;
 * json["d"] = "1.5";
 * json["e"] = 1.5
 * json["child"]["a"] = "1";
 * json["child"]["b"] = "2";
 * json["array"][0] = 1;
 * json["array"][1] = 2;
 *
 * std::string strJsonText = json.GetJsonText();
 *
 * CJsonUtils json2;
 * json2.Parse(strJsonText);
 *
 * std::string a1 = json2["a"];
 * int a2 = json2["a"];
 * double a3 = json2["a"];
 * int ca1 = json["child"]["a"];
 * int aa1 = json["array"][0];
 */
class CJsonUtils
{
private:
    CJsonUtils(rapidjson::Document* pDoc, rapidjson::Value* pValue);

public:
    CJsonUtils();
    CJsonUtils(const CJsonUtils& other);
    ~CJsonUtils();

    CJsonUtils& operator=(const CJsonUtils& Other);

    /**
     * 解析Json文本
     * @param strJsonText
     * @return
     */
    bool Parse(const char* strJsonText);
    bool Parse(const std::string& strJsonText);

    /**
     * 生成Json本文
     * @return Json文本字符串
     */
    std::string GetJsonText() const;

public:
    /**
     * 判断当前存储的内容的什么类型
     * IsNumber = IsInt32|IsInt64|IsUint32|IsUint64|IsDouble
     *
     * @return
     *		true	是
     *		false	不是
     *
     * 注意:
     *		1.字符串数字，类型为字符串，而不是数字，因此请正确的存储值的类型
     *		2.对于整形而言，若值能正确转换为某种类型，则IsType=true.以下为举例:
     *			 1:		IsInt32、IsInt64、IsUint32、IsUint64 = true
     *			-1:		IsInt32、IsInt64   = true;
     *					IsUint32、IsUint64 = false
     *			50亿:	IsInt64、IsUint64  = true;
     *					IsInt32、 IsUint32 = false
     */
    bool IsObject() const;
    bool IsString() const;
    bool IsNumber() const;
    bool IsStringNumber() const;
    bool IsInt32() const;
    bool IsInt64() const;
    bool IsUint32() const;
    bool IsUint64() const;
    bool IsDouble() const;

    /**
     * 判断是否存在制定的键值对
     * @param[in] strKey 键字符串
     * @return
     */
    bool IsExists(const char* strKey) const;
    bool IsExists(const std::string& strKey) const;

public:
    /**
     * 键值对操作，得到值对象
     * @param[in] strKey 键字符串
     * @return 值对象
     */
    CJsonUtils operator[](const char* strKey);
    CJsonUtils operator[](const std::string& strKey);
    const CJsonUtils operator[](const char* strKey) const;
    const CJsonUtils operator[](const std::string& strKey) const;

    /**
	 * 返回数组中元素的个数
	 * @return
	 *		>=0	元素个数
	 *		<0	不是数组
	 */
    int32_t ArrayCount() const;

    /**
     * 得到数组中指定索引的对象
     * @param[in] iArrayIndex 数组索引号
     * @return 值对象
     */
    CJsonUtils operator[](int32_t iArrayIndex);
    const CJsonUtils operator[](int32_t iArrayIndex) const;

public:
    /**
     * 赋值操作，修改对象存储的内容
     * @param[in] 各种Value
     * @return 对象自身的引用
     */
    CJsonUtils& operator=(const char* strValue);
    CJsonUtils& operator=(const std::string& strValue);
    CJsonUtils& operator=(int32_t iValue);
    CJsonUtils& operator=(int64_t i64Value);
    CJsonUtils& operator=(uint32_t uValue);
    CJsonUtils& operator=(uint64_t u64Value);
    CJsonUtils& operator=(double dValue);

    /**
     * 隐式转换，取值
     * @return
     *		std::string	若存储的是字符串，则的得到字符串
     *					若存储的是数值，则得到转换后的字符串
     *					若存储的是其他对象，则得到Json文本
     *
     *		int32_t、uint32_t、int64_t、uint64_t、double
     *					若存储的是数值，则返回数值本身
     *					若存储的是字符串形式的数值，则自动转换为对应的数值
     *					若存储的是其他类型，则返回0
     *
     * 注意:
     *		取值不会破坏原本的存储类型，例如:原本存储的 "1234" - 字符串1234，若用int来取值，
     *		得到的虽然是整形的1234，但是存储的内容还是字符串1234，不会改变
     */
    operator std::string() const;
    operator int32_t() const;
    operator uint32_t() const;
    operator int64_t() const;
    operator uint64_t() const;
    operator double() const;

private:
    template<typename _TYPE_, typename _CONVERT_FUNC_, typename _DEF_VAL>
    _TYPE_ ConvertToNumber(_CONVERT_FUNC_ pFunc, _DEF_VAL tDefValue) const;

    bool                    m_bRoot;
    rapidjson::Document*    m_pDoc;
    rapidjson::Value*       m_pValue;
} ;

/**
 * 流模式Json生成类，流式写入，仅能写一次，可用于快速生成Json文本，性能是CJObject的2倍有余
 * JsonWriter tWriter;
 * tWriter.SetAttrib("str", "string");
 * tWriter.SetAttrib("i32", 1);
 * tWriter.SetAttrib("dbl", 1.0);
 *
 * //括号非必要，只是为了代码清晰
 * tWriter.ChildBegin("child");
 * {
 *		tWriter.SetAttrib("c1", "c1");
 *		tWriter.SetAttrib("c2", 2);
 * }
 * tWriter.ChildEnd();
 *
 * //括号非必要，只是为了代码清晰
 * tWriter.ArrayBegin("array");
 * {
 *		tWriter.ArraySetValue("string");
 *		tWriter.ArraySetValue(1);
 * }
 * tWriter.ArrayEnd();
 *
 * //混合写法，这时能体现括号增加代码可读性的价值
 * tWriter.ChildBegin("child_1");
 * {
 *		tWriter.SetAttrib("child_1_key", "child_1_val");
 *		tWriter.ChildBegin("child_2");
 *		{
 *			tWriter.SetAttrib("key_2_str", "value_2");
 *			tWriter.SetAttrib("key_2_int", 1);
 *
 *			tWriter.ArrayBegin("Array_2");
 *			{
 *				tWriter.ArraySetValue("str_2_1");
 *				tWriter.ArraySetValue("str_2_2");
 *			}
 *			tWriter.ArrayEnd();
 *		}
 *		tWriter.ChildEnd();
 * }
 * tWriter.ChildEnd();
 */
class JsonWriter
{
private:
    typedef rapidjson::Writer<rapidjson::StringBuffer> MT_RapidJsonWriter;

    /**
     * 禁用复制构造函数
     * @param[in] other
     */
    JsonWriter(const JsonWriter& other);

public:
    JsonWriter();
    ~JsonWriter();

    /**
     * 完成Json文本的生成，并获取文本内容
     * 本函数一但调用，所有其他函数均失效
     * @return
     */
    std::string GetJsonText();

public:
    /**
     * 标准的键值参数写入
     * @param[in] strKey 键字符串
     * @param[in] xValue 值
     */
    void SetAttrib(const char* strKey, const char* strValue);
    void SetAttrib(const std::string& strKey, const char* strValue);
    void SetAttrib(const char* strKey, const std::string& strValue);
    void SetAttrib(const std::string& strKey, const std::string& strValue);
    void SetAttrib(const char* strKey, int32_t iValue);
    void SetAttrib(const std::string&strKey, int32_t iValue);
    void SetAttrib(const char* strKey, int64_t i64Value);
    void SetAttrib(const std::string&strKey, int64_t i64Value);
    void SetAttrib(const char* strKey, uint32_t uValue);
    void SetAttrib(const std::string&strKey, uint32_t uValue);
    void SetAttrib(const char* strKey, uint64_t u64Value);
    void SetAttrib(const std::string&strKey, uint64_t u64Value);
    void SetAttrib(const char* strKey, double dValue);
    void SetAttrib(const std::string&strKey, double dValue);

    /**
     * 子对象，为了兼容多级Json，注意成对使用，使用错误的话，函数自身是无法检测的
     * @param[in] strKey 键字符串
     */
    void ChildBegin(const char* strKey);
    void ChildBegin(const std::string& strKey);
    void ChildEnd();

    /**
     * 数组操作，注意成对使用，使用错误的话，函数自身是无法检测的
     * @param[in] strKey 键字符串
     */
    void ArrayBegin(const char* strKey);
    void ArrayBegin(const std::string& strKey);
    void ArrayEnd();

    void ArraySetValue(const char* strValue);
    void ArraySetValue(const std::string& strValue);
    void ArraySetValue(int32_t iValue);
    void ArraySetValue(int64_t i64Value);
    void ArraySetValue(uint32_t uValue);
    void ArraySetValue(uint64_t u64Value);
    void ArraySetValue(double dValue);

private:
    std::string					m_strJsonText;
    rapidjson::StringBuffer		m_Buffer;
    MT_RapidJsonWriter			m_Writer;
} ;


#endif //RAPIDJSONSAMPLE_CJOBJECT_H
