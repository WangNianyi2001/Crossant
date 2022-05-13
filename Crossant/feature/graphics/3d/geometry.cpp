#include "geometry.hpp"

using namespace Crossant::Graphics::Graphics3D;

#define o(a, b) (unsigned)offsetof(a, b)
std::map<Vertex::Attribute, unsigned> Vertex::offsetMap{
	{ Attribute::Vertex, o(Vertex, vertex) },
	{ Attribute::Color, o(Vertex, color) },
	{ Attribute::TexCoord, o(Vertex, texCoord) },
	{ Attribute::Normal, o(Vertex, normal) },
	{ Attribute::EdgeFlag, o(Vertex, edgeFlag) },
};
#undef o

using DUT = Vertex::DatumType;

std::map<Vertex::Attribute, DUT> Vertex::typeMap{
	{ Attribute::Vertex, DUT::Float },
	{ Attribute::Color, DUT::Float },
	{ Attribute::TexCoord, DUT::Float },
	{ Attribute::Normal, DUT::Float },
	{ Attribute::EdgeFlag, DUT::Byte },
};

std::map<Vertex::Attribute, unsigned> Vertex::dimensionMap{
	{ Attribute::Vertex, 3 },
	{ Attribute::Color, 3 },
	{ Attribute::TexCoord, 2 },
	{ Attribute::Normal, 3 },
	{ Attribute::EdgeFlag, 1 },
};

Mesh Mesh::cube{
	{
		{ { 0, 0, 0 }, { 0, 0, 0 } },
		{ { 1, 0, 0 }, { 1, 0, 0 } },
		{ { 0, 1, 0 }, { 0, 1, 0 } },
		{ { 1, 1, 0 }, { 1, 1, 0 } },
		{ { 0, 0, 1 }, { 0, 0, 1 } },
		{ { 1, 0, 1 }, { 1, 0, 1 } },
		{ { 0, 1, 1 }, { 0, 1, 1 } },
		{ { 1, 1, 1 }, { 1, 1, 1 } },
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