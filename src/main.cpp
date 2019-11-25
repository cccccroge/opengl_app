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

#include <iostream>

ShaderProgram* global::program;
ShaderProgram* global::program_flat;
ShaderProgram* global::program_normal_as_color;
Renderer* global::renderer;
Model* global::Palace;


void setupRendering()
{
	// setup shader program
	Shader vertexShader = Shader(GL_VERTEX_SHADER, "assets/vertex.vs.glsl");

	Shader fragmentShader_flat = Shader(GL_FRAGMENT_SHADER, "assets/fragment_flat.fs.glsl");
	global::program_flat = new ShaderProgram();
	global::program_flat->addShader(vertexShader);
	global::program_flat->addShader(fragmentShader_flat);
	global::program_flat->compile();

	Shader fragmentShader_normal_as_color = Shader(GL_FRAGMENT_SHADER, "assets/fragment_normal_as_color.fs.glsl");
	global::program_normal_as_color = new ShaderProgram();
	global::program_normal_as_color->addShader(vertexShader);
	global::program_normal_as_color->addShader(fragmentShader_normal_as_color);
	global::program_normal_as_color->compile();

	global::program = global::program_flat;
   
	// setup modeles
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
	delete global::program_flat;
	delete global::program_normal_as_color;
	delete global::Palace;
	delete global::renderer;

	return 0;
}