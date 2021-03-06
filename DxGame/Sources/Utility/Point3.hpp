# pragma once

# include <ostream>

// -------------------------------------------------------------------
// 前置宣言
// -------------------------------------------------------------------
class Point4;
class Vector3;
class String;

/// <summary>三次元点</summary>
class Point3
{
public:

	/// <summary>(0, 0, 0)で初期化された点を返す</summary>
	static const Point3& Zero();

	/// <summary>(1, 1, 1)で初期化された点を返す</summary>
	static const Point3& One();

	/// <summary>(-1, 0, 0)で初期化された点を返す</summary>
	static const Point3& Left();

	/// <summary>(1, 0, 0)で初期化された点を返す</summary>
	static const Point3& Right();

	/// <summary>(0, 1, 0)で初期化された点を返す</summary>
	static const Point3& Up();

	/// <summary>(0, -1, 0)で初期化された点を返す</summary>
	static const Point3& Down();

	/// <summary>(0, 0, 1)で初期化された点を返す</summary>
	static const Point3& Forward();

	/// <summary>(0, 0, -1)で初期化された点を返す</summary>
	static const Point3& Backward();

public:

	/// <summary>コンストラクタ</summary>
	Point3();

	/// <summary>コピーコンストラクタ</summary>
	Point3(const Point3& v);

	/// <summary>要素を指定して構築する</summary>
	Point3(int x, int y, int z);

	/// <summary>四次元点から構築する</summary>
	explicit Point3(const Point4& v);

	/// <summary>三次元ベクトルから構築する</summary>
	explicit Point3(const Vector3& v);

	/// <summary>代入演算子</summary>
	Point3& operator = (const Point3& v);

public:

	/// <summary>配列に変換する</summary>
	operator int* ();

	/// <summary>配列に変換する</summary>
	operator const int* () const;

public:

	/// <summary>内積を返す</summary>
	/// <param name="v">点</param>
	int dot(const Point3& v) const;

	/// <summary>外積を返す</summary>
	/// <param name="v">点</param>
	Point3 cross(const Point3& v) const;

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">点</param>
	int lengthSquared() const;

	/// <summary>長さを返す</summary>
	/// <param name="v">点</param>
	float length() const;

public:

	/// <summary>内積を返す</summary>
	/// <param name="v1">点</param>
	/// <param name="v2">点</param>
	static int Dot(const Point3& v1, const Point3& v2);

	/// <summary>外積を返す</summary>
	static Point3 Cross(const Point3& v1, const Point3& v2);

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">点</param>
	static int LengthSquared(const Point3& v);

	/// <summary>長さを返す</summary>
	/// <param name="v">点</param>
	static float Length(const Point3& v);

public:

	union
	{
		int elm[3];

		int mat[1][3];

		struct
		{
			int r, g, b;
		};

		struct
		{
			int x, y, z;
		};
	};
};

bool operator == (const Point3& v1, const Point3& v2);

bool operator != (const Point3& v1, const Point3& v2);

Point3 operator + (const Point3& v);

Point3 operator - (const Point3& v);

Point3& operator += (Point3& v1, const Point3& v2);

Point3& operator -= (Point3& v1, const Point3& v2);

Point3& operator *= (Point3& v1, const Point3& v2);

Point3& operator *= (Point3& v, int s);

Point3& operator /= (Point3& v1, const Point3& v2);

Point3& operator /= (Point3& v, int s);

Point3 operator + (const Point3& v1, const Point3& v2);

Point3 operator - (const Point3& v1, const Point3& v2);

Point3 operator * (const Point3& v1, const Point3& v2);

Point3 operator * (const Point3& v, int s);

Point3 operator * (int s, const Point3& v);

Point3 operator / (const Point3& v1, const Point3& v2);

Point3 operator / (const Point3& v, int s);

std::ostream& operator << (std::ostream& stream, const Point3& v);
