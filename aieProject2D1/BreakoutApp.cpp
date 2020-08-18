#include "BreakoutApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm\ext.hpp>
#include <Gizmos.h>

aieProject2D1App::aieProject2D1App() {

}

aieProject2D1App::~aieProject2D1App() {

}

bool aieProject2D1App::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U); 
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void aieProject2D1App::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void aieProject2D1App::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	//aie::Gizmos::add2DCircle(glm::vec2(0, 0), 4, 12, glm::vec4(9, 50, 90, 5));
	//aie::Gizmos::add2DTri(glm::vec2(0, 4), glm::vec2(4, 4), glm::vec2(69, 9), glm::vec4(0, 1, 0, 1));
	//static const glm::vec4 colours[] = {
	//	glm::vec4(1,0,0,1), glm::vec4(0,1,0,1),
	//	glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0.5f,1),
	//	glm::vec4(0,1,1,1)
	//};

	//static const int rows = 5;
	//static const int columns = 10;
	//static const int hSpace = 1;
	//static const int vSpace = 1;

	//static const glm::vec2 scrExtents(100, 50);
	//static const glm::vec2 boxExtents(7, 3);
	//static const glm::vec2 startPos(
	//	-(columns >> 1)*((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace / 2.0f),
	//	scrExtents.y - ((boxExtents.y * 2) + hSpace));
	////draw the grid of blocks
	//glm::vec2 pos;
	//for (int y = 0; y < rows; y++) {
	//	pos = glm::vec2(startPos.x, startPos.y - (y* ((boxExtents.y * 2) + hSpace)));
	//	for (int x = 0; x < columns; x++) {
	//		aie::Gizmos::add2DAABBFilled(pos, boxExtents, colours[y]);
	//		pos.x += (boxExtents.x * 2) + vSpace;
	//	}
	//}

	//// draw the ball
	//aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));
	//// draw the player's paddle
	//aie::Gizmos::add2DAABBFilled(glm::vec2(0, -40), glm::vec2(12, 2),
	//	glm::vec4(1, 0, 1, 1));
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void aieProject2D1App::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100 , -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}