/*************************************************************************
> File Name: FdmBlas.cpp
> Project Name: CubbyFlow
> Author: Dongmin Kim
> Purpose: Implements finite difference method Basic Linear Algebra Subprograms.
> Created Time: 2017/06/19
> Copyright (c) 2017, Dongmin Kim
*************************************************************************/
#include"FdmBlas3.h"

namespace CubbyFlow
{
	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::set(double s, FdmVector3* result)
	{
		result->set(s);
	}

	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::set(const FdmVector3& v, FdmVector3* result)
	{
		result->set(v);
	}

	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::set(const double s, FdmMatrix3* result)
	{
		result->set(s);
	}

	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::set(const FdmMatrix3& m, FdmMatrix3* result)
	{
		result->set(m);
	}

	template <typename T, typename FdmMatrixRow3>
	double FdmBlas3<T, FdmMatrixRow3>::dot(const FdmVector3& a, FdmVector3& b)
	{
		return a.dot(b);
	}

	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::axpy(
		double a,
		const FdmVector3& x,
		const FdmVector3& y,
		FdmVector3* result)
	{
		*result = a * x + y;
	}

	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::mvm(
		const FdmMatrix3& m, 
		const FdmVector3& v, 
		FdmVector3* result)
	{
		Size3 size = m.size();
		m.parallelForEachIndex([&](size_t i, size_t j, size_t k) {
			(*result)(i, j, k)
				= m(i, j, k).center * v(i, j, k)
				+ ((i > 0) ? m(i - 1, j, k).right * v(i - 1, j, k) : 0.0)
				+ ((i + 1 < size.x) ? m(i, j, k).right * v(i + 1, j, k) : 0.0)
				+ ((j > 0) ? m(i, j - 1, k).up * v(i, j - 1, k) : 0.0)
				+ ((j + 1 < size.y) ? m(i, j, k).up * v(i, j + 1, k) : 0.0)
				+ ((k > 0) ? m(i, j, k - 1).front * v(i, j, k - 1) : 0.0)
				+ ((k + 1 < size.z) ? m(i, j, k).front * v(i, j, k + 1) : 0.0);
		})
	}

	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::residual(
		const FdmMatrix3& a,
		const FdmVector3& x,
		const FdmVector3& b,
		FdmVector3* result)
	{
		*result = b - a * x;
	}

	template <typename T, typename FdmMatrixRow3>
	double FdmBlas3<T, FdmMatrixRow3>::l2Norm(const FdmVector3& v)
	{
		return std::sqrt(v.dot(v));
	}

	template <typename T, typename FdmMatrixRow3>
	void FdmBlas3<T, FdmMatrixRow3>::lInfNorm(const FdmVector3& v)
	{
		return std::fabs(v.absmax());
	}
}