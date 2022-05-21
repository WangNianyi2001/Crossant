#include "meshrenderer.hpp"

using namespace Crossant::Graphics::Graphics3D;

using VA = Vertex::Attribute;
using DUT = Vertex::DatumType;

std::map<Vertex::Attribute, MeshRenderer::AttributeUsage> useTemplate{
	{ VA::Position, { DUT::Float, true } },
	{ VA::Color, { DUT::Float } },
	{ VA::TexCoord, { DUT::Float } },
	{ VA::Normal, { DUT::Float } },
	{ VA::EdgeFlag, { DUT::Byte } },
};

MeshRenderer::MeshRenderer(Object &object) :
	Renderer(object), attributeUsage(useTemplate) {}

void MeshRenderer::Render() {
	Space &space = object.space;
	space.SetMatrixMode(Space::MatrixMode::Space);
	space.PushMatrix();
	object.transform.Apply();
	for(MeshFilter *filter : object.ComponentsOf<MeshFilter>()) {
		if(filter->mesh == nullptr)
			continue;
		Mesh const *const mesh = filter->mesh;
		for(auto pair : attributeUsage) {
			space.SetAttributeArray(
				pair.first,
				pair.second.datumType,
				pair.second.used,
				&mesh->vertices[0]
			);
		}
		space.DrawElements(Context::GeometryType::Triangles, (std::vector<unsigned> &)mesh->indices);
	}
	space.PopMatrix();
}