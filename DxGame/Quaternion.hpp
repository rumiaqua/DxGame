# pragma once

namespace aqua
{
	class Matrix;

	class Vector2;

	class Vector3;

	class Quaternion
	{
	public:

		/// <summary>�f�t�H���g�R���X�g���N�^</summary>
		Quaternion() = default;

		/// <summary>�v�f���w�肷��</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <param name="z">z</param>
		/// <param name="w">w</param>
		Quaternion(float x, float y, float z, float w);

		/// <summary>��]������]�ʂ��w�肷��</summary>
		/// <param name="axis">��]��</param>
		/// <param name="angle">��]��</param>
		Quaternion(const Vector3& axis, float angle);

		/// <summary>DirectX�̃x�N�g������ϊ�����</summary>
		/// <param name="v">DirectX�̃x�N�g��</param>
		Quaternion(const DirectX::XMVECTOR& v);

	public:

		/// <summary>�P�ʃN�H�[�^�j�I����Ԃ�</summary>
		/// <returns>�P�ʃN�H�[�^�j�I��</returns>
		static Quaternion Identity();

		/// <summary>z����]�����N�H�[�^�j�I����Ԃ�</summary>
		/// <param name="angle">��]��</param>
		/// <returns>�N�H�[�^�j�I��</returns>
		static Quaternion Roll(float angle);

		/// <summary>x����]�����N�H�[�^�j�I����Ԃ�</summary>
		/// <param name="angle">��]��</param>
		/// <returns>�N�H�[�^�j�I��</returns>
		static Quaternion Pitch(float angle);

		/// <summary>y����]�����N�H�[�^�j�I����Ԃ�</summary>
		/// <param name="angle">��]��</param>
		/// <returns>�N�H�[�^�j�I��</returns>
		static Quaternion Yaw(float angle);

		/// <summary>3����]�����N�H�[�^�j�I����Ԃ�</summary>
		/// <param name="roll">z����]��</param>
		/// <param name="pitch">x����]��</param>
		/// <param name="yaw">y����]��</param>
		/// <returns>�N�H�[�^�j�I��</returns>
		static Quaternion RollPitchYaw(float roll, float pitch, float yaw);

		/// <summary>���K�����ꂽ�N�H�[�^�j�I����Ԃ�</summary>
		/// <param name="q">�N�H�[�^�j�I��</param>
		/// <returns>���K�����ꂽ�N�H�[�^�j�I��</returns>
		static Quaternion Normalize(const Quaternion& q);

		/// <summary>�s��ɕϊ�����</summary>
		/// <param name="q">�N�H�[�^�j�I��</param>
		/// <returns>�s��</returns>
		static Matrix ToMatrix(const Quaternion& q);

		/// <summary>�P�ʃN�H�[�^�j�I�����ǂ����Ԃ�</summary>
		/// <param name="q">�N�H�[�^�j�I��</param>
		/// <returns>�P�ʃN�H�[�^�j�I���ł����true �����łȂ����false</returns>
		static bool IsIdentity(const Quaternion& q);

	public:

		union
		{
			/// <summary>DirectX�x�N�g��</summary>
			DirectX::XMVECTOR xm;

			/// <summary>�z��</summary>
			float elm[4];

			/// <summary>�v�f</summary>
			struct
			{
				float x, y, z, w;
			};
		};
	};

	Quaternion operator * (const Quaternion& q, const Quaternion& p);

	Quaternion& operator *= (Quaternion& q, const Quaternion& p);

	Vector2 operator * (const Vector2& v, const Quaternion& q);

	Vector2 operator *= (Vector2& v, const Quaternion& q);

	Vector3 operator * (const Vector3& v, const Quaternion& q);

	Vector3 operator *= (Vector3& v, const Quaternion& q);
}
