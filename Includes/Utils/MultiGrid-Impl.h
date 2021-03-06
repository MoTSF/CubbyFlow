/*************************************************************************
> File Name: MultiGrid-Impl.h
> Project Name: CubbyFlow
> Author: Chan-Ho Chris Ohk
> Purpose: Multi-grid wrapper functions for CubbyFlow.
> Created Time: 2017/09/26
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef CUBBYFLOW_MULTI_GRID_IMPL_H
#define CUBBYFLOW_MULTI_GRID_IMPL_H

namespace CubbyFlow
{
	namespace Internal
	{
		template <typename BlasType>
		MultiGridResult MultiGridVCycle(
			const MultiGridMatrix<BlasType>& A, MultiGridParameters<BlasType> params,
			unsigned int currentLevel, MultiGridVector<BlasType>* x,
			MultiGridVector<BlasType>* b, MultiGridVector<BlasType>* buffer)
		{
			// 1) Relax a few times on Ax = b, with arbitrary x
			params.relaxFunc(A[currentLevel], (*b)[currentLevel],
				params.numberOfRestrictionIter, params.maxTolerance,
				&((*x)[currentLevel]), &((*buffer)[currentLevel]));

			// 2) if currentLevel is the coarsest grid, goto 5)
			if (currentLevel < A.levels.size() - 1)
			{
				auto r = buffer;
				BlasType::Residual(A[currentLevel], (*x)[currentLevel], (*b)[currentLevel], &(*r)[currentLevel]);
				params.restrictFunc((*r)[currentLevel], &(*b)[currentLevel + 1]);

				BlasType::Set(0.0, &(*x)[currentLevel + 1]);

				params.maxTolerance *= 0.5;
				// Solve Ae = r
				MultiGridVCycle(A, params, currentLevel + 1, x, b, buffer);
				params.maxTolerance *= 2.0;

				// 3) correct
				params.correctFunc((*x)[currentLevel + 1], &(*x)[currentLevel]);

				// 4) relax nIter times on Ax = b, with initial guess x
				if (currentLevel > 0)
				{
					params.relaxFunc(A[currentLevel], (*b)[currentLevel],
						params.numberOfCorrectionIter, params.maxTolerance,
						&((*x)[currentLevel]), &((*buffer)[currentLevel]));
				}
				else
				{
					params.relaxFunc(A[currentLevel], (*b)[currentLevel],
						params.numberOfFinalIter, params.maxTolerance,
						&((*x)[currentLevel]), &((*buffer)[currentLevel]));
				}
			}
			else
			{
				// 5) solve directly with initial guess x
				params.relaxFunc(A[currentLevel], (*b)[currentLevel],
					params.numberOfCoarsestIter, params.maxTolerance,
					&((*x)[currentLevel]), &((*buffer)[currentLevel]));

				BlasType::Residual(A[currentLevel], (*x)[currentLevel], (*b)[currentLevel], &(*buffer)[currentLevel]);
			}

			BlasType::Residual(A[currentLevel], (*x)[currentLevel], (*b)[currentLevel], &(*buffer)[currentLevel]);

			MultiGridResult result;
			result.lastResidualNorm = BlasType::L2Norm((*buffer)[currentLevel]);
			return result;
		}
	}

	template <typename BlasType>
	const typename BlasType::MatrixType& MultiGridMatrix<BlasType>::operator[](size_t i) const
	{
		return levels[i];
	}

	template <typename BlasType>
	typename BlasType::MatrixType& MultiGridMatrix<BlasType>::operator[](size_t i)
	{
		return levels[i];
	}

	template <typename BlasType>
	const typename BlasType::MatrixType& MultiGridMatrix<BlasType>::Finest() const
	{
		return levels.Front();
	}

	template <typename BlasType>
	typename BlasType::MatrixType& MultiGridMatrix<BlasType>::Finest()
	{
		return levels.Front();
	}

	template <typename BlasType>
	const typename BlasType::VectorType& MultiGridVector<BlasType>::operator[](size_t i) const
	{
		return levels[i];
	}

	template <typename BlasType>
	typename BlasType::VectorType& MultiGridVector<BlasType>::operator[](size_t i)
	{
		return levels[i];
	}

	template <typename BlasType>
	const typename BlasType::VectorType& MultiGridVector<BlasType>::Finest() const
	{
		return levels.Front();
	}

	template <typename BlasType>
	typename BlasType::VectorType& MultiGridVector<BlasType>::Finest()
	{
		return levels.Front();
	}

	template <typename BlasType>
	MultiGridResult MultiGridVCycle(
		const MultiGridMatrix<BlasType>& A, MultiGridParameters<BlasType> params,
		MultiGridVector<BlasType>* x, MultiGridVector<BlasType>* b,
		MultiGridVector<BlasType>* buffer)
	{
		return Internal::MultiGridVCycle<BlasType>(A, params, 0u, x, b, buffer);
	}
}

#endif