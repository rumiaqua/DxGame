# pragma once

# include <string>
# include <vector>
# include <sstream>

class String
{
public:

	/// <summary>デフォルトコンストラクタ</summary>
	String();

	/// <summary>マルチバイト文字列で初期化</summary>
	/// <param name="str">マルチバイト文字列</param>
	String(const char* str);

	/// <summary>ワイド文字列で初期化</summary>
	/// <param name="str">ワイド文字列</param>
	String(const wchar_t* str);

	/// <summary>stringクラスで初期化</summary>
	/// <param name="str">stringクラス</param>
	String(const std::string& str);

	/// <summary>wstringクラスで初期化</summary>
	/// <param name="str">wstringクラス</param>
	String(const std::wstring& str);

public:

	/// <summary>代入演算子</summary>
	/// <param name="str">文字列</param>
	String& operator = (const String& str);

	/// <summary>指定したインデックスの文字を返す</summary>
	/// <param name="index">インデックス</param>
	wchar_t operator [] (unsigned int index) const;

public:

	/// <summary>文字列の長さを返す</summary>
	unsigned int Length() const;

	/// <summary>ワイド文字列を返す</summary>
	std::wstring ToWide() const;

	/// <summary>マルチバイト文字列を返す</summary>
	std::string ToNarrow() const;

public:

	/// <summary>文字列の長さを返す</summary>
	/// <param name="str">文字列</param>
	static unsigned int Length(const String& str);

	/// <summary>ワイド文字列に変換する</summary>
	/// <param name="narrow">マルチバイト文字列</param>
	static std::wstring ToWide(const std::string& narrow);

	/// <summary>マルチバイト文字列に変換する</summary>
	/// <param name="wide">ワイド文字列</param>
	static std::string ToNarrow(const std::wstring& wide);

	/// <summary>ワイド文字列を返す</summary>
	/// <param name="str">文字列</param>
	static std::wstring ToWide(const String& str);

	/// <summary>マルチバイト文字列を返す</summary>
	/// <param name="str">文字列</param>
	static std::string ToNarrow(const String& str);

	/// <summary>値から文字列を生成する</summary>
	/// <param name="value">operator &lt;&lt; が定義されている値</param>
	template <typename Type>
	static String Create(const Type& value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}

	/// <summary>値から文字列を生成する</summary>
	/// <param name="value">operator &lt;&lt; が定義されている値</param>
	static String Create(const wchar_t* value)
	{
		return String(value);
	}

	/// <summary>値から文字列を生成する</summary>
	/// <param name="value">operator &lt;&lt; が定義されている値</param>
	template <typename Type, typename ...Args>
	static String Create(const Type& value, Args&& ...args)
	{
		return Create(value) + Create(std::forward<Args>(args)...);
	}

	/// <summary>文字列から値を生成する</summary>
	/// <param name="str">文字列</param>
	template <typename Type>
	static Type ToValue(const String& str)
	{
		std::stringstream stream(str.ToNarrow());
		Type value;
		stream >> value;
		return value;
	}

	/// <summary>文字列を分割する</summary>
	/// <param name="delim">分割文字</param>
	static std::vector<String> Split(const String& str, char delim);

public:

	bool operator == (const String& str) const;

	bool operator != (const String& str) const;

	String& operator += (const String& str);

	String operator + (const String& str) const;

private:

	/// <summary>wstringクラス</summary>
	std::wstring m_str;
};

namespace std
{
	template <>
	struct hash<String>
	{
		inline std::size_t operator() (const String& key) const
		{
			return std::hash<std::string>()(key.ToNarrow());
		}
	};
}

std::ostream& operator << (std::ostream& stream, const String& str);
