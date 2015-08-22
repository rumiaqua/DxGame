# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Vector2;

	class Vector3;

	class Vector4
	{
	public:

		/// <summary>��x�N�g��</summary>
		static const Vector4 Zero;

		/// <summary>(1, 1, 1, 1)�̃x�N�g��</summary>
		static const Vector4 One;

	public:

		/// <summary>�f�t�H���g�R���X�g���N�^</summary>
		Vector4();

		/// <summary>�R�s�[�R���X�g���N�^</summary>
		/// <param name="v">�x�N�g��</param>
		Vector4(const Vector4& other);

		/// <summary>DirectX�x�N�g������ϊ�</summary>
		/// <param name="v">DirectX�x�N�g��</param>
		Vector4(const XMVECTOR& xm);

		/// <summary>�񎟌��x�N�g���Q����ϊ�</summary>
		/// <param name="v1">xy�񎟌��x�N�g��</param>
		/// <param name="v2">zw�񎟌��x�N�g��</param>
		Vector4(const Vector2& v1, const Vector2& v2);

		/// <summary>�O�����x�N�g������ϊ�</summary>
		/// <param name="v">�O�����x�N�g��</param>
		/// <param name="w">w�v�f</param>
		Vector4(const Vector3& v, float w);

		/// <summary>�v�f���w�肷��</summary>
		/// <param name="x">x�v�f</param>
		/// <param name="y">y�v�f</param>
		/// <param name="z">z�v�f</param>
		/// <param name="w">w�v�f</param>
		Vector4(float x, float y, float z, float w);

	public:

		Vector4& operator = (const Vector4& other);

	public:

		operator XMVECTOR();

		operator const XMVECTOR() const;

		operator float* ();

		operator const float* () const;

		XMVECTOR* operator & ();

		const XMVECTOR* operator & () const;

	public:

		/// <summary>�����̓���Ԃ�</summary>
		/// <returns>�����̓��</returns>
		float LengthSquared() const;

		/// <summary>������Ԃ�</summary>
		/// <returns>����</returns>
		float Length() const;

		/// <summary>���K�����ꂽ�x�N�g����Ԃ�</summary>
		/// <returns>���K�����ꂽ�x�N�g��</returns>
		Vector4 Normalized() const;

		/// <summary>0����1�̊ԂɃN�����v���ꂽ�x�N�g����Ԃ�</summary>
		/// <returns>0����1�̊ԂɃN�����v���ꂽ�x�N�g��</returns>
		Vector4 Saturated() const;

		/// <summary>�w�茅���łȂ炵���x�N�g����Ԃ�</summary>
		/// <returns>�Ȃ炵���x�N�g��</returns>
		Vector4 Smoothed(int f = -4) const;

		/// <summary>���ς�Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>����</returns>
		float Dot(const Vector4& v) const;

		/// <summary>������Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>����</returns>
		float Distance(const Vector4& v) const;

	public:

		/// <summary>���K������</summary>
		/// <returns>�x�N�g��</returns>
		Vector4& Normalize();

		/// <summary>0����1�̊ԂɃN�����v����</summary>
		/// <returns>�x�N�g��</returns>
		Vector4& Saturate();

		/// <summary>�w�茅���łȂ炷</summary>
		/// <returns>�x�N�g��</returns>
		Vector4& Smooth(int f = -4);

	public:

		/// <summary>���`��Ԃ����x�N�g����Ԃ�</summary>
		/// <param name="v1">�n�_</param>
		/// <param name="v2">�I�_</param>
		/// <param name="t">�䗦</param>
		/// <returns>��ԃx�N�g��</returns>
		static Vector4 Lerp(const Vector4& v1, const Vector4& v2, float t);

	public:

		union
		{
			/// <summary>�F</summary>
			struct
			{
				float r;

				float g;

				float b;

				float a;
			};

			/// <summary>���W</summary>
			struct
			{
				float x;

				float y;

				float z;
				
				float w;
			};

			/// <summary>�z��</summary>
			float elm[4];

			XMVECTOR xm;
		};
	};

	bool operator == (const Vector4& v1, const Vector4& v2);

	bool operator != (const Vector4& v1, const Vector4& v2);

	Vector4 operator + (const Vector4& v);

	Vector4 operator - (const Vector4& v);

	Vector4& operator += (Vector4& v1, const Vector4& v2);

	Vector4& operator -= (Vector4& v1, const Vector4& v2);

	Vector4& operator *= (Vector4& v, float s);

	Vector4& operator *= (float s, Vector4& v);

	Vector4& operator /= (Vector4& v, float s);

	Vector4 operator + (const Vector4& v1, const Vector4& v2);

	Vector4 operator - (const Vector4& v1, const Vector4& v2);

	Vector4 operator * (const Vector4& v, float s);

	Vector4 operator * (float s, const Vector4& v);

	Vector4 operator / (const Vector4& v, float s);
}
