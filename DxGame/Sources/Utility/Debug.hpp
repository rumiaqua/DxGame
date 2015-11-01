# pragma once

# include "String.hpp"

# include <DxLib.h>

/// <summary>デバッグ情報</summary>
class Debug
{
public:

	Debug();

public:

	/// <summary>画面にデバッグ表示する</summary>
	template <typename ...Args>
	static void FormatPrint(const String& format, Args&& ...args)
	{
		printfDx(format.ToWide().c_str(), std::forward<Args>(args)...);
	}

	/// <summary>画面にデバッグ表示したあと改行する</summary>
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

	/// <summary>更新処理</summary>
	static void Update();

	/// <summary>毎フレームクリアするかどうかを設定する</summary>
	static void SetClear(bool isClear);

	/// <summary>毎フレームクリアするかどうかを返す</summary>
	static bool IsClear();

	/// <summary>デバッグ表示をクリアする</summary>
	static void Clear();

	/// <summary>メッセージボックスを表示する</summary>
	static void Show(const TCHAR* messsage, const TCHAR* caption, UINT style);

	/// <summary>フォントサイズを変更する</summary>
	static void ChangeFontSize(int fontSize);

private:

	bool m_isClear;

	int m_fontSize;
};
