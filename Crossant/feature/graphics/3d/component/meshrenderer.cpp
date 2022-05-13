#include "meshrenderer.hpp"

using namespace Crossant::Graphics::Graphics3D;

using VA = Vertex::Attribute;

std::map<VA, bool> useTemplate{
	{ VA::Vertex, true },
	{ VA::Color, false },
	{ VA::TexCoord, false },
	{ VA::Normal, false },
	{ VA::EdgeFlag, false },
};

MeshRenderer::MeshRenderer(Object &object) :
	Component(object), use(useTemplate) {}

void MeshRenderer::Render() {
	MeshFilter *const filter = object.GetComponentOfType<MeshFilter>();
	if(filter == nullptr || filter->mesh == nullptr)
		return;
	Mesh const *const mesh = filter->mesh;
	Space &space = object.space;
	space.SetMatrixMode(Space::MatrixMode::Space);
	space.PushMatrix();
	space.LoadIdentity();
	object.transform.Apply();
	for(auto pair : use)
		space.SetAttributeArray(pair.first, pair.second, &mesh->vertices[0]);
	space.DrawElements(Context::GeometryType::Triangles, (std::vector<unsigned> &)mesh->indices);
	space.PopMatrix();
}