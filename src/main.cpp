#include "GLEW/glew.h"
#include "freeGLUT/freeglut.h"

#include "GLM/glm_996/vec3.hpp"

#include "global.h"
#include "utils.h"
#include "init.h"
#include "scene/Model.h"
#include "render/Shader.h"
#include "render/ShaderProgram.h"
#include "scene/Camera.h"
#include "render/Renderer.h"
#include "render/FrameBuffer.h"

#include <iostream>

ShaderProgram* global::program;
ShaderProgram* global::program_first;
ShaderProgram* global::program_second;
FrameBuffer* global::postEffectBuffer;
Renderer* global::renderer;
Model* global::Palace;


void setupRendering()
{
	// setup shader program
	Shader vertexShader_first = Shader(GL_VERTEX_SHADER, "assets/vertex_first.vs.glsl");
	Shader fragmentShader_first = Shader(GL_FRAGMENT_SHADER, "assets/fragment_first.fs.glsl");
	global::program_first = new ShaderProgram();
	global::program_first->addShader(vertexShader_first);
	global::program_first->addShader(fragmentShader_first);
	global::program_first->compile();

	Shader vertexShader_second = Shader(GL_VERTEX_SHADER, "assets/vertex_second.vs.glsl");
	Shader fragmentShader_second = Shader(GL_FRAGMENT_SHADER, "assets/fragment_second.fs.glsl");
	global::program_second = new ShaderProgram();
	global::program_second->addShader(vertexShader_second);
	global::program_second->addShader(fragmentShader_second);
	global::program_second->compile();

	
	// setup shader variables
	float comp_bar_xCoord = 0.5;
	global::program = global::program_first;
	global::program->bind();
	global::program->setUniform1f("uf_comp_bar_xCoord", comp_bar_xCoord);
   
	// setup models
	//global::Palace = new Model("assets/myman/myMan.obj");
	global::Palace = new Model("assets/lost_empire/lost_empire.obj");

	// setup camera
	global::camViewport = Camera(PROJECTION_TYPE::PERSPECTIVE, 
		std::vector<float>({ 0.1f, 1000.0f }), glm::vec3(-5.0f, 10.0f, -10.0f), 
		glm::vec3(0.0f, 5.0f, 0.0f), 60.0f);

	// send to renderer
	global::renderer = new Renderer();
	global::renderer->addModel(*global::Palace);

	global::renderer->setCamera(global::camViewport);

	// set up post effect buffer
	global::postEffectBuffer = new FrameBuffer();
	global::program_second->setUniform1i("screenTex", 0);
}


int main(int argc, char *argv[])
{
	/* Glut initialization */
	initGlutContext(argc, argv);
	createMenu();
	registerCallbacks();
	global::timer.Start();
	
	/* GLEW initialization */
	initGlew();
	dumpInfo();

	/* Render initialization */
	setupRendering();

	/* Enter main event loop */
	glutMainLoop();	

	// MainLoop ends here, free mem.
	std::cout << "Return control from main loop." << std::endl;
	delete global::program_first;
	delete global::program_second;
	delete global::Palace;
	delete global::renderer;
	delete global::postEffectBuffer;

	return 0;
}