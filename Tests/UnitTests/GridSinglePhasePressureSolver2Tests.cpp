#include "pch.h"

#include <Grid/CellCenteredScalarGrid2.h>
#include <Solver/Grid/GridSinglePhasePressureSolver2.h>

using namespace CubbyFlow;

TEST(GridSinglePhasePressureSolver2, SolveSinglePhase)
{
	FaceCenteredGrid2 vel(3, 3);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			vel.GetU(i, j) = 0.0;
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (j == 0 || j == 3)
			{
				vel.GetV(i, j) = 0.0;
			}
			else
			{
				vel.GetV(i, j) = 1.0;
			}
		}
	}

	GridSinglePhasePressureSolver2 solver;
	solver.Solve(vel, 1.0, &vel);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			EXPECT_NEAR(0.0, vel.GetU(i, j), 1e-6);
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			EXPECT_NEAR(0.0, vel.GetV(i, j), 1e-6);
		}
	}

	const auto& pressure = solver.GetPressure();
	for (size_t j = 0; j < 2; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			EXPECT_NEAR(pressure(i, j + 1) - pressure(i, j), -1.0, 1e-6);
		}
	}
}

TEST(GridSinglePhasePressureSolver2, SolveSinglePhaseWithBoundary)
{
	FaceCenteredGrid2 vel(3, 3);
	CellCenteredScalarGrid2 boundarySDF(3, 3);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			vel.GetU(i, j) = 0.0;
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (j == 0 || j == 3)
			{
				vel.GetV(i, j) = 0.0;
			}
			else
			{
				vel.GetV(i, j) = 1.0;
			}
		}
	}

	// Wall on the right-most column
	boundarySDF.Fill([&](const Vector2D& x)
	{
		return -x.x + 2.0;
	});

	GridSinglePhasePressureSolver2 solver;
	solver.Solve(vel, 1.0, &vel, boundarySDF);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			EXPECT_NEAR(0.0, vel.GetU(i, j), 1e-6);
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (i == 2 && (j == 1 || j == 2))
			{
				EXPECT_NEAR(1.0, vel.GetV(i, j), 1e-6);
			}
			else
			{
				EXPECT_NEAR(0.0, vel.GetV(i, j), 1e-6);
			}
		}
	}

	const auto& pressure = solver.GetPressure();
	for (size_t j = 0; j < 2; ++j)
	{
		for (size_t i = 0; i < 2; ++i)
		{
			EXPECT_NEAR(pressure(i, j + 1) - pressure(i, j), -1.0, 1e-6);
		}
	}
}

TEST(GridSinglePhasePressureSolver2, SolveFreeSurface)
{
	FaceCenteredGrid2 vel(3, 3);
	CellCenteredScalarGrid2 fluidSDF(3, 3);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			vel.GetU(i, j) = 0.0;
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (j == 0 || j == 3)
			{
				vel.GetV(i, j) = 0.0;
			}
			else
			{
				vel.GetV(i, j) = 1.0;
			}
		}
	}

	fluidSDF.Fill([&](const Vector2D& x)
	{
		return x.y - 2.0;
	});

	GridSinglePhasePressureSolver2 solver;
	solver.Solve(
		vel,
		1.0,
		&vel,
		ConstantScalarField2(std::numeric_limits<double>::max()),
		ConstantVectorField2({ 0, 0 }),
		fluidSDF);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			EXPECT_NEAR(0.0, vel.GetU(i, j), 1e-6);
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			EXPECT_NEAR(0.0, vel.GetV(i, j), 1e-6);
		}
	}

	const auto& pressure = solver.GetPressure();
	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			double p = static_cast<double>(2 - j);
			EXPECT_NEAR(p, pressure(i, j), 1e-6);
		}
	}
}

TEST(GridSinglePhasePressureSolver2, SolveFreeSurfaceWithBoundary)
{
	FaceCenteredGrid2 vel(3, 3);
	CellCenteredScalarGrid2 fluidSDF(3, 3);
	CellCenteredScalarGrid2 boundarySDF(3, 3);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			vel.GetU(i, j) = 0.0;
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (j == 0 || j == 3)
			{
				vel.GetV(i, j) = 0.0;
			}
			else
			{
				vel.GetV(i, j) = 1.0;
			}
		}
	}

	// Wall on the right-most column
	boundarySDF.Fill([&](const Vector2D& x)
	{
		return -x.x + 2.0;
	});
	fluidSDF.Fill([&](const Vector2D& x)
	{
		return x.y - 2.0;
	});

	GridSinglePhasePressureSolver2 solver;
	solver.Solve(
		vel,
		1.0,
		&vel,
		boundarySDF,
		ConstantVectorField2({ 0, 0 }),
		fluidSDF);

	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			EXPECT_NEAR(0.0, vel.GetU(i, j), 1e-6);
		}
	}

	for (size_t j = 0; j < 4; ++j)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (i == 2 && (j == 1 || j == 2))
			{
				EXPECT_NEAR(1.0, vel.GetV(i, j), 1e-6);
			}
			else
			{
				EXPECT_NEAR(0.0, vel.GetV(i, j), 1e-6);
			}
		}
	}

	const auto& pressure = solver.GetPressure();
	for (size_t j = 0; j < 3; ++j)
	{
		for (size_t i = 0; i < 2; ++i)
		{
			double p = static_cast<double>(2 - j);
			EXPECT_NEAR(p, pressure(i, j), 1e-6);
		}
	}
}