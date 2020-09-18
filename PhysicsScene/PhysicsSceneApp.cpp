#include "PhysicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include"PhysicsScene.h"
#include<Gizmos.h>
#include "Sphere.h"
#include "Plane.h"


PhysicsSceneApp::PhysicsSceneApp() {

}

PhysicsSceneApp::~PhysicsSceneApp() {

}

bool PhysicsSceneApp::startup() {
	// increase the 2D line cound to maximize the number of objects
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	glm::vec2  gravity = glm::vec2(0.0f, 0.0f);

	glm::vec2 initialPosition = glm::vec2(0.0f, 0.0f);
	glm::vec2 finalPosition = glm::vec2(60.0f, 0.0f);
	glm::vec2 initialvelocity = calculateVelocity(initialPosition, finalPosition, gravity.y, 5.0f);


	Plane* plane = new Plane(glm::vec2(0.0f, 1.0f), 0.0f);
	Sphere* seean = new Sphere(glm::vec2(0.0f,20.0f), glm::vec2(0.0f,000.0f), 1.0f, 5.0f, glm::vec4(3, 1, 0, 1));
	Sphere* seean1 = new Sphere(glm::vec2(0.0f,40.0f), glm::vec2(0.0f,-80.0f), 1.0f, 5.0f, glm::vec4(3, 1, 0, 1));

	/*Sphere* ball = new Sphere(initialPosition, initialvelocity, 1.0f, 4.0f, glm::vec4(1, 0.0f, 0.0f, 1.0f));*/

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(gravity);
	m_physicsScene->setTimeStep(0.01f);


	m_physicsScene->addActor(seean);
	m_physicsScene->addActor(seean1);
	m_physicsScene->addActor(plane);

	return true;
}

void PhysicsSceneApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsSceneApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();


	

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(
		-100.0f, 100.0f,
		-100.0f / aspectRatio, 100.0f / aspectRatio
		));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsSceneApp::setupContinuousDemo(glm::vec2 initialPosition, glm::vec2 initialVelocity, float gravity)
{
	float time = 0.0f;
	float timeStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(3, 1, 0, 1);

	while (time <= 5)
	{
		float x = initialPosition.x + initialVelocity.x*time;
		float y = initialPosition.y + initialVelocity.y*time+ .5 * -gravity * (time * time);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		time += timeStep;
	}
}

glm::vec2 PhysicsSceneApp::calculateVelocity(glm::vec2 initialPosition, glm::vec2 finalPosition, float gravity, float time)
{
	glm::vec2 initialVelocity = glm::vec2(0, 0);

	initialVelocity.x = (finalPosition.x - initialPosition.x) / time;
	initialVelocity.y = (finalPosition.y - initialPosition.y - (0.5f * gravity * (time * time)) / time);

	return initialVelocity;
}
