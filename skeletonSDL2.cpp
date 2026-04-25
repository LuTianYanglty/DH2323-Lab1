// DH2323 Lab 1
// Introduction lab that covers:
// * SDL2 (https://www.libsdl.org/)
// * C++, std::vector and glm::vec3 (https://glm.g-truc.net)
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDL2Auxiliary.h"

using namespace std;
using glm::vec3;

// ---------------------------------------------------------
// GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL2Aux *sdlAux;

// ---------------------------------------------------------
// FUNCTION DECLARATIONS
void Interpolate(float a, float b, vector<float>& result);
void Interpolate(vec3 a, vec3 b, vector<vec3>& result);

void Draw();
// ---------------------------------------------------------

// FUNCTION DEFINITIONS
int main(int argc, char* argv[])
{
	vector<float> result(10);
	Interpolate(5, 14, result);
	for (int i = 0; i < (int)result.size(); ++i)
		cout << result[i] << " ";
	cout << endl;

	vector<vec3> result2(4);
	vec3 a(1, 4, 9.2f);
	vec3 b(4, 1, 9.8f);
	Interpolate(a, b, result2);
	for (int i = 0; i < (int)result2.size(); ++i) {
		cout << "( " << result2[i].x << ", "
				 << result2[i].y << ", "
				 << result2[i].z << " ) ";
	}
	cout << endl;

	sdlAux = new SDL2Aux(SCREEN_WIDTH, SCREEN_HEIGHT);
	while (!sdlAux->quitEvent()) {
		Draw();
	}
	sdlAux->saveBMP("screenshot.bmp");
	return 0;
}

void Draw()
{
	sdlAux->clearPixels();

	vec3 topLeft(1, 0, 0);
	vec3 topRight(0, 0, 1);
	vec3 bottomLeft(0, 1, 0);
	vec3 bottomRight(1, 1, 0);

	vector<vec3> leftSide(SCREEN_HEIGHT);
	vector<vec3> rightSide(SCREEN_HEIGHT);
	Interpolate(topLeft, bottomLeft, leftSide);
	Interpolate(topRight, bottomRight, rightSide);

	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		vector<vec3> row(SCREEN_WIDTH);
		Interpolate(leftSide[y], rightSide[y], row);
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			sdlAux->putPixel(x, y, row[x]);
		}
	}

	sdlAux->render();
}

void Interpolate(float a, float b, vector<float>& result)
{
	int N = (int)result.size();
	if (N == 1) {
		result[0] = (a + b) / 2.0f;
		return;
	}
	float step = (b - a) / float(N - 1);
	for (int i = 0; i < N; ++i) {
		result[i] = a + step * i;
	}
}

void Interpolate(vec3 a, vec3 b, vector<vec3>& result)
{
	int N = (int)result.size();
	if (N == 1) {
		result[0] = (a + b) * 0.5f;
		return;
	}
	vec3 step = (b - a) / float(N - 1);
	for (int i = 0; i < N; ++i) {
		result[i] = a + step * float(i);
	}
}