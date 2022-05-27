#pragma once

#include <istream>

namespace Crossant::Graphics::Graphics3D {
	struct Shader {
		unsigned id = 0;

		~Shader();

		Shader *FromStream(std::istream vertexStream, std::istream fragmentStream);
		
		void Use() const;
	};
}