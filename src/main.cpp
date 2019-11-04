#include "GLEW/glew.h"
#include "freeGLUT/freeglut.h"

#include "GLM/glm_996/vec3.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "TinyOBJ/tiny_obj_loader.h"

#include "global.h"
#include "utils.h"
#include "init.h"
#include "scene/Mesh.h"
#include "render/Shader.h"
#include "render/ShaderProgram.h"
#include "scene/Camera.h"
#include "render/Renderer.h"

#include <iostream>

ShaderProgram* global::program;
Mesh* global::Torso;
Mesh* global::Head;
Mesh* global::Arm_R1;
Mesh* global::Arm_R2;
Mesh* global::Arm_L1;
Mesh* global::Arm_L2;
Mesh* global::Leg_R1;
Mesh* global::Leg_R2;
Mesh* global::Leg_L1;
Mesh* global::Leg_L2;

void setupRendering()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);	// TODO: temp add this, NEED to fix renderer constructor not called
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// setup shader program
	Shader vertexShader = Shader(GL_VERTEX_SHADER, "assets/vertex.vs.glsl");
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, "assets/fragment.fs.glsl");
	global::program = new ShaderProgram();
	global::program->addShader(vertexShader);
	global::program->addShader(fragmentShader);
	global::program->compile();
   
	// setup meshes
	global::Torso = new Mesh("assets/Torso.obj", 
		glm::vec3(0.0f, 2.7361f, 0.0f));	// global pos, copy from blender
	global::Torso->sendRendering();
	global::Torso->attachProgram(*global::program);

	global::Head = new Mesh("assets/Head.obj",
		glm::vec3(0.0f, 5.1385f, 0.0f));
	global::Head->sendRendering();
	global::Head->attachProgram(*global::program);

	global::Arm_R1 = new Mesh("assets/Arm_R1.obj", 
		glm::vec3(1.1264f, 4.6385f, 0.0f));
	global::Arm_R1->sendRendering();
	global::Arm_R1->attachProgram(*global::program);

	global::Arm_R2 = new Mesh("assets/Arm_R2.obj", 
		glm::vec3(1.56f, 4.1143f, 0.0f));
	global::Arm_R2->sendRendering();
	global::Arm_R2->attachProgram(*global::program);

	global::Arm_L1 = new Mesh("assets/Arm_L1.obj",
		glm::vec3(-1.1264f, 4.6385f, 0.0f));
	global::Arm_L1->sendRendering();
	global::Arm_L1->attachProgram(*global::program);

	global::Arm_L2 = new Mesh("assets/Arm_L2.obj",
		glm::vec3(-1.56f, 4.1143f, 0.0f));
	global::Arm_L2->sendRendering();
	global::Arm_L2->attachProgram(*global::program);

	global::Leg_R1 = new Mesh("assets/Leg_R1.obj",
		glm::vec3(0.56001f, 2.6803f, 0.0f));
	global::Leg_R1->sendRendering();
	global::Leg_R1->attachProgram(*global::program);

	global::Leg_R2 = new Mesh("assets/Leg_R2.obj",
		glm::vec3(0.56001f, 1.3538f, 0.0f));
	global::Leg_R2->sendRendering();
	global::Leg_R2->attachProgram(*global::program);

	global::Leg_L1 = new Mesh("assets/Leg_L1.obj",
		glm::vec3(-0.56001f, 2.6803f, 0.0f));
	global::Leg_L1->sendRendering();
	global::Leg_L1->attachProgram(*global::program);

	global::Leg_L2 = new Mesh("assets/Leg_L2.obj",
		glm::vec3(-0.56001f, 1.3538f, 0.0f));
	global::Leg_L2->sendRendering();
	global::Leg_L2->attachProgram(*global::program);

	// specify relationship
	global::Head->setParent(*global::Torso);
	global::Arm_R1->setParent(*global::Torso);
	global::Arm_L1->setParent(*global::Torso);
	global::Leg_R1->setParent(*global::Torso);
	global::Leg_L1->setParent(*global::Torso);

	global::Arm_R2->setParent(*global::Arm_R1);
	global::Arm_L2->setParent(*global::Arm_L1);
	global::Leg_R2->setParent(*global::Leg_R1);
	global::Leg_L2->setParent(*global::Leg_L1);

	// test if parent work
	global::Torso->rotate(15, std::vector<float>({ 1.0f, 0.0f, 0.0f }));
	global::Arm_R1->rotate(30, std::vector<float>({ 1.0f, 0.0f, 0.0f }));
	global::Arm_R2->rotate(45, std::vector<float>({ 1.0f, 0.0f, 0.0f }));


	// setup camera
	global::cameraPersp = Camera(PROJECTION_TYPE::PERSPECTIVE, 
		std::vector<float>({ 0.1f, 1000.0f }), glm::vec3(-5.0f, 10.0f, -10.0f), 
		glm::vec3(0.0f, 5.0f, 0.0f), 60.0f);

	// send to renderer
	global::renderer.addMesh(*global::Arm_R1);
	global::renderer.addMesh(*global::Arm_R2);
	global::renderer.addMesh(*global::Arm_L1);
	global::renderer.addMesh(*global::Arm_L2);
	global::renderer.addMesh(*global::Leg_R1);
	global::renderer.addMesh(*global::Leg_R2);
	global::renderer.addMesh(*global::Leg_L1);
	global::renderer.addMesh(*global::Leg_L2);
	global::renderer.addMesh(*global::Torso);
	global::renderer.addMesh(*global::Head);

	global::renderer.setCamera(global::cameraPersp);

	printGLError();
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
	delete global::Torso;
	delete global::Head;

	return 0;
}