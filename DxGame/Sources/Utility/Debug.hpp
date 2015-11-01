# pragma once

# include "String.hpp"

# include <DxLib.h>

/// <summary>�f�o�b�O���</summary>
class Debug
{
public:

	Debug();

public:

	/// <summary>��ʂɃf�o�b�O�\������</summary>
	template <typename ...Args>
	static void FormatPrint(const String& format, Args&& ...args)
	{
		printfDx(format.ToWide().c_str(), std::forward<Args>(args)...);
	}

	/// <summary>��ʂɃf�o�b�O�\���������Ɖ��s����</summary>
	template <typename ...Args>
	static void FormatPrintln(const String& format, Args&& ...args)
	{
		FormatPrint(format.ToWide().c_str(), std::forward<Args>(args)...);
		printfDx("\n");
	}

	template <typename Type, typename ...Args>
	static void Print(const Type& value, Args&& ...args)
	{
		printfDx(String::Create(value, std::forward<Args>(args)...).ToWide().c_str());
	}

	template <typename Type, typename ...Args>
	static void Println(const Type& value, Args&& ...args)
	{
		FormatPrint(value, std::forward<Args>(args)...);
		printfDx(L"\n");
	}

	/// <summary>�X�V����</summary>
	static void Update();

	/// <summary>���t���[���N���A���邩�ǂ�����ݒ肷��</summary>
	static void SetClear(bool isClear);

	/// <summary>���t���[���N���A���邩�ǂ�����Ԃ�</summary>
	static bool IsClear();

	/// <summary>�f�o�b�O�\�����N���A����</summary>
	static void Clear();

	/// <summary>���b�Z�[�W�{�b�N�X��\������</summary>
	static void Show(const TCHAR* messsage, const TCHAR* caption, UINT style);

	/// <summary>�t�H���g�T�C�Y��ύX����</summary>
	static void ChangeFontSize(int fontSize);

private:

	bool m_isClear;

	int m_fontSize;
};
