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
#include "render/PostEffectBuffer.h"

#include <iostream>

ShaderProgram* global::program_first;
ShaderProgram* global::program_second;
ShaderProgram* global::program_skybox;
PostEffectBuffer* global::postEffectBuffer;
Renderer* global::renderer;
Model* global::Palace;
Skybox* global::skybox;


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

	Shader vertexShader_skybox = Shader(GL_VERTEX_SHADER, "assets/skybox.vs.glsl");
	Shader fragmentShader_skybox = Shader(GL_FRAGMENT_SHADER, "assets/skybox.fs.glsl");
	global::program_skybox = new ShaderProgram();
	global::program_skybox->addShader(vertexShader_skybox);
	global::program_skybox->addShader(fragmentShader_skybox);
	global::program_skybox->compile();
	
	// setup shader variables
	global::comp_bar_xCoord = 0.5;
	global::program_first->bind();
	global::program_first->setUniform1f("uf_comp_bar_xCoord", 
		global::comp_bar_xCoord);
	global::program_second->bind();
	global::program_second->setUniform1f("uf_comp_bar_xCoord", 
		global::comp_bar_xCoord);
   
	// setup models
	//global::Palace = new Model("assets/myman/myMan.obj");
	global::Palace = new Model("assets/lost_empire/lost_empire.obj");

	// setup skybox
	global::skybox = new Skybox({
		"assets/cubemaps/face-r.png",
		"assets/cubemaps/face-l.png",
		"assets/cubemaps/face-t.png",
		"assets/cubemaps/face-d.png",
		"assets/cubemaps/face-f.png",
		"assets/cubemaps/face-b.png",
	});
	global::skybox->scale(1.0f, 1.0f, -1.0f);

	// setup camera
	global::camViewport = Camera(PROJECTION_TYPE::PERSPECTIVE, 
		std::vector<float>({ 0.1f, 1000.0f }), glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(-1.0f, -1.0f, 0.0f), 80.0f);

	// send to renderer
	global::renderer = new Renderer();
	global::renderer->addModel(*global::Palace);
	global::renderer->addSkybox(*global::skybox);
	global::renderer->setCamera(global::camViewport);

	// set up post effect buffer
	global::postEffectBuffer = new PostEffectBuffer(MAINWINDOW_WIDTH,
		MAINWINDOW_HEIGHT);
	
	global::program_second->bind();
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
	
	delete global::postEffectBuffer;
	delete global::renderer;
	delete global::Palace;
	delete global::program_second;
	delete global::program_first;
	
	return 0;
}