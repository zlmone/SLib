/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#include "slib/math/matrix3.h"

namespace slib
{

	template <class T>
	SLIB_ALIGN(8) T Matrix3T<T>::_zero[9] = {
		0, 0, 0
		, 0, 0, 0
		, 0, 0, 0 };

	template <class T>
	SLIB_ALIGN(8) T Matrix3T<T>::_one[9] = {
		1, 1, 1
		, 1, 1, 1
		, 1, 1, 1 };

	template <class T>
	SLIB_ALIGN(8) T Matrix3T<T>::_identity[9] = {
		1, 0, 0
		, 0, 1, 0
		, 0, 0, 1 };


	template <class T>
	Vector3T<T> Matrix3T<T>::getRow0() const noexcept
	{
		return {m00, m01, m02};
	}

	template <class T>
	void Matrix3T<T>::setRow0(const Vector3T<T>& v) noexcept
	{
		m00 = v.x;
		m01 = v.y;
		m02 = v.z;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::getRow1() const noexcept
	{
		return {m10, m11, m12};
	}

	template <class T>
	void Matrix3T<T>::setRow1(const Vector3T<T>& v) noexcept
	{
		m10 = v.x;
		m11 = v.y;
		m12 = v.z;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::getRow2() const noexcept
	{
		return {m20, m21, m22};
	}

	template <class T>
	void Matrix3T<T>::setRow2(const Vector3T<T>& v) noexcept
	{
		m20 = v.x;
		m21 = v.y;
		m22 = v.z;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::getRow(sl_uint32 index) const noexcept
	{
		const T* t = &m00 + (index + (index << 1));
		return {t[0], t[1], t[2]};
	}

	template <class T>
	void Matrix3T<T>::setRow(sl_uint32 index, const Vector3T<T>& v) noexcept
	{
		T* t = &m00 + (index + (index << 1));
		t[0] = v.x;
		t[1] = v.y;
		t[2] = v.z;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::getColumn0() const noexcept
	{
		return {m00, m10, m20};
	}

	template <class T>
	void Matrix3T<T>::setColumn0(const Vector3T<T>& v) noexcept
	{
		m00 = v.x;
		m10 = v.y;
		m20 = v.z;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::getColumn1() const noexcept
	{
		return {m01, m11, m21};
	}

	template <class T>
	void Matrix3T<T>::setColumn1(const Vector3T<T>& v) noexcept
	{
		m01 = v.x;
		m11 = v.y;
		m21 = v.z;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::getColumn2() const noexcept
	{
		return {m02, m12, m22};
	}

	template <class T>
	void Matrix3T<T>::setColumn2(const Vector3T<T>& v) noexcept
	{
		m02 = v.x;
		m12 = v.y;
		m22 = v.z;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::getColumn(sl_uint32 index) const noexcept
	{
		const T* t = &m00 + index;
		return {t[0], t[3], t[6]};
	}

	template <class T>
	void Matrix3T<T>::setColumn(sl_uint32 index, const Vector3T<T>& v) noexcept
	{
		T* t = &m00 + index;
		t[0] = v.x;
		t[3] = v.y;
		t[6] = v.z;
	}

	template <class T>
	T Matrix3T<T>::getElement(sl_uint32 row, sl_uint32 column) const noexcept
	{
		return (&m00)[row + (row << 1) + column];
	}

	template <class T>
	void Matrix3T<T>::setElement(sl_uint32 row, sl_uint32 column, const T& v) noexcept
	{
		(&m00)[row + (row << 1) + column] = v;
	}

	template <class T>
	void Matrix3T<T>::add(const Matrix3T<T>& other) noexcept
	{
		m00 += other.m00; m01 += other.m01; m02 += other.m02;
		m10 += other.m10; m11 += other.m11; m12 += other.m12;
		m20 += other.m20; m21 += other.m21; m22 += other.m22;
	}

	template <class T>
	void Matrix3T<T>::subtract(const Matrix3T<T>& other) noexcept
	{
		m00 -= other.m00; m01 -= other.m01; m02 -= other.m02;
		m10 -= other.m10; m11 -= other.m11; m12 -= other.m12;
		m20 -= other.m20; m21 -= other.m21; m22 -= other.m22;
	}

	template <class T>
	void Matrix3T<T>::multiply(T value) noexcept
	{
		m00 *= value; m01 *= value; m02 *= value;
		m10 *= value; m11 *= value; m12 *= value;
		m20 *= value; m21 *= value; m22 *= value;
	}

	template <class T>
	void Matrix3T<T>::divide(T value) noexcept
	{
		m00 /= value; m01 /= value; m02 /= value;
		m10 /= value; m11 /= value; m12 /= value;
		m20 /= value; m21 /= value; m22 /= value;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::multiplyLeft(const Vector3T<T>& v) const noexcept
	{
		T _x = v.x * m00 + v.y * m10 + v.z * m20;
		T _y = v.x * m01 + v.y * m11 + v.z * m21;
		T _z = v.x * m02 + v.y * m12 + v.z * m22;
		return {_x, _y, _z};
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::multiplyRight(const Vector3T<T>& v) const noexcept
	{
		T _x = m00 * v.x + m01 * v.y + m02 * v.z;
		T _y = m10 * v.x + m11 * v.y + m12 * v.z;
		T _z = m20 * v.x + m21 * v.y + m22 * v.z;
		return {_x, _y, _z};
	}

	template <class T>
	Vector2T<T> Matrix3T<T>::transformPosition(T x, T y) const noexcept
	{
		T _x = x * m00 + y * m10 + m20;
		T _y = x * m01 + y * m11 + m21;
		return {_x, _y};
	}

	template <class T>
	Vector2T<T> Matrix3T<T>::transformPosition(const Vector2T<T>& v) const noexcept
	{
		T _x = v.x * m00 + v.y * m10 + m20;
		T _y = v.x * m01 + v.y * m11 + m21;
		return {_x, _y};
	}

	template <class T>
	Vector2T<T> Matrix3T<T>::transformDirection(T x, T y) const noexcept
	{
		T _x = x * m00 + y * m10;
		T _y = x * m01 + y * m11;
		return {_x, _y};
	}

	template <class T>
	Vector2T<T> Matrix3T<T>::transformDirection(const Vector2T<T>& v) const noexcept
	{
		T _x = v.x * m00 + v.y * m10;
		T _y = v.x * m01 + v.y * m11;
		return {_x, _y};
	}

	template <class T>
	void Matrix3T<T>::multiply(const Matrix3T<T>& m) noexcept
	{
		T v0, v1, v2;
		v0 = m00 * m.m00 + m01 * m.m10 + m02 * m.m20;
		v1 = m00 * m.m01 + m01 * m.m11 + m02 * m.m21;
		v2 = m00 * m.m02 + m01 * m.m12 + m02 * m.m22;
		m00 = v0; m01 = v1; m02 = v2;
		v0 = m10 * m.m00 + m11 * m.m10 + m12 * m.m20;
		v1 = m10 * m.m01 + m11 * m.m11 + m12 * m.m21;
		v2 = m10 * m.m02 + m11 * m.m12 + m12 * m.m22;
		m10 = v0; m11 = v1; m12 = v2;
		v0 = m20 * m.m00 + m21 * m.m10 + m22 * m.m20;
		v1 = m20 * m.m01 + m21 * m.m11 + m22 * m.m21;
		v2 = m20 * m.m02 + m21 * m.m12 + m22 * m.m22;
		m20 = v0; m21 = v1; m22 = v2;
	}

	template <class T>
	T Matrix3T<T>::getDeterminant() const noexcept
	{
		return SLIB_MATH_MATRIX_DETERMINANT3(m00, m01, m02,
											m10, m11, m12,
											m20, m21, m22);
	}

	template <class T>
	void Matrix3T<T>::makeInverse() noexcept
	{
		T A00 = SLIB_MATH_MATRIX_DETERMINANT2(m11, m12, m21, m22);
		T A01 = -SLIB_MATH_MATRIX_DETERMINANT2(m10, m12, m20, m22);
		T A02 = SLIB_MATH_MATRIX_DETERMINANT2(m10, m11, m20, m21);
		T A10 = -SLIB_MATH_MATRIX_DETERMINANT2(m01, m02, m21, m22);
		T A11 = SLIB_MATH_MATRIX_DETERMINANT2(m00, m02, m20, m22);
		T A12 = -SLIB_MATH_MATRIX_DETERMINANT2(m00, m01, m20, m21);
		T A20 = SLIB_MATH_MATRIX_DETERMINANT2(m01, m02, m11, m12);
		T A21 = -SLIB_MATH_MATRIX_DETERMINANT2(m00, m02, m10, m12);
		T A22 = SLIB_MATH_MATRIX_DETERMINANT2(m00, m01, m10, m11);
		T D = 1 / (m00*A00 + m01*A01 + m02*A02);
		m00 = D * A00; m01 = D * A10; m02 = D * A20;
		m10 = D * A01; m11 = D * A11; m12 = D * A21;
		m20 = D * A02; m21 = D * A12; m22 = D * A22;
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::inverse() const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.makeInverse();
		return ret;
	}

	template <class T>
	void Matrix3T<T>::makeTranspose() noexcept
	{
		T	f;
		f = m01; m01 = m10; m10 = f;
		f = m02; m02 = m20; m20 = f;
		f = m12; m12 = m21; m21 = f;
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::transpose() const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.makeTranspose();
		return ret;
	}

	template <class T>
	void Matrix3T<T>::makeInverseTranspose() noexcept
	{
		makeInverse();
		makeTranspose();
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::inverseTranspose() const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.makeInverse();
		ret.makeTranspose();
		return ret;
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::lerp(const Matrix3T<T>& target, float factor) const noexcept
	{
		return {
			SLIB_LERP(m00, target.m00, factor), SLIB_LERP(m01, target.m01, factor), SLIB_LERP(m02, target.m02, factor),
			SLIB_LERP(m10, target.m10, factor), SLIB_LERP(m11, target.m11, factor), SLIB_LERP(m12, target.m12, factor),
			SLIB_LERP(m20, target.m20, factor), SLIB_LERP(m21, target.m21, factor), SLIB_LERP(m22, target.m22, factor)};
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::operator+(const Matrix3T<T>& other) const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.add(other);
		return ret;
	}

	template <class T>
	Matrix3T<T>& Matrix3T<T>::operator+=(const Matrix3T<T>& other) noexcept
	{
		add(other);
		return *this;
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::operator-(const Matrix3T<T>& other) const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.subtract(other);
		return ret;
	}

	template <class T>
	Matrix3T<T>& Matrix3T<T>::operator-=(const Matrix3T<T>& other) noexcept
	{
		subtract(other);
		return *this;
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::operator-() const noexcept
	{
		Matrix3T<T> ret(Matrix3T<T>::zero());
		ret.subtract(*this);
		return ret;
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::operator*(T value) const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.multiply(value);
		return ret;
	}

	template <class T>
	Matrix3T<T>& Matrix3T<T>::operator*=(T value) noexcept
	{
		multiply(value);
		return *this;
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::operator/(T value) const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.divide(value);
		return ret;
	}

	template <class T>
	Matrix3T<T>& Matrix3T<T>::operator/=(T value) noexcept
	{
		divide(value);
		return *this;
	}

	template <class T>
	Vector3T<T> Matrix3T<T>::operator*(const Vector3T<T>& v) const noexcept
	{
		return multiplyRight(v);
	}

	template <class T>
	Matrix3T<T> Matrix3T<T>::operator*(const Matrix3T<T>& other) const noexcept
	{
		Matrix3T<T> ret(*this);
		ret.multiply(other);
		return ret;
	}

	template <class T>
	Matrix3T<T>& Matrix3T<T>::operator*=(const Matrix3T<T>& other) noexcept
	{
		multiply(other);
		return *this;
	}

	template <class T>
	sl_bool Matrix3T<T>::operator==(const Matrix3T<T>& other) const noexcept
	{
		return m00 == other.m00 && m01 == other.m01 && m02 == other.m02 &&
			m10 == other.m10 && m11 == other.m11 && m12 == other.m12 &&
			m20 == other.m20 && m21 == other.m21 && m22 == other.m22;
	}

	template <class T>
	sl_bool Matrix3T<T>::operator!=(const Matrix3T<T>& other) const noexcept
	{
		return m00 != other.m00 || m01 != other.m01 || m02 != other.m02 ||
			m10 != other.m10 || m11 != other.m11 || m12 != other.m12 ||
			m20 != other.m20 || m21 != other.m21 || m22 != other.m22;
	}

	SLIB_DEFINE_GEOMETRY_TYPE(Matrix3)

}
