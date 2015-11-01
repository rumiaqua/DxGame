# pragma once

# include <string>
# include <vector>
# include <sstream>

class String
{
public:

	/// <summary>�f�t�H���g�R���X�g���N�^</summary>
	String();

	/// <summary>�}���`�o�C�g������ŏ�����</summary>
	/// <param name="str">�}���`�o�C�g������</param>
	String(const char* str);

	/// <summary>���C�h������ŏ�����</summary>
	/// <param name="str">���C�h������</param>
	String(const wchar_t* str);

	/// <summary>string�N���X�ŏ�����</summary>
	/// <param name="str">string�N���X</param>
	String(const std::string& str);

	/// <summary>wstring�N���X�ŏ�����</summary>
	/// <param name="str">wstring�N���X</param>
	String(const std::wstring& str);

public:

	/// <summary>������Z�q</summary>
	/// <param name="str">������</param>
	String& operator = (const String& str);

	/// <summary>�w�肵���C���f�b�N�X�̕�����Ԃ�</summary>
	/// <param name="index">�C���f�b�N�X</param>
	wchar_t operator [] (unsigned int index) const;

public:

	/// <summary>������̒�����Ԃ�</summary>
	unsigned int Length() const;

	/// <summary>���C�h�������Ԃ�</summary>
	std::wstring ToWide() const;

	/// <summary>�}���`�o�C�g�������Ԃ�</summary>
	std::string ToNarrow() const;

public:

	/// <summary>������̒�����Ԃ�</summary>
	/// <param name="str">������</param>
	static unsigned int Length(const String& str);

	/// <summary>���C�h������ɕϊ�����</summary>
	/// <param name="narrow">�}���`�o�C�g������</param>
	static std::wstring ToWide(const std::string& narrow);

	/// <summary>�}���`�o�C�g������ɕϊ�����</summary>
	/// <param name="wide">���C�h������</param>
	static std::string ToNarrow(const std::wstring& wide);

	/// <summary>���C�h�������Ԃ�</summary>
	/// <param name="str">������</param>
	static std::wstring ToWide(const String& str);

	/// <summary>�}���`�o�C�g�������Ԃ�</summary>
	/// <param name="str">������</param>
	static std::string ToNarrow(const String& str);

	/// <summary>�l���當����𐶐�����</summary>
	/// <param name="value">operator &lt;&lt; ����`����Ă���l</param>
	template <typename Type>
	static String Create(const Type& value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}

	/// <summary>�l���當����𐶐�����</summary>
	/// <param name="value">operator &lt;&lt; ����`����Ă���l</param>
	static String Create(const wchar_t* value)
	{
		return String(value);
	}

	/// <summary>�l���當����𐶐�����</summary>
	/// <param name="value">operator &lt;&lt; ����`����Ă���l</param>
	template <typename Type, typename ...Args>
	static String Create(const Type& value, Args&& ...args)
	{
		return Create(value) + Create(std::forward<Args>(args)...);
	}

	/// <summary>�����񂩂�l�𐶐�����</summary>
	/// <param name="str">������</param>
	template <typename Type>
	static Type ToValue(const String& str)
	{
		std::stringstream stream(str.ToNarrow());
		Type value;
		stream >> value;
		return value;
	}

	/// <summary>������𕪊�����</summary>
	/// <param name="delim">��������</param>
	static std::vector<String> Split(const String& str, char delim);

public:

	bool operator == (const String& str) const;

	bool operator != (const String& str) const;

	String& operator += (const String& str);

	String operator + (const String& str) const;

private:

	/// <summary>wstring�N���X</summary>
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
