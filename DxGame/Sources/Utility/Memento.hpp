# pragma once

# include <deque>

/// <summary>メメントパターン</summary>
/// <summary>型に対しデフォルトコンストラクタを要求します</summary>
template <typename Type>
class Memento
{
private:

	using Buffer = std::deque<Type>;

	using Size = typename Buffer::size_type;

public:

	/// <summary>コンストラクタ</summary>
	/// <param name="bufferSize">バッファのサイズ</param>
	/// <param name="isFill">バッファを埋めるかどうか</param>
	Memento(const Size& bufferSize, bool isFill = true)
		: m_buffer()
		, m_bufferSize(bufferSize + 1)
		, m_isFill(isFill)
	{
		TryFill(true);
	}

public:

	/// <summary>バッファのサイズを変更する</summary>
	void ChangeBufferSize(const Size& bufferSize)
	{
		m_bufferSize = bufferSize + 1;
		Resolve();
		TryFill(false);
	}

	/// <summary>値を保存する</summary>
	const Type& Save(const Type& value)
	{
		return Save(value, true);
	}

	/// <summary>値を内部で構築して保存する</summary>
	template <typename ...Args>
	void Emplace(Args&& ...args)
	{
		m_buffer.emplace_back(std::forward<Args>(args)...);
		Resolve();
	}

	/// <summary>履歴を辿る</summary>
	const Type& History(const Size& numPrevious)
	{
		// 一つも保存されていない場合、エラー
		if (Count() == 0)
		{
			throw std::out_of_range("履歴が保存されていません");
		}

		// 保存数より多く遡ろうとした場合、最も古いデータを返す
		Size index = Count() > numPrevious ? Count() - numPrevious : Count();
		index -= 1;
		Buffer::iterator it = m_buffer.begin();
		for (Size i = 0; i < index; ++i)
		{
			++it;
		}
		return *it;
	}

	/// <summary>履歴から復元する</summary>
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

	/// <summary>値を保存する</summary>
	/// <param name="isPost">末尾に追加するかどうか</param>
	const Type& Save(const Type& value, bool isPost)
	{
		isPost ? m_buffer.push_back(value) : m_buffer.push_front(value);
		Resolve();
		return m_buffer.back();
	}

	/// <summary>オーバーフローを解決する</summary>
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

	/// <summary>バッファに保存されている値の数を返す</summary>
	Size Count() const
	{
		return m_buffer.size();
	}

	/// <summary>許容されているサイズを返す</summary>
	Size Capacity() const
	{
		return m_bufferSize - 1;
	}

	/// <summary>値で埋める</summary>
	/// <param name="isPost">末尾に追加するかどうか</param>
	void Fill(bool isPost)
	{
		Size loop = Capacity() - Count();
		for (Size i = 0; i < loop; ++i)
		{
			Save(Type(), isPost);
		}
	}

	/// <summary>値で埋めるか試行する</summary>
	void TryFill(bool isPost)
	{
		if (m_isFill)
		{
			Fill(isPost);
		}
	}

	/// <summary>指定したインデックスの値を返す</summary>
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
