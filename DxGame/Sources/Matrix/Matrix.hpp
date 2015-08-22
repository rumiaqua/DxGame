# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Quaternion;

	class Vector2;

	class Vector3;

	class Matrix : public XMMATRIX
	{
	public:

		/// <summary>�f�t�H���g�R���X�g���N�^</summary>
		Matrix() = default;

		/// <summary>�v�f���w��</summary>
		Matrix(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24, 
			float _31, float _32, float _33, float _34, 
			float _41, float _42, float _43, float _44);

		/// <summary>DirectX�̃x�N�g������ϊ�</summary>
		/// <param name="matrix">DirectX�̍s��</param>
		Matrix(const XMMATRIX& matrix);

		operator const float* () const;

	public:

		/// <summary>�P�ʍs���Ԃ�</summary>
		/// <returns>�P�ʍs��</returns>
		static Matrix Identity();

		/// <summary>���s�ړ��s���Ԃ�</summary>
		/// <param name="position">�ړ���</param>
		/// <returns>���s�ړ��s��</returns>
		static Matrix Translate(const Vector3& position);

		/// <summary>���s�ړ��s���Ԃ�</summary>
		/// <param name="x">x�����̈ړ���</param>
		/// <param name="y">y�����̈ړ���</param>
		/// <param name="z">z�����̈ړ���</param>
		/// <returns>���s�ړ��s��</returns>
		static Matrix Translate(float x, float y, float z);

		/// <summary>�g��k���s���Ԃ�</summary>
		/// <param name="s">�g�嗦</param>
		/// <returns>�g��k���s��</returns>
		static Matrix Scale(float scale);

		/// <summary>�g��k���s���Ԃ�</summary>
		/// <param name="scale">�g�嗦</param>
		/// <returns>�g��k���s��</returns>
		static Matrix Scale(const Vector3& scale);

		/// <summary>�g��k���s���Ԃ�</summary>
		/// <param name="x">x�����̊g�嗦</param>
		/// <param name="y">y�����̊g�嗦</param>
		/// <param name="z">z�����̊g�嗦</param>
		/// <returns>�g��k���s��</returns>
		static Matrix Scale(float x, float y, float z);

		/// <summary>X���ŉ�]</summary>
		/// <param name="angle">��]��</param>
		/// <returns>��]�s��</returns>
		static Matrix RotateX(float angle);

		/// <summary>X���ŉ�]</summary>
		/// <param name="angle">��]��</param>
		/// <returns>��]�s��</returns>
		static Matrix RotateY(float angle);

		/// <summary>X���ŉ�]</summary>
		/// <param name="angle">��]��</param>
		/// <returns>��]�s��</returns>
		static Matrix RotateZ(float angle);

		/// <summary>��]�s���Ԃ�</summary>
		/// <param name="pitchYawRoll">��]��</param>
		/// <returns>�g��k���s��</returns>
		static Matrix Rotate(const Vector3& pitchYawRoll);

		/// <summary>��]�s���Ԃ�</summary>
		/// <param name="pitch">x���̉�]��</param>
		/// <param name="yaw">y���̉�]��</param>
		/// <param name="roll">z���̉�]��</param>
		/// <returns>�g��k���s��</returns>
		static Matrix Rotate(float pitch, float yaw, float roll);

		/// <summary>��]�s���Ԃ�</summary>
		/// <param name="q">��]��</param>
		/// <returns>�g��k���s��</returns>
		static Matrix Rotate(const Quaternion& q);

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		static Matrix Transform(
			float scaling,
			const Vector3& rotation,
			const Vector3& translation);

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		static Matrix Transform(
			const Vector3& scaling,
			const Vector3& rotation,
			const Vector3& translation);

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		static Matrix Transform(
			float scaling,
			const Quaternion& rotation,
			const Vector3& translation);

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		static Matrix Transform(
			const Vector3& scaling,
			const Quaternion& rotation,
			const Vector3& translation);

	public:

		/// <summary>���s�ړ��s���Ԃ�</summary>
		/// <param name="position">�ړ���</param>
		/// <returns>���s�ړ��s��</returns>
		Matrix Translated(const Vector3& position) const;

		/// <summary>���s�ړ��s���Ԃ�</summary>
		/// <param name="x">x�����̈ړ���</param>
		/// <param name="y">y�����̈ړ���</param>
		/// <param name="z">z�����̈ړ���</param>
		/// <returns>���s�ړ��s��</returns>
		Matrix Translated(float x, float y, float z) const;

		/// <summary>�g��k���s���Ԃ�</summary>
		/// <param name="s">�g�嗦</param>
		/// <returns>�g��k���s��</returns>
		Matrix Scaled(float scale) const;

		/// <summary>�g��k���s���Ԃ�</summary>
		/// <param name="scale">�g�嗦</param>
		/// <returns>�g��k���s��</returns>
		Matrix Scaled(const Vector3& scale) const;

		/// <summary>�g��k���s���Ԃ�</summary>
		/// <param name="x">x�����̊g�嗦</param>
		/// <param name="y">y�����̊g�嗦</param>
		/// <param name="z">z�����̊g�嗦</param>
		/// <returns>�g��k���s��</returns>
		Matrix Scaled(float x, float y, float z) const;

		/// <summary>X���ŉ�]</summary>
		/// <param name="angle">��]��</param>
		/// <returns>��]�s��</returns>
		Matrix RotatedX(float angle) const;

		/// <summary>X���ŉ�]</summary>
		/// <param name="angle">��]��</param>
		/// <returns>��]�s��</returns>
		Matrix RotatedY(float angle) const;

		/// <summary>X���ŉ�]</summary>
		/// <param name="angle">��]��</param>
		/// <returns>��]�s��</returns>
		Matrix RotatedZ(float angle) const;

		/// <summary>��]�s���Ԃ�</summary>
		/// <param name="pitchYawRoll">��]��</param>
		/// <returns>�g��k���s��</returns>
		Matrix Rotated(const Vector3& pitchYawRoll) const;

		/// <summary>��]�s���Ԃ�</summary>
		/// <param name="pitch">x���̉�]��</param>
		/// <param name="yaw">y���̉�]��</param>
		/// <param name="roll">z���̉�]��</param>
		/// <returns>�g��k���s��</returns>
		Matrix Rotated(float pitch, float yaw, float roll) const;

		/// <summary>��]�s���Ԃ�</summary>
		/// <param name="q">��]��</param>
		/// <returns>�g��k���s��</returns>
		Matrix Rotated(const Quaternion& q) const;

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		Matrix Transformed(
			float scaling,
			const Vector3& rotation,
			const Vector3& translation) const;

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		Matrix Transformed(
			const Vector3& scaling,
			const Vector3& rotation,
			const Vector3& translation) const;

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		Matrix Transformed(
			float scaling,
			const Quaternion& rotation,
			const Vector3& translation) const;

		/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>�A�t�B���ϊ��s��</returns>
		Matrix Transformed(
			const Vector3& scaling,
			const Quaternion& rotation,
			const Vector3& translation) const;

	public:

		/// <summary>�������Ĉ����Ɏ��[����</summary>
		/// <param name="scaling">�g�嗦</param>
		/// <param name="rotation">��]��</param>
		/// <param name="translation">�ړ���</param>
		/// <returns>���������true �����łȂ����false</returns>
		bool Decompose(
			Vector3& scale,
			Quaternion& rotation,
			Vector3& translation) const;

		/// <summary>�s�񎮂�Ԃ�</summary>
		/// <returns>�s��</returns>
		float Determinant() const;

		/// <summary>�t�s���Ԃ�</summary>
		/// <returns>�t�s��</returns>
		Matrix Inverse() const;

		/// <summary>�s�񎮂����[���ċt�s���Ԃ�</summary>
		/// <param name="determinant">�s��</param>
		/// <returns>�t�s��</returns>
		Matrix Inverse(float& determinant) const;

		/// <summary>�]�u�s���Ԃ�</summary>
		/// <returns>�]�u�s��</returns>
		Matrix Transposed() const;

		/// <summary>�P�ʍs�񂩂ǂ�����Ԃ�</summary>
		/// <returns>�P�ʍs��ł����true �����łȂ����false</returns>
		bool IsIdentity() const;
	};

	Matrix operator * (const Matrix& m1, const Matrix& m2);

	Matrix& operator *= (Matrix& m1, const Matrix& m2);

	Vector3 operator * (const Vector3& v, const Matrix& matrix);

	Vector3& operator *= (Vector3& v, const Matrix& matrix);

	Vector2 operator * (const Vector2& v, const Matrix& matrix);

	Vector2& operator *= (Vector2& v, const Matrix& matrix);
}
