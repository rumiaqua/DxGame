# pragma once

# include <ostream>

/// <summary>ゲッターインターフェース</summary>
template <typename Type>
class IGetter
{
public:
	virtual const Type& Get() const = 0;
	operator const Type& () const
	{
		return Get();
	}
};

/// <summary>セッターインターフェース</summary>
template <typename Type>
class ISetter
{
public:
	virtual void Set(const Type& value) = 0;
	virtual ISetter& operator = (const Type& value) = 0;
	virtual Type& Get() = 0;
	operator Type& ()
	{
		return Get();
	}
};

/// <summary>ゲッタークラス</summary>
template <typename Type>
class Getter : public IGetter<Type>
{
public:
	/// <summary>コンストラクタ</summary>
	/// <param name="value">ホールドする変数</param>
	Getter(const Type& value)
		: m_value(value)
	{

	}
	/// <summary>値の取得</summary>
	virtual const Type& Get() const override
	{
		return m_value;
	}
private:
	const Type& m_value;
};

template <typename Type>
class Setter : public ISetter<Type>
{
public:
	/// <summary>コンストラクタ</summary>
	/// <param name="value">ホールドする値</param>
	Setter(Type& value)
		: m_value(value)
	{

	}
	/// <summary>値の設定</summary>
	/// <param name="value">値</param>
	virtual void Set(const Type& value) override
	{
		m_value = value;
	}
	virtual ISetter& operator = (const Type& value) override
	{
		Set(value);
		return *this;
	}
	/// <summary>値の取得</summary>
	virtual Type& Get() override
	{
		return m_value;
	}
private:
	Type& m_value;
};

/// <summary>アクセサークラス</summary>
template <typename Type>
class Accessor : public IGetter<Type>, ISetter<Type>
{
public:
	/// <summary>コンストラクタ</summary>
	/// <param name="value">ホールドする値</param>
	Accessor(Type& value)
		: m_value(value)
	{

	}
	/// <summary>値の取得</summary>
	virtual const Type& Get() const override
	{
		return m_value;
	}
	/// <summary>値の設定</summary>
	/// <param name="value">値</param>
	virtual void Set(const Type& value) override
	{
		m_value = value;
	}
	virtual ISetter& operator = (const Type& value) override
	{
		Set(value);
		return *this;
	}
	/// <summary>値の取得</summary>
	virtual Type& Get() override
	{
		return m_value;
	}
private:
	Type& m_value;
};

/// <summary>標準入出力をサポート</summary>
template <typename Type>
std::ostream& operator << (std::ostream& stream, const IGetter<Type>& accessor)
{
	stream << accessor.Get();
	return stream;
}
