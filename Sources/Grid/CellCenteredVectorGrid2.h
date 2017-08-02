/*************************************************************************
> File Name: CellCenteredVectorGrid2.h
> Project Name: CubbyFlow
> Author: Dongmin Kim
> Purpose: 2-D Cell-centered vector grid structure.
> Created Time: 2017/08/02
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef CUBBYFLOW_CELL_CENTERED_VECTOR_GRID2_H
#define CUBBYFLOW_CELL_CNETERED_VECTOR_GRID2_H

#include <Grid/Grid2.h>
#include <Grid/VectorGrid2.h>

namespace CubbyFlow
{
	//!
	//! \brief 2-D Cell-centered vector grid structure.
	//!
	//! This class represents 2-D cell-centered vector grid which extends
	//! VectorGrid2. As its name suggests, the class defines the data point at the
	//! center of a grid cell. Thus, the dimension of data points are equal to the
	//! dimension of the cells.
	//!
	class CellCenteredVectorGrid2 final : public VectorGrid2
	{
	public :
		CUBBYFLOW_GRID2_TYPE_NAME(CellCenteredVectorGrid2);

		class Builder;
		
		//! Constructs zero-sized grid.
		CellCenteredVectorGrid2();
		
		//! Constructs a grid with given resolution, grid spacing, origin
		//! and initial value.
		CellCenteredVectorGrid2(
			size_t resolutionX, size_t resolutionY,
			double gridSpacingX = 1.0, double gridSpacingY = 1.0,
			double originX = 0.0, double originY = 0.0,
			double initialValueU = 0.0, double initalValueV = 0.0);

		//! Constructs a grid with given resolution, grid spacing, origin
		//! and initial value.
		CellCenteredVectorGrid2(
			const Size2& resolution,
			const Vector2D& gridSpacing = Vector2D(1.0, 1.0),
			const Vector2D& origin = Vector2D(),
			const Vector2D& initalValue = Vector2D());
		
		//! Copy constructor.
		CellCenteredVectorGrid2(const CellCenteredVectorGrid2& other);

		//! Returns the actual data point size.
		Size2 GetDataSize() contt override;

		//! Returns data position for the grid point at (0, 0).
		//! Note that this is different from origin() since origin() returns
		//! the lower corner point of the bouding box.
		Vector2D GetDataOrigin() const override;

		//!
		//! \brief Swaps the contents with the given \p other grid.
		//!
		//! This function swaps the contents of the grid instance with the given
		//! grid object \p other only if \p other has the same type with this grid.\
		//! 
		void Swap(Grid2* other) override;

		//! Sets the contents with the given \p other grid.
		void Set(const CellCenteredVectorGrid2& other);
		
		//! Sets the contents with the given \p other gird.
		CellCenteredVectorGrid2& operator=(const CellCenteredVectorGrid2& other);
		
		//! Fills the grid with given value.
		void fill(const Vector2D& value, ExecutionPolicy policy = ExecutionPolicy::kParallel) override;

		//! Fills the grid with given function.
		void fill(const std::function < Vector2D(const Vector2D& > )& func,
			ExecutionPolicy policy = ExecutionPolicy::kParallel) override;
		//! Returns the copy of the grid instance.
		std::shared_ptr<VectorGrid2> Clone() const override;
		
		//! Returns the builder fox CellCenteredVectorGrid2.
		static Builder GetBuilder();
	};

	//! Shared pointer for the CellCenteredVectorGrid2 type.
	using CellCenteredVectorGrid2Ptr = std::shared_ptr<CellCenteredVectorGrid2>;

	//!
	//! \brief Front-end to create CellCenteredVectorGrid2 objects step by step.\
	//!
	class CellCenteredVectorGrid2::Builder final : public VectorGridBuilder2
	{
	public:
		//! Returns builder with resolution.
		Builder& WithResolution(const Size2& resolution);
		
		//! Returns builder with resolution.
		Builder& WithResolution(size_t resolutionX, size_t resolutionY);

		//! Returns builder with grid spacing.
		Builder& WithGridSpacing(const Vector2D& gridSpacing);

		//! Returns builder with grid spacing.
		Builder& WithGridSpacing(double gridSpacingX, double gridSpacingY);
		
		//! Returns builder with grid origin.
		Builder& WithOrigin(const Vector2D& gridOrigin);

		//! Returns builder with grid origin.
		Builder& WithOrigin(double gridOriginX, double gridOriginY);

		//! Returns bulider with inital value.
		Builder& WithInitialValue(const Vector2D& initalVal);

		//! Returns bulider with inital value.
		Builder& WithInitialValue(double initialValU, double initalValV);

		//! Builds CellCenteredVectorGrid2 instance.
		CellCenteredVectorGrid2 Build() const;

		//! Builds shared pointer of CellCenteredScalarGrid2 instance.
		CellCenteredVectorGrid2Ptr MakeShared() const;

		//! \brief Builds shared pointer of CellCenteredVectorGrid2 instance.
		//!
		//! This is an overriding function that implements VectorGridBuilder2.
		//!
		VectorGrid2Ptr Build(
			const Size2& resolution,
			const Vector2D& gridSpacing,
			const Vector2D& gridOrigin,
			const Vector2D& initalVal) const override;
		
	private:
		Size2 m_resolution{ 1, 1 };
		Vector2D m_gridSpacing{ 1, 1 };
		Vector2D m_gridOrigin{ 0, 0 };
		Vector2D m_initalVal{ 0, 0 };
	};
}

#endif