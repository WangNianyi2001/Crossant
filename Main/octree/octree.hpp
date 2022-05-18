#pragma once

#include "Crossant/common/basic.hpp"
#include "Space/space.hpp"
#include "Space/component/renderer.hpp"
#include <sstream>

namespace Octree {
	using namespace Crossant;
	using namespace Crossant::Graphics::Graphics3D;

	int Main();

	struct Octree {
		Coord3D offset;
		Coord3D position{};
		Byte branch;
		Octree *const parent;
		Octree *children[8];

		Octree(Octree *parent = nullptr) : parent(parent) {
			memset(children, 0, sizeof(Octree *) * 8);
		}

		~Octree() {
			for(int i = 0; i < 8; ++i)
				delete children[i];
		}

		void Update() {
			for(int i = 0; i < 8; ++i) {
				Octree *child = children[i];
				if(child == nullptr)
					continue;
				Coord3D flip;
				Byte branch = child->branch;
				for(int d = 0; d < 3; ++d) {
					flip[d] = (Float)((branch & 1) == 0 ? -1 : 1);
					branch >>= 1;
				}
				child->offset = child->offset.Operate<Float>([](Float x) { return x < 0 ? 0 : x; });
				child->position = position + child->offset * flip;
				child->Update();
			}
		}

		static void Serialize(std::ostream &ss, Octree const *node) {
			if(node == nullptr) {
				ss << '#';
				return;
			}
			Coord3D const &pos = node->offset;
			ss << '@' << pos[0] << ',' << pos[1] << ',' << pos[2] << ':';
			for(int i = 0; i < 8; ++i)
				Serialize(ss, node->children[i]);
		}

		static Octree *Deserialize(std::istream &ss, Octree *parent = nullptr) {
			if(ss.fail())
				return nullptr;
			char c;
			ss >> c;
			if(c == '#')
				return nullptr;
			if(c != '@')
				return nullptr;
			Float x, y, z;
			ss >> x >> c >> y >> c >> z >> c;
			if(ss.fail())
				return nullptr;
			Octree *node = new Octree(parent);
			node->offset = Coord3D{ x, y, z };
			for(int i = 0; i < 8; ++i) {
				if((char)ss.peek() == '.') {
					ss.get();
					break;
				}
				Octree *child = Deserialize(ss, node);
				if(child == nullptr)
					continue;
				child->branch = i;
				node->children[i] = child;
			}
			return node;
		}
	};

	struct OctreeRenderer : Renderer {
		std::vector<Vertex> vertices{};
		std::vector<unsigned> indices{};

		OctreeRenderer(Object &object) : Renderer(object) {}

		void Update(Octree *root, unsigned rootIndex) {
			if(root == nullptr)
				return;
			for(int i = 0; i < 8; ++i) {
				Octree *child = root->children[i];
				if(child == nullptr)
					continue;
				vertices.push_back({ child->position });
				unsigned childIndex = (unsigned)(vertices.size() - 1);
				indices.push_back(rootIndex);
				indices.push_back(childIndex);
				Update(child, childIndex);
			}
		}

		void Update(Octree *root) {
			vertices.clear();
			indices.clear();
			vertices.push_back({ root->offset });
			Update(root, 0);
		}

		virtual void Render() override {
			Space &space = parent.parent;
			space.SetMatrixMode(Space::MatrixMode::Space);
			space.PushMatrix();
			space.SetAttributeArray(Vertex::Attribute::Vertex, true, &vertices[0]);
			space.DrawElements(Context::GeometryType::Lines, indices);
			space.PopMatrix();
		}
	};
}