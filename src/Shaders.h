
#ifndef WKCUSTOMRENDERER_SHADERS_H
#define WKCUSTOMRENDERER_SHADERS_H

#include <GL/glew.h>
#include <string>

class Shaders {

	static inline const std::string indexedFragmentShaderSource =
#include "shaders/indexedFragmentShader.fs"
	;
	static inline const std::string vertexShaderSource =
#include "shaders/vertexShader.vs"
	;
	static inline const std::string paletteFragmentShaderSource =
#include "shaders/paletteFragmentShader.fs"
	;

	static inline GLint indexedShaderProgram, paletteShaderProgram;
	static inline GLint indexed_TextureSamplerLocation;
	static inline GLint palette_IndexedTextureSamplerLocation, palette_PaletteTextureSamplerLocation, palette_TransparentFlagLocation;
	static inline GLuint palette_texture = 0;
	static inline GLuint palette_PaletteTextureSampler = 0;

public:
	static bool compileShaders();
	static void install();
};


#endif //WKCUSTOMRENDERER_SHADERS_H
