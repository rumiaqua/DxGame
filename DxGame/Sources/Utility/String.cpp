# include "String.hpp"

# include <Windows.h>

String::String()
	: m_str()
{

}

String::String(const char* str)
	: String(std::string(str))
{

}

String::String(const wchar_t* str)
	: m_str(str)
{

}

String::String(const std::string& str)
	: m_str(ToWide(str))
{

}

String::String(const std::wstring& str)
	: m_str(str)
{

}

String& String::operator = (const String& str)
{
	m_str = str.m_str;
	return *this;
}

wchar_t String::operator[](unsigned int index) const
{
	return m_str[index];
}

unsigned int String::Length() const
{
	return Length(*this);
}

std::wstring String::ToWide() const
{
	return ToWide(*this);
}

std::string String::ToNarrow() const
{
	return ToNarrow(*this);
}

std::wstring String::ToWide(const std::string& narrow)
{
	int length =
		MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, NULL, 0);
	wchar_t* buffer = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, buffer, length);
	std::wstring result(buffer, buffer + length - 1);
	delete[] buffer;
	return result;
}

std::string String::ToNarrow(const std::wstring& wide)
{
	int length = WideCharToMultiByte(
		CP_OEMCP, 0, wide.c_str(), -1, NULL, 0, NULL, NULL);
	char* buffer = new char[length];
	WideCharToMultiByte(
		CP_OEMCP, 0, wide.c_str(), -1, buffer, length, NULL, NULL);
	std::string result(buffer, buffer + length - 1);
	delete[] buffer;
	return result;
}

unsigned int String::Length(const String& str)
{
	return (unsigned int)str.m_str.length();
}

std::string String::ToNarrow(const String& str)
{
	return ToNarrow(str.m_str);
}

std::wstring String::ToWide(const String& str)
{
	return str.m_str;
}

std::vector<String> String::Split(const String& str, char delim)
{
	std::vector<String> res;
	size_t current = 0, found;
	std::string s = str.ToNarrow();
	while ((found = s.find_first_of(delim, current)) != std::string::npos)
	{
		res.push_back(std::string(s, current, found - current));
		current = found + 1;
	}
	res.push_back(std::string(s, current, s.size() - current));
	return res;
}

bool String::operator == (const String& str) const
{
	return m_str == str.m_str;
}

bool String::operator != (const String& str) const
{
	return !(*this == str);
}

String& String::operator += (const String& str)
{
	m_str.append(str.m_str);
	return *this;
}

String String::operator + (const String& str) const
{
	String result = *this;
	return result += str;
}

std::ostream& operator << (std::ostream& stream, const String& str)
{
	stream << String::ToNarrow(str);
	return stream;
}
