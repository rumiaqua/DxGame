# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Vector2;

	class Vector4;

	class Vector3
	{
	public:

		/// <summary>��x�N�g��</summary>
		static const Vector3 Zero;

		/// <summary>(1, 1, 1)�̃x�N�g��</summary>
		static const Vector3 One;

		/// <summary>(-1, 0, 0)�̃x�N�g��</summary>
		static const Vector3 Left;

		/// <summary>(1, 0, 0)�̃x�N�g��</summary>
		static const Vector3 Right;

		/// <summary>(0, 1, 0)�̃x�N�g��</summary>
		static const Vector3 Up;

		/// <summary>(0, -1, 0)�̃x�N�g��</summary>
		static const Vector3 Down;

		/// <summary>(0, 0, 1)�̃x�N�g��</summary>
		static const Vector3 Forward;

		/// <summary>(0, 0, -1)�̃x�N�g��</summary>
		static const Vector3 Backward;

	public:

		/// <summary>�f�t�H���g�R���X�g���N�^</summary>
		Vector3();

		/// <summary>�R�s�[�R���X�g���N�^</summary>
		/// <param name="v">�x�N�g��</param>
		Vector3(const Vector3& other);

		/// <summary>DirectX�x�N�g������ϊ�</summary>
		/// <param name="v">DirectX�x�N�g��</param>
		Vector3(const XMVECTOR& xm);

		/// <summary>�񎟌��x�N�g������ϊ�</summary>
		/// <param name="v">�񎟌��x�N�g��</param>
		/// <param name="z">z�v�f</param>
		Vector3(const Vector2& v, float z = -1.0f);

		/// <summary>�l�����x�N�g������ϊ�</summary>
		/// <param name="v">�l�����x�N�g��</param>
		Vector3(const Vector4& v);

		/// <summary>�v�f���w�肷��</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <param name="z">z</param>
		Vector3(float x, float y, float z);

	public:

		Vector3& operator = (const Vector3& other);

	public:

		/// <summary>�����̓���Ԃ�</summary>
		/// <returns>�����̓��</returns>
		float LengthSquared() const;

		/// <summary>������Ԃ�</summary>
		/// <returns>����</returns>
		float Length() const;

		/// <summary>���K�����ꂽ�x�N�g����Ԃ�</summary>
		/// <returns>���K�����ꂽ�x�N�g��</returns>
		Vector3 Normalized() const;

		/// <summary>0����1�̊ԂɃN�����v���ꂽ�x�N�g����Ԃ�</summary>
		/// <returns>0����1�̊ԂɃN�����v���ꂽ�x�N�g��</returns>
		Vector3 Saturated() const;

		/// <summary>�w�茅���łȂ炵���x�N�g����Ԃ�</summary>
		/// <returns>�Ȃ炵���x�N�g��</returns>
		Vector3 Smoothed(int f = -4) const;

		/// <summary>���ς�Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>����</returns>
		float Dot(const Vector3& v) const;

		/// <summary>�O�ς�Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>�O��</returns>
		Vector3 Cross(const Vector3& v) const;

		/// <summary>DirectX�̃x�N�g���ɕϊ�����</summary>
		/// <param name="w">w�v�f�̒l</param>
		/// <returns>DirectX�̃x�N�g��</returns>
		XMVECTOR ToVector(float w = 1.0f) const;

		/// <summary>������Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>����</returns>
		float Distance(const Vector3& v) const;

		/// <summary>�ǂ���x�N�g����Ԃ�</summary>
		/// <param name="normal">�@���x�N�g��</param>
		/// <returns>�ǂ���x�N�g��</returns>
		Vector3 Scratched(const Vector3& normal) const;

		/// <summary>���˃x�N�g����Ԃ�</summary>
		/// <param name="normal">�@���x�N�g��</param>
		/// <returns>���˃x�N�g��</returns>
		Vector3 Reflected(const Vector3& normal) const;

		/// <summary>�ˉe�x�N�g����Ԃ�</summary>
		/// <param name="target">�Ώۂ̃x�N�g��</param>
		/// <returns>�ˉe�x�N�g��</returns>
		Vector3 Projected(const Vector3& target) const;

	public:

		/// <summary>���K������</summary>
		/// <returns>�x�N�g��</returns>
		Vector3& Normalize();

		/// <summary>0����1�̊ԂɃN�����v����</summary>
		/// <returns>�x�N�g��</returns>
		Vector3& Saturate();

		/// <summary>�w�茅���łȂ炷</summary>
		/// <returns>�x�N�g��</returns>
		Vector3& Smooth(int f = -4);

		/// <summary>�ǂ���x�N�g�����v�Z����</summary>
		/// <param name="normal">�@���x�N�g��</param>
		/// <returns>�x�N�g��</returns>
		Vector3& Scratch(const Vector3& normal);

		/// <summary>���˃x�N�g�����v�Z����</summary>
		/// <param name="normal">�@���x�N�g��</param>
		/// <returns>�x�N�g��</returns>
		Vector3& Reflect(const Vector3& normal);

		/// <summary>�ˉe�x�N�g�����v�Z����</summary>
		/// <param name="target">�Ώۂ̃x�N�g��</param>
		/// <returns>�x�N�g��</returns>
		Vector3& Project(const Vector3& target);

	public:

		/// <summary>���`��Ԃ����x�N�g����Ԃ�</summary>
		/// <param name="v1">�n�_</param>
		/// <param name="v2">�I�_</param>
		/// <param name="t">�䗦</param>
		/// <returns>��ԃx�N�g��</returns>
		static Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

	public:

		union
		{
			/// <summary>�F</summary>
			struct
			{
				float r;

				float g;

				float b;
			};

			/// <summary>���W</summary>
			struct
			{
				float x;

				float y;

				float z;
			};

			/// <summary>�z��</summary>
			float elm[3];
		};
	};

	bool operator == (const Vector3& v1, const Vector3& v2);

	bool operator != (const Vector3& v1, const Vector3& v2);

	Vector3 operator + (const Vector3& v);

	Vector3 operator - (const Vector3& v);

	Vector3& operator += (Vector3& v1, const Vector3& v2);

	Vector3& operator -= (Vector3& v1, const Vector3& v2);

	Vector3& operator *= (Vector3& v, float s);

	Vector3& operator *= (float s, Vector3& v);

	Vector3& operator /= (Vector3& v, float s);

	Vector3 operator + (const Vector3& v1, const Vector3& v2);

	Vector3 operator - (const Vector3& v1, const Vector3& v2);

	Vector3 operator * (const Vector3& v, float s);

	Vector3 operator * (float s, const Vector3& v);

	Vector3 operator / (const Vector3& v, float s);
}
