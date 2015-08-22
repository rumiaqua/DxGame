# pragma once

# include <DxLib.h>

DxLib::VECTOR To(const aqua::Vector3& vec)
{
	return { vec.x, vec.y, vec.z };
}

DxLib::MATRIX To(const aqua::Matrix& matrix)
{
	MATRIX m;
	const size_t Size = sizeof(float) * 16;
	memcpy_s(m.m, Size, matrix.m, Size);
	return m;
}
