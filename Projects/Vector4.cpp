/*************************************************************************
> File Name: Vector2.cpp
> Project Name: CubbyFlow
> Author: Dongmin Kim
> Purpose: 4-D vector class.
> Created Time: 2017/02/26
> Copyright (c) 2017, Dongmin Kim
*************************************************************************/
#include<Vector\Vector4.h>

namespace CubbyFlow
{
	template <typename T>
	Vector<T, 4>::Vector() :
		x(0), y(0), z(0), w(0)
	{
		// Do nothing
	}

	template <typename T>
	Vector<T, 4>::Vector(T newX, T newY, T newZ, T newW) :
		x(newX), y(newY), z(newZ), w(newW)
	{
		// Do nothing
	}

	template <typename T>
	template <typename U>
	Vector<T, 4>::Vector(const std::initializer_list<U>& list)
	{
		Set(list);
	}

	template <typename T>
	Vector<T, 4>::Vector(const Vector& v) :
		x(v.x), y(v.y), z(v.z), w(v.w)
	{
		// Do nothing
	}

	template <typename T>
	Vector<T, 4>::Vector(const Vector<T, 3>& pt, T newW) :
		x(pt.x), y(pt.y), z(pt.z), w(newW)
	{
		// Do nothing
	}

	template <typename T>
	void Vector<T, 4>::Set(T s)
	{
		x = s;
		y = s;
		z = s;
		w = s;
	}

	template <typename T>
	void Vector<T, 4>::Set(T newX, T newY, T newZ, T newW)
	{
		x = newX;
		y = newY;
		z = newZ;
		w = newW;
	}

	template <typename T>
	void Vector<T, 4>::Set(const Vector<T, 3>& pt, T newW)
	{
		x = pt.x;
		y = pt.y;
		z = pt.z;
		w = newW;
	}


	template <typename T>
	template <typename U>
	void Vector<T, 4>::Set(const std::initializer_list<U>& list)
	{
		assert(list.size() >= 4);

		auto inputElem = list.begin();
		x = static_cast<T>(*inputElem);
		y = static_cast<T>(*(++inputElem));
		z = static_cast<T>(*(++inputElem));
		w = static_cast<T>(*(++inputElem));
	}

	template <typename T>
	void Vector<T, 4>::Set(const Vector& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	template <typename T>
	void Vector<T, 4>::SetZero()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template <typename T>
	void Vector<T, 4>::Normalize()
	{
		x /= Length();
		y /= Length();
		z /= Length();
		w /= Length();
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Add(T v) const
	{
		return Vector(x + v, y + v, z + v, w + v);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Add(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Sub(T v) const
	{
		return Vector(x - v, y - v, z - v, w - v);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Sub(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Mul(T v) const
	{
		return Vector(x * v, y * v, z * v, w * v);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Mul(const Vector& v) const
	{
		return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Div(T v) const
	{
		return Vector(x / v, y / v, z / v, w / v);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Div(const Vector& v) const
	{
		return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	template <typename T>
	T Vector<T, 4>::Dot(const Vector& v) const
	{
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::RSub(T v) const
	{
		return Vector(v - x, v - y, v - z, v - w);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::RSub(const Vector& v) const
	{
		return Vector(v.x - x, v.y - y, v.z - z, v.w - w);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::RDiv(T v) const
	{
		return Vector(v / x, v / y, v / z, v / w);
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::RDiv(const Vector& v) const
	{
		return Vector(v.x / x, v.y / y, v.z / z, v.w / w);
	}

	template <typename T>
	void Vector<T, 4>::IAdd(T v)
	{
		x += v;
		y += v;
		z += v;
		w += v;
	}

	template <typename T>
	void Vector<T, 4>::IAdd(const Vector& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	template <typename T>
	void Vector<T, 4>::ISub(T v)
	{
		x -= v;
		y -= v;
		z -= v;
		w -= v;
	}

	template <typename T>
	void Vector<T, 4>::ISub(const Vector& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
	}

	template <typename T>
	void Vector<T, 4>::IMul(T v)
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
	}

	template <typename T>
	void Vector<T, 4>::IMul(const Vector& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
	}

	template <typename T>
	void Vector<T, 4>::IDiv(T v)
	{
		x /= v;
		y /= v;
		z /= v;
		w /= v;
	}

	template <typename T>
	void Vector<T, 4>::IDiv(const Vector& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
	}

	template <typename T>
	const T& Vector<T, 4>::At(size_t i) const
	{
		assert(i < 4);
		return (&x)[i];
	}

	template <typename T>
	T& Vector<T, 4>::At(size_t i)
	{
		assert(i < 4);
		return (&x)[i];
	}

	template <typename T>
	T Vector<T, 4>::Sum() const
	{
		return x + y + z +w;
	}

	template <typename T>
	T Vector<T, 4>::Avg() const
	{
		return (x + y + z + w) / 4;
	}

	template <typename T>
	T Vector<T, 4>::Min() const
	{
		return std::min(x, y, z, w);
	}

	template <typename T>
	T Vector<T, 4>::Max() const
	{
		return std::max(x, y, z, w);
	}

	template <typename T>
	T Vector<T, 4>::AbsMin() const
	{
		return CubbyFlow::AbsMin(x, y, z, w);
	}

	template <typename T>
	T Vector<T, 4>::AbsMax() const
	{
		return CubbyFlow::AbsMax(x, y, z, w);
	}

	template <typename T>
	size_t Vector<T, 4>::DominantAxis() const
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (AbsMax() == &x[i])
				return i;
		}
	}

	template <typename T>
	size_t Vector<T, 4>::SubdominantAxis() const
	{
		T arr[4] = { x,y,z,w };
		std::sort(arr, arr + 4);

		for (size_t i = 0; i < 4; i++)
		{
			if (&x[i] == arr[1])
				return i;
		}
	}

	template <typename T>
	Vector<T, 4> Vector<T, 4>::Normalized() const
	{
		return Vector(x / Length(), y / Length(), z / Length(), w / Length());
	}

	template <typename T>
	T Vector<T, 4>::Length() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	template <typename T>
	T Vector<T, 4>::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template <typename T>
	T Vector<T, 4>::DistanceTo(const Vector<T, 4>& other) const
	{
		return Sub(other).Length();
	}

	template <typename T>
	T Vector<T, 4>::DistanceSquaredTo(const Vector<T, 4>& other) const
	{
		return Sub(other).LengthSquared();
	}

	template <typename T>
	template <typename U>
	Vector<U, 4> Vector<T, 4>::CastTo() const
	{
		return Vector<U, 4>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(w));
	}

	template <typename T>
	bool Vector<T, 4>::IsEqual(const Vector& other) const
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}

	template <typename T>
	bool Vector<T, 4>::IsSimilar(const Vector& other, T epsilon) const
	{
		return (std::fabs(x - other.x) < epsilon) && (std::fabs(y - other.y) < epsilon && std::fabs(z - other.z) < epsilon) && (std::fabs(w - other.w) < epsilon);
	}

	template <typename T>
	T& Vector<T, 4>::operator[](size_t i)
	{
		assert(i < 4);
		return (&x)[i];
	}

	template <typename T>
	const T& Vector<T, 4>::operator[](size_t i) const
	{
		return At(i);
	}

	template <typename T>
	template <typename U>
	Vector<T, 4>& Vector<T, 4>::operator=(const std::initializer_list<U>& list)
	{
		Set(list);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator=(const Vector& v)
	{
		Set(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator+=(T v)
	{
		IAdd(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator+=(const Vector& v)
	{
		IAdd(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator-=(T v)
	{
		ISub(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator-=(const Vector& v)
	{
		ISub(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator*=(T v)
	{
		IMul(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator*=(const Vector& v)
	{
		IMul(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator/=(T v)
	{
		IDiv(v);
		return (*this);
	}

	template <typename T>
	Vector<T, 4>& Vector<T, 4>::operator/=(const Vector& v)
	{
		IDiv(v);
		return (*this);
	}

	template <typename T>
	bool Vector<T, 4>::operator==(const Vector& v) const
	{
		return IsEqual(v);
	}

	template <typename T>
	bool Vector<T, 4>::operator!=(const Vector& v) const
	{
		return !IsEqual(v);
	}

	template <typename T>
	Vector<T, 4> operator+(const Vector<T, 4>& a)
	{
		return a;
	}

	template <typename T>
	Vector<T, 4> operator-(const Vector<T, 4>& a)
	{
		return Vector<T, 4>(-a.x, -a.y, -a.z, -a.w);
	}

	template <typename T>
	Vector<T, 4> operator+(const Vector<T, 4>& a, T b)
	{
		return a.Add(b);
	}

	template <typename T>
	Vector<T, 4> operator+(T a, const Vector<T, 4>& b)
	{
		return b.Add(a);
	}

	template <typename T>
	Vector<T, 4> operator+(const Vector<T, 4>& a, const Vector<T, 4>& b)
	{
		return a.Add(b);
	}

	template <typename T>
	Vector<T, 4> operator-(const Vector<T, 4>& a, T b)
	{
		return a.Sub(b);
	}


	template <typename T>
	Vector<T, 4> operator-(T a, const Vector<T, 4>& b)
	{
		return b.RSub(a);
	}

	template <typename T>
	Vector<T, 4> operator-(const Vector<T, 4>& a, const Vector<T, 4>& b)
	{
		return a.Sub(b);
	}

	template <typename T>
	Vector<T, 4> operator*(const Vector<T, 4>& a, T b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Vector<T, 4> operator*(T a, const Vector<T, 4>& b)
	{
		return b.Mul(a);
	}

	template <typename T>
	Vector<T, 4> operator*(const Vector<T, 4>& a, const Vector<T, 4>& b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Vector<T, 4> operator/(const Vector<T, 4>& a, T b)
	{
		return a.Div(b);
	}

	template <typename T>
	Vector<T, 4> operator/(T a, const Vector<T, 4>& b)
	{
		return b.RDiv(a);
	}

	template <typename T>
	Vector<T, 4> operator/(const Vector<T, 4>& a, const Vector<T, 4>& b)
	{
		return a.Div(b);
	}

	template <typename T>
	Vector<T, 4> Min(const Vector<T, 4>& a, const Vector<T, 4>& b)
	{
		return Vector<T, 4>(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
	}

	template <typename T>
	Vector<T, 4> Max(const Vector<T, 4>& a, const Vector<T, 4>& b)
	{
		return Vector<T, 4>(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
	}

	template <typename T>
	Vector<T, 4> Clamp(const Vector<T, 4>& v, const Vector<T, 4>& low, const Vector<T, 4>& high)
	{
		return Vector<T, 4>(std::clamp(v.x, low.x, high.x), std::clamp(v.y, low.y, high.y), std::clamp(v.z, low.z, high.z), std::clamp(v.w, low.w, high.w));
	}

	template <typename T>
	Vector<T, 4> Ceil(const Vector<T, 4>& a)
	{
		return Vector<T, 4>(std::ceil(a.x), std::ceil(a.y), std::ceil(a.z), std::ceil(a.w));
	}

	template <typename T>
	Vector<T, 4> Floor(const Vector<T, 4>& a)
	{
		return Vector<T, 4>(std::floor(a.x), std::floor(a.y), std::floor(a.z), std::floor(a.w));
	}

	template <typename T>
	Vector<T, 4> MonotonicCatmullRom(
		const Vector<T, 4>& v0,
		const Vector<T, 4>& v1,
		const Vector<T, 4>& v2,
		const Vector<T, 4>& v3,
		T f)
	{

	}
}