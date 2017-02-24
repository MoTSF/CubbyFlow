/*************************************************************************
> File Name: Vector4.h
> Project Name: CubbyFlow
> Author: Chan-Ho Chris Ohk
> Purpose: 4-D vector class.
> Created Time: 2017/02/24
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef CUBBYFLOW_VECTOR4_H
#define CUBBYFLOW_VECTOR4_H

#include <Vector/Vector3.h>

#include <limits>

namespace CubbyFlow
{
	//!
	//! \brief 4-D vector class.
	//!
	//! This class defines simple 4-D vector data.
	//!
	//! \tparam T - Type of the element
	//!
	template <typename T>
	class Vector<T, 4> final
	{
	public:
		static_assert(std::is_floating_point<T>::value, "Vector only can be instantiated with floating point types");

		//! X (or the first) component of the vector.
		T x;

		//! Y (or the second) component of the vector.
		T y;

		//! Z (or the third) component of the vector.
		T z;

		//! W (or the fourth) component of the vector.
		T w;

		// MARK: Constructors
		//! Constructs default vector (0, 0, 0, 0).
		Vector();

		//! Constructs vector with given parameters \p x, \p y, \p z, and \p w.
		Vector(T x, T y, T z, T w);

		//! Constructs vector with a 3-D vector (x, y, and z) and a scalar (w).
		Vector(const Vector3<T>& pt, T w);

		//! Constructs vector with initializer list.
		template <typename U>
		Vector(const std::initializer_list<U>& list);

		//! Copy constructor.
		Vector(const Vector& v);

		// MARK: Basic setters
		//! Set both x, y, z, and w components to \p s.
		void Set(T s);

		//! Set x, y, z, and w components with given parameters.
		void Set(T x, T y, T z, T w);

		//! Set x, y, z, and w components with \p pt.x, \p pt.y, \p z, and \p w.
		void Set(const Vector<T, 3>& pt, T z);

		//! Set x, y, z, and w components with given initializer list.
		template <typename U>
		void Set(const std::initializer_list<U>& list);

		//! Set x, y, z, and w with other vector \p v.
		void Set(const Vector& v);

		//! Set all x, y, z, and w to zero.
		void SetZero();

		//! Normalizes this vector.
		void Normalize();

		// MARK: Binary operations: new instance = this (+) v
		//! Computes this + (v, v, v).
		Vector Add(T v) const;

		//! Computes this + (v.x, v.y, v.z).
		Vector Add(const Vector& v) const;

		//! Computes this - (v, v, v).
		Vector Sub(T v) const;

		//! Computes this - (v.x, v.y, v.z).
		Vector Sub(const Vector& v) const;

		//! Computes this * (v, v, v).
		Vector Mul(T v) const;

		//! Computes this * (v.x, v.y, v.z).
		Vector Mul(const Vector& v) const;
		
		//! Computes this / (v, v, v).
		Vector Div(T v) const;

		//! Computes this / (v.x, v.y, v.z).
		Vector Div(const Vector& v) const;

		//! Computes dot product.
		T Dot(const Vector& v) const;

		// MARK: Binary operations: new instance = v (+) this
		//! Computes (v, v, v) - this.
		Vector RSub(T v) const;

		//! Computes (v.x, v.y, v.z) - this.
		Vector RSub(const Vector& v) const;

		//! Computes (v, v, v) / this.
		Vector RDiv(T v) const;

		//! Computes (v.x, v.y, v.z) / this.
		Vector RDiv(const Vector& v) const;

		// MARK: Augmented operations: this (+)= v
		//! Computes this += (v, v, v).
		void IAdd(T v);

		//! Computes this += (v.x, v.y, v.z).
		void IAdd(const Vector& v);

		//! Computes this -= (v, v, v).
		void ISub(T v);

		//! Computes this -= (v.x, v.y, v.z).
		void ISub(const Vector& v);

		//! Computes this *= (v, v, v).
		void IMul(T v);

		//! Computes this *= (v.x, v.y, v.z).
		void IMul(const Vector& v);

		//! Computes this /= (v, v, v).
		void IDiv(T v);

		//! Computes this /= (v.x, v.y, v.z).
		void IDiv(const Vector& v);

		// MARK: Basic getters
		//! Returns const reference to the \p i -th element of the vector.
		const T& At(size_t i) const;

		//! Returns reference to the \p i -th element of the vector.
		T& At(size_t i);

		//! Returns the sum of all the components (i.e. x + y + z + w).
		T Sum() const;

		//! Returns the average of all the components.
		T Avg() const;

		//! Returns the minimum value among x, y, and z.
		T Min() const;

		//! Returns the maximum value among x, y, and z.
		T Max() const;

		//! Returns the absolute minimum value among x, y, and z.
		T AbsMin() const;

		//! Returns the absolute maximum value among x, y, and z.
		T AbsMax() const;

		//! Returns the index of the dominant axis.
		size_t DominantAxis() const;

		//! Returns the index of the sub-dominant axis.
		size_t SubdominantAxis() const;

		//! Returns normalized vector.
		Vector Normalized() const;

		//! Returns the length of the vector.
		T Length() const;

		//! Returns the squared length of the vector.
		T LengthSquared() const;

		//! Returns the distance to the other vector.
		T DistanceTo(const Vector& other) const;

		//! Returns the squared distance to the other vector.
		T DistanceSquaredTo(const Vector& other) const;

		//! Returns a vector with different value type.
		template <typename U>
		Vector<U, 4> CastTo() const;

		//! Returns true if \p other is the same as this vector.
		bool IsEqual(const Vector& other) const;

		//! Returns true if \p other is similar to this vector.
		bool IsSimilar(const Vector& other, T epsilon = std::numeric_limits<T>::epsilon()) const;

		// MARK: Operators
		//! Returns reference to the \p i -th element of the vector.
		T& operator[](size_t i);

		//! Returns const reference to the \p i -th element of the vector.
		const T& operator[](size_t i) const;

		//! Set x and y components with given initializer list.
		template <typename U>
		Vector& operator=(const std::initializer_list<U>& list);

		//! Set x and y with other vector \p pt.
		Vector& operator=(const Vector& v);

		//! Computes this += (v, v)
		Vector& operator+=(T v);

		//! Computes this += (v.x, v.y)
		Vector& operator+=(const Vector& v);

		//! Computes this -= (v, v)
		Vector& operator-=(T v);

		//! Computes this -= (v.x, v.y)
		Vector& operator-=(const Vector& v);

		//! Computes this *= (v, v)
		Vector& operator*=(T v);

		//! Computes this *= (v.x, v.y)
		Vector& operator*=(const Vector& v);

		//! Computes this /= (v, v)
		Vector& operator/=(T v);

		//! Computes this /= (v.x, v.y)
		Vector& operator/=(const Vector& v);

		//! Returns true if \p other is the same as this vector.
		bool operator==(const Vector& v) const;

		//! Returns true if \p other is the not same as this vector.
		bool operator!=(const Vector& v) const;
	};

	//! Type alias for four dimensional vector.
	template <typename T> using Vector4 = Vector<T, 4>;

	//! Positive sign operator.
	template <typename T>
	Vector4<T> operator+(const Vector4<T>& a);

	//! Negative sign operator.
	template <typename T>
	Vector4<T> operator-(const Vector4<T>& a);

	//! Computes (a, a, a, a) + (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator+(T a, const Vector4<T>& b);

	//! Computes (a.x, a.y, a.z, a.w) + (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b);

	//! Computes (a.x, a.y, a.z, a.w) - (b, b, b, b).
	template <typename T>
	Vector4<T> operator-(const Vector4<T>& a, T b);

	//! Computes (a, a, a, a) - (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator-(T a, const Vector4<T>& b);

	//! Computes (a.x, a.y, a.z, a.w) - (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b);

	//! Computes (a.x, a.y, a.z, a.w) * (b, b, b, b).
	template <typename T>
	Vector4<T> operator*(const Vector4<T>& a, T b);

	//! Computes (a, a, a, a) * (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator*(T a, const Vector4<T>& b);

	//! Computes (a.x, a.y, a.z, a.w) * (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator*(const Vector4<T>& a, const Vector4<T>& b);

	//! Computes (a.x, a.y, a.z, a.w) / (b, b, b, b).
	template <typename T>
	Vector4<T> operator/(const Vector4<T>& a, T b);

	//! Computes (a, a, a, a) / (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator/(T a, const Vector4<T>& b);

	//! Computes (a.x, a.y, a.z, a.w) / (b.x, b.y, b.z, b.w).
	template <typename T>
	Vector4<T> operator/(const Vector4<T>& a, const Vector4<T>& b);

	//! Returns element-wise min vector.
	template <typename T>
	Vector4<T> Min(const Vector4<T>& a, const Vector4<T>& b);

	//! Returns element-wise max vector.
	template <typename T>
	Vector4<T> Max(const Vector4<T>& a, const Vector4<T>& b);

	//! Returns element-wise clamped vector.
	template <typename T>
	Vector4<T> Clamp(const Vector4<T>& v, const Vector4<T>& low, const Vector4<T>& high);

	//! Returns element-wise ceiled vector.
	template <typename T>
	Vector4<T> Ceil(const Vector4<T>& a);

	//! Returns element-wise floored vector.
	template <typename T>
	Vector4<T> Floor(const Vector4<T>& a);

	//! Float-type 4D vector.
	using Vector4F = Vector4<float>;

	//! Double-type 4D vector.
	using Vector4D = Vector4<double>;

	// MARK: Extensions
	//! Returns float-type zero vector.
	template <>
	inline Vector4F Zero<Vector4F>()
	{
		return Vector4F(0.f, 0.f, 0.f, 0.f);
	}

	//! Returns double-type zero vector.
	template <>
	inline Vector4D Zero<Vector4D>()
	{
		return Vector4D(0.0, 0.0, 0.0, 0.0);
	}

	//! Returns the type of the value itself.
	template <typename T>
	struct ScalarType<Vector4<T>>
	{
		typedef T value;
	};

	//! Computes monotonic Catmull-Rom interpolation.
	template <typename T>
	Vector4<T> MonotonicCatmullRom(
		const Vector4<T>& v0,
		const Vector4<T>& v1,
		const Vector4<T>& v2,
		const Vector4<T>& v3,
		T f);
}

#endif