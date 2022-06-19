
#include "Shaders.h"
#include <stdexcept>
#include "Debugf.h"

bool Shaders::compileShaders() {
	try {
		debugf("Compiling shaders...\n");
//		glEnableClientState(GL_VERTEX_ARRAY);
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		static bool glewInitialized = false;
		if(!glewInitialized) {
			GLenum err = glewInit();
			if (GLEW_OK != err) {
				throw std::runtime_error("glewInit failed: " + std::string((const char*)glewGetErrorString(err)));
			}
			glewInitialized = true;
		}

		vertex = glCreateShader(GL_VERTEX_SHADER);
		const char *vs_c_str = vertexShaderSource.c_str();
		glShaderSource(vertex, 1, (const GLchar *const *) &vs_c_str, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to compile vertex shader, reason:\n" + std::string(infoLog));
		};
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		const char *fs_c_str = indexedFragmentShaderSource.c_str();
		glShaderSource(fragment, 1, (const GLchar *const *) &fs_c_str, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to compile fragment shader (indexed), reason:\n" + std::string(infoLog));
		};

		GLint ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to link shader program, reason:\n" + std::string(infoLog));
		}

		glDeleteShader(fragment);
		indexedShaderProgram = ID;
		indexed_TextureSamplerLocation = glGetUniformLocation(indexedShaderProgram, "indexed_text");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		fs_c_str = paletteFragmentShaderSource.c_str();
		glShaderSource(fragment, 1, (const GLchar *const *) &fs_c_str, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to compile fragment shader (palette), reason:\n" + std::string(infoLog));
		};

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to link shader program (palette), reason:\n" + std::string(infoLog));
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		paletteShaderProgram = ID;
		palette_IndexedTextureSamplerLocation = glGetUniformLocation(paletteShaderProgram, "indexed_text");
		palette_PaletteTextureSamplerLocation = glGetUniformLocation(paletteShaderProgram, "palette_text");
		palette_TransparentFlagLocation = glGetUniformLocation(paletteShaderProgram, "transparent_flag");

		debugf("Finished\n");
	}
	catch(std::exception & e) {
		debugf("Failed to compile shaders: %s\n", e.what());
		return false;
	}
	return true;
}

void Shaders::install() {

}

