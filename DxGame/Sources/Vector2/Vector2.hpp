# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Vector3;

	class Vector2
	{
	public:

		/// <summary>��x�N�g��</summary>
		static const Vector2 Zero;

		/// <summary>(1, 1)�̃x�N�g��</summary>
		static const Vector2 One;

		/// <summary>(-1, 0)�̃x�N�g��</summary>
		static const Vector2 Left;

		/// <summary>(1, 0)�̃x�N�g��</summary>
		static const Vector2 Right;

		/// <summary>(0, -1)�̃x�N�g��</summary>
		static const Vector2 Up;

		/// <summary>(0, 1)�̃x�N�g��</summary>
		static const Vector2 Down;

		// constructor
	public:

		/// <summary>�f�t�H���g�R���X�g���N�^</summary>
		Vector2();

		/// <summary>�R�s�[�R���X�g���N�^</summary>
		/// <param name="v">�x�N�g��</param>
		Vector2(const Vector2& other);

		/// <summary>DirectX�x�N�g������ϊ�</summary>
		/// <param name="v">DirectX�x�N�g��</param>
		Vector2(const XMVECTOR& xm);

		/// <summary>�v�f���w�肷��</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		Vector2(float x, float y);

		/// <summary>�R�s�[���Z�q</summary>
		/// <param name="other">�x�N�g��</param>
		/// <returns>���g</returns>
		Vector2& operator = (const Vector2& other);

	public:

		/// <summary>�����̓���Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>�����̓��</returns>
		static float LengthSquared(const Vector2& v);

		/// <summary>������Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>����</returns>
		static float Length(const Vector2& v);

		/// <summary>���K�����ꂽ�x�N�g����Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>���K�����ꂽ�x�N�g��</returns>
		static Vector2 Normalize(const Vector2& v);

		/// <summary>0����1�̊ԂɃN�����v���ꂽ�x�N�g����Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>0����1�̊ԂɃN�����v���ꂽ�x�N�g��</returns>
		static Vector2 Saturate(const Vector2& v);

		/// <summary>�w�茅���łȂ炵���x�N�g����Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>�Ȃ炵���x�N�g��</returns>
		static Vector2 Smooth(const Vector2& v, int f = -4);

		// binary math method

		/// <summary>���ς�Ԃ�</summary>
		/// <param name="v1">�x�N�g��</param>
		/// <param name="v2">�x�N�g��</param>
		/// <returns>����</returns>
		static float Dot(const Vector2& v1, const Vector2& v2);

		/// <summary>�O�ς�Ԃ�</summary>
		/// <param name="v1">�x�N�g��</param>
		/// <param name="v2">�x�N�g��</param>
		/// <returns>�O��</returns>
		static float Cross(const Vector2& v1, const Vector2& v2);

		/// <summary>������Ԃ�</summary>
		/// <param name="v1">�x�N�g��</param>
		/// <param name="v2">�x�N�g��</param>
		/// <returns>����</returns>
		static float Distance(const Vector2& v1, const Vector2& v2);

		/// <summary>���`��Ԃ����x�N�g����Ԃ�</summary>
		/// <param name="v1">�n�_</param>
		/// <param name="v2">�I�_</param>
		/// <param name="t">�䗦</param>
		/// <returns>��ԃx�N�g��</returns>
		static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t);

	public:

		union
		{
			/// <summary>UV</summary>
			struct
			{
				float u;

				float v;
			};

			/// <summary>���W</summary>
			struct
			{
				float x;

				float y;
			};

			/// <summary>�z��</summary>
			float elm[2];
		};
	};

	bool operator == (const Vector2& v1, const Vector2& v2);

	bool operator != (const Vector2& v1, const Vector2& v2);

	Vector2 operator + (const Vector2& v);

	Vector2 operator - (const Vector2& v);

	Vector2& operator += (Vector2& v1, const Vector2& v2);

	Vector2& operator -= (Vector2& v1, const Vector2& v2);

	Vector2& operator *= (Vector2& v, float s);

	Vector2& operator *= (float s, Vector2& v);

	Vector2& operator /= (Vector2& v, float s);

	Vector2 operator + (const Vector2& v1, const Vector2& v2);

	Vector2 operator - (const Vector2& v1, const Vector2& v2);

	Vector2 operator * (const Vector2& v, float s);

	Vector2 operator * (float s, const Vector2& v);

	Vector2 operator / (const Vector2& v, float s);
}
