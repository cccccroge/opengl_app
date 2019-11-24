#include "GLEW/glew.h"
#include "freeGLUT/freeglut.h"

#include "GLM/glm_996/vec3.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "TinyOBJ/tiny_obj_loader.h"

#include "global.h"
#include "utils.h"
#include "init.h"
#include "scene/Model.h"
#include "render/Shader.h"
#include "render/ShaderProgram.h"
#include "scene/Camera.h"
#include "render/Renderer.h"

#include <iostream>

ShaderProgram* global::program;
Renderer* global::renderer;
Model* global::Palace;


void setupRendering()
{
	// setup shader program
	Shader vertexShader = Shader(GL_VERTEX_SHADER, "assets/vertex.vs.glsl");
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, "assets/fragment.fs.glsl");
	global::program = new ShaderProgram();
	global::program->addShader(vertexShader);
	global::program->addShader(fragmentShader);
	global::program->compile();
   
	// setup modeles
	global::Palace = new Model("assets/myman/myMan.obj");
	//global::Palace = new Model("assets/sibenik/sibenik.obj");

	// setup camera
	global::camViewport = Camera(PROJECTION_TYPE::PERSPECTIVE, 
		std::vector<float>({ 0.1f, 1000.0f }), glm::vec3(-5.0f, 10.0f, -10.0f), 
		glm::vec3(0.0f, 5.0f, 0.0f), 60.0f);

	// send to renderer
	global::renderer = new Renderer();
	global::renderer->addModel(*global::Palace);

	global::renderer->setCamera(global::camViewport);
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
	delete global::Palace;

	return 0;
}