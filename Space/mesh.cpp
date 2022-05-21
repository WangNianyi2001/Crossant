#include "mesh.hpp"

using namespace Crossant::Graphics::Graphics3D;

Mesh Mesh::cube{
	{
		{ { 0, 0, 0 } },
		{ { 1, 0, 0 } },
		{ { 0, 1, 0 } },
		{ { 1, 1, 0 } },
		{ { 0, 0, 1 } },
		{ { 1, 0, 1 } },
		{ { 0, 1, 1 } },
		{ { 1, 1, 1 } },
	},
	{
		{ 1, 0, 2 }, { 2, 3, 1 },
		{ 0, 4, 6 }, { 6, 2, 0 },
		{ 4, 5, 7 }, { 7, 6, 4 },
		{ 5, 1, 3 }, { 3, 7, 5 },
		{ 6, 7, 3 }, { 3, 2, 6 },
		{ 4, 5, 1 }, { 1, 0, 4 },
	}
};