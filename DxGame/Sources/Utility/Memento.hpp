# pragma once

# include <deque>

/// <summary>�������g�p�^�[��</summary>
/// <summary>�^�ɑ΂��f�t�H���g�R���X�g���N�^��v�����܂�</summary>
template <typename Type>
class Memento
{
private:

	using Buffer = std::deque<Type>;

	using Size = typename Buffer::size_type;

public:

	/// <summary>�R���X�g���N�^</summary>
	/// <param name="bufferSize">�o�b�t�@�̃T�C�Y</param>
	/// <param name="isFill">�o�b�t�@�𖄂߂邩�ǂ���</param>
	Memento(const Size& bufferSize, bool isFill = true)
		: m_buffer()
		, m_bufferSize(bufferSize + 1)
		, m_isFill(isFill)
	{
		TryFill(true);
	}

public:

	/// <summary>�o�b�t�@�̃T�C�Y��ύX����</summary>
	void ChangeBufferSize(const Size& bufferSize)
	{
		m_bufferSize = bufferSize + 1;
		Resolve();
		TryFill(false);
	}

	/// <summary>�l��ۑ�����</summary>
	const Type& Save(const Type& value)
	{
		return Save(value, true);
	}

	/// <summary>�l������ō\�z���ĕۑ�����</summary>
	template <typename ...Args>
	void Emplace(Args&& ...args)
	{
		m_buffer.emplace_back(std::forward<Args>(args)...);
		Resolve();
	}

	/// <summary>������H��</summary>
	const Type& History(const Size& numPrevious)
	{
		// ����ۑ�����Ă��Ȃ��ꍇ�A�G���[
		if (Count() == 0)
		{
			throw std::out_of_range("�������ۑ�����Ă��܂���");
		}

		// �ۑ�����葽���k�낤�Ƃ����ꍇ�A�ł��Â��f�[�^��Ԃ�
		Size index = Count() > numPrevious ? Count() - numPrevious : Count();
		index -= 1;
		Buffer::iterator it = m_buffer.begin();
		for (Size i = 0; i < index; ++i)
		{
			++it;
		}
		return *it;
	}

	/// <summary>�������畜������</summary>
	const Type& Restore(const Size& numPrevious)
	{
		Size index = Count() > numPrevious ? numPrevious : 0;
		for (Size i = 0; i < index; ++i)
		{
			m_buffer.pop_back();
		}
		TryFill(false);
		return At(index);
	}

private:

	/// <summary>�l��ۑ�����</summary>
	/// <param name="isPost">�����ɒǉ����邩�ǂ���</param>
	const Type& Save(const Type& value, bool isPost)
	{
		isPost ? m_buffer.push_back(value) : m_buffer.push_front(value);
		Resolve();
		return m_buffer.back();
	}

	/// <summary>�I�[�o�[�t���[����������</summary>
	void Resolve()
	{
		if (Count() < Capacity())
		{
			return;
		}
		for (Size i = 0; i < Count() - Capacity(); ++i)
		{
			m_buffer.pop_front();
		}
	}

	/// <summary>�o�b�t�@�ɕۑ�����Ă���l�̐���Ԃ�</summary>
	Size Count() const
	{
		return m_buffer.size();
	}

	/// <summary>���e����Ă���T�C�Y��Ԃ�</summary>
	Size Capacity() const
	{
		return m_bufferSize - 1;
	}

	/// <summary>�l�Ŗ��߂�</summary>
	/// <param name="isPost">�����ɒǉ����邩�ǂ���</param>
	void Fill(bool isPost)
	{
		Size loop = Capacity() - Count();
		for (Size i = 0; i < loop; ++i)
		{
			Save(Type(), isPost);
		}
	}

	/// <summary>�l�Ŗ��߂邩���s����</summary>
	void TryFill(bool isPost)
	{
		if (m_isFill)
		{
			Fill(isPost);
		}
	}

	/// <summary>�w�肵���C���f�b�N�X�̒l��Ԃ�</summary>
	const Type& At(const Size& index) const
	{
		Buffer::const_iterator it = m_buffer.begin();
		for (Size i = 0; i < index; ++i)
		{
			++it;
		}
		return *it;
	}

private:

	Buffer m_buffer;

	Size m_bufferSize;

	bool m_isFill;
};
