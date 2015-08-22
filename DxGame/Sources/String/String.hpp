# pragma once

# include <string>

# include <vector>

# include <unordered_map>

namespace aqua
{
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

		operator const wchar_t* () const;

	public:

		String& operator = (const String& str);

		bool operator == (const wchar_t* str) const;

		bool operator == (const String& str) const;

		wchar_t operator [] (unsigned int index) const;

	public:

		/// <summary>������̒�����Ԃ�</summary>
		/// <param name="str">������</param>
		unsigned int Length() const;

		/// <summary>string�N���X�ɕϊ�</summary>
		/// <param name="str">������</param>
		std::string ToNarrow() const;

		/// <summary>wstring�N���X�ɕϊ�</summary>
		/// <param name="str">������</param>
		std::wstring ToWide() const;

		/// <summary>�������ĕԂ�</summary>
		/// <param name="str">������</param>
		/// <param name="delim">��������</param>
		/// <returns>�������Ď��[�������X�g</returns>
		std::vector<String> Split(wchar_t delim) const;

	private:

		std::wstring m_str;
	};
}

namespace std
{
	template <>
	class hash<aqua::String>
	{
	public:
		size_t operator()(const aqua::String& str) const
		{
			return hash<std::wstring>()(str.ToWide());
		}
	};
}
