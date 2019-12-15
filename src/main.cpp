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

ShaderProgram* global::program_model;
ShaderProgram* global::program_posteffect;
ShaderProgram* global::program_skybox;
PostEffectBuffer* global::postEffectBuffer;
Renderer* global::renderer;
Model* global::Man;
Skybox* global::skybox;


void setupRendering()
{
	// setup shader program
	Shader vertexShader_first = Shader(GL_VERTEX_SHADER, "assets/model.vs.glsl");
	Shader fragmentShader_first = Shader(GL_FRAGMENT_SHADER, "assets/model.fs.glsl");
	global::program_model = new ShaderProgram();
	global::program_model->addShader(vertexShader_first);
	global::program_model->addShader(fragmentShader_first);
	global::program_model->compile();

	Shader vertexShader_second = Shader(GL_VERTEX_SHADER, "assets/posteffect.vs.glsl");
	Shader fragmentShader_second = Shader(GL_FRAGMENT_SHADER, "assets/posteffect.fs.glsl");
	global::program_posteffect = new ShaderProgram();
	global::program_posteffect->addShader(vertexShader_second);
	global::program_posteffect->addShader(fragmentShader_second);
	global::program_posteffect->compile();

	Shader vertexShader_skybox = Shader(GL_VERTEX_SHADER, "assets/skybox.vs.glsl");
	Shader fragmentShader_skybox = Shader(GL_FRAGMENT_SHADER, "assets/skybox.fs.glsl");
	global::program_skybox = new ShaderProgram();
	global::program_skybox->addShader(vertexShader_skybox);
	global::program_skybox->addShader(fragmentShader_skybox);
	global::program_skybox->compile();
   
	// setup models
	//global::Palace = new Model("assets/myman/myMan.obj");
	//global::Palace = new Model("assets/lost_empire/lost_empire.obj");
	global::Man = new Model("assets/hisman/ball.obj");
	global::Man->translate(-10.0f, -13.0f, -8.0f);
	//global::Man->scale(0.5f, 0.35f, 0.5f);

	// setup skybox
	global::skybox = new Skybox({
		"assets/cubemaps/face-r.png",
		"assets/cubemaps/face-l.png",
		"assets/cubemaps/face-t.png",
		"assets/cubemaps/face-d.png",
		"assets/cubemaps/face-f.png",
		"assets/cubemaps/face-b.png",
	});
	global::skybox->scale(1.0f, 1.0f, -1.0f);	// flip it for godsake!

	// setup camera
	global::camViewport = Camera(PROJECTION_TYPE::PERSPECTIVE, 
		std::vector<float>({ 0.1f, 1000.0f }), glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(-1.0f, -1.0f, 0.0f), 80.0f);

	// send to renderer
	global::renderer = new Renderer();
	global::renderer->addModel(*global::Man);
	global::renderer->addSkybox(*global::skybox);
	global::renderer->setCamera(global::camViewport);

	// set up post effect buffer
	global::postEffectBuffer = new PostEffectBuffer(MAINWINDOW_WIDTH,
		MAINWINDOW_HEIGHT);
	
	global::program_posteffect->bind();
	global::program_posteffect->setUniform1i("screenTex", 0);

	// set up uniforms in first program
	global::program_model->bind();
	global::program_model->setUniformVec3("lightPos", 
		glm::vec3(-31.75f, 26.05f, -97.72f));
	global::program_model->setUniform1f("ambientStrength", 0.0f);
	global::program_model->setUniformVec3("ambientAlbedo",
		glm::vec3(1.0f, 1.0f, 1.0f));
	global::program_model->setUniformVec3("diffuseAlbedo",
		glm::vec3(0.35f, 0.35f, 0.35f));
	global::program_model->setUniformVec3("specularAlbedo",
		glm::vec3(0.7f, 0.7f, 0.7f));
	global::program_model->setUniform1i("specularPower", 200);
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
	delete global::Man;
	delete global::program_posteffect;
	delete global::program_model;
	
	return 0;
}