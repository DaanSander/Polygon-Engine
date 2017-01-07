#include <unordered_map>
#include <iostream>
#include <GL/glew.h>

#include "..\math\Math.h"

namespace engine { namespace graphics {

	class Shader {

		GLuint programID, vertexShaderID, fragmentShaderID;

		GLuint compileShader(char* source, GLenum type);
		
		std::unordered_map<char*, GLuint> uniforms;

	public:
		Shader(char* vertexShader, char* fragmentShader);

		~Shader();

		void enable();

		void disable();

		GLuint getUniformLocation(char* name);

		void recompileShader(char* vertexShader, char* fragmentShader);

		void loadUniformMat4f(GLuint location, math::Matrix4f matrix);

		inline GLuint getProgramID() { return programID; }
	};

}}