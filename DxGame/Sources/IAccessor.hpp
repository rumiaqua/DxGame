# pragma once

# include <ostream>

/// <summary>�Q�b�^�[�C���^�[�t�F�[�X</summary>
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

/// <summary>�Z�b�^�[�C���^�[�t�F�[�X</summary>
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

/// <summary>�Q�b�^�[�N���X</summary>
template <typename Type>
class Getter : public IGetter<Type>
{
public:
	/// <summary>�R���X�g���N�^</summary>
	/// <param name="value">�z�[���h����ϐ�</param>
	Getter(const Type& value)
		: m_value(value)
	{

	}
	/// <summary>�l�̎擾</summary>
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
	/// <summary>�R���X�g���N�^</summary>
	/// <param name="value">�z�[���h����l</param>
	Setter(Type& value)
		: m_value(value)
	{

	}
	/// <summary>�l�̐ݒ�</summary>
	/// <param name="value">�l</param>
	virtual void Set(const Type& value) override
	{
		m_value = value;
	}
	virtual ISetter& operator = (const Type& value) override
	{
		Set(value);
		return *this;
	}
	/// <summary>�l�̎擾</summary>
	virtual Type& Get() override
	{
		return m_value;
	}
private:
	Type& m_value;
};

/// <summary>�A�N�Z�T�[�N���X</summary>
template <typename Type>
class Accessor : public IGetter<Type>, ISetter<Type>
{
public:
	/// <summary>�R���X�g���N�^</summary>
	/// <param name="value">�z�[���h����l</param>
	Accessor(Type& value)
		: m_value(value)
	{

	}
	/// <summary>�l�̎擾</summary>
	virtual const Type& Get() const override
	{
		return m_value;
	}
	/// <summary>�l�̐ݒ�</summary>
	/// <param name="value">�l</param>
	virtual void Set(const Type& value) override
	{
		m_value = value;
	}
	virtual ISetter& operator = (const Type& value) override
	{
		Set(value);
		return *this;
	}
	/// <summary>�l�̎擾</summary>
	virtual Type& Get() override
	{
		return m_value;
	}
private:
	Type& m_value;
};

/// <summary>�W�����o�͂��T�|�[�g</summary>
template <typename Type>
std::ostream& operator << (std::ostream& stream, const IGetter<Type>& accessor)
{
	stream << accessor.Get();
	return stream;
}
