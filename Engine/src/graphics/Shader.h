#include <GL/glew.h>
#include <iostream>

namespace engine { namespace graphics {

	class Shader {

		GLuint programID, vertexShaderID, fragmentShaderID;

		GLuint compileShader(char* source, GLenum type);
		
	public:
		Shader(char* vertexShader, char* fragmentShader);

		~Shader();

		void enable();

		void disable();
	};

}}