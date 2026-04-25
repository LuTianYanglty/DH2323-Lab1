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
#include <cstdlib>
#include <cmath>
#include "SDL2Auxiliary.h"

using namespace std;
using glm::vec3;

// ---------------------------------------------------------
// GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL2Aux *sdlAux;
vector<vec3> stars(1000);
int t;

// ---------------------------------------------------------
// FUNCTION DECLARATIONS
void Interpolate(float a, float b, vector<float>& result);
void Interpolate(vec3 a, vec3 b, vector<vec3>& result);

void Draw(vector<vec3>& stars);
void Update(vector<vec3>& stars);
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

	for (int s = 0; s < (int)stars.size(); ++s) {
		stars[s].x = 2.0f * float(rand()) / float(RAND_MAX) - 1.0f;
		stars[s].y = 2.0f * float(rand()) / float(RAND_MAX) - 1.0f;
		stars[s].z = float(rand()) / float(RAND_MAX);
	}

	t = SDL_GetTicks();
	while (!sdlAux->quitEvent()) {
		Update(stars);
		Draw(stars);
	}
	sdlAux->saveBMP("screenshot.bmp");
	return 0;
}

void Draw(vector<vec3>& stars)
{
	sdlAux->clearPixels();

	float f = SCREEN_HEIGHT / 2.0f;
	float cx = SCREEN_WIDTH / 2.0f;
	float cy = SCREEN_HEIGHT / 2.0f;

	for (size_t i = 0; i < stars.size(); ++i) {
		int u = int(f * stars[i].x / stars[i].z + cx);
		int v = int(f * stars[i].y / stars[i].z + cy);

		if (u >= 0 && u < SCREEN_WIDTH && v >= 0 && v < SCREEN_HEIGHT) {
			vec3 color = 0.2f * vec3(1, 1, 1) / (stars[i].z * stars[i].z);
			sdlAux->putPixel(u, v, color);
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

void Update(vector<vec3>& stars)
{
	int t2 = SDL_GetTicks();
	float dt = float(t2 - t);
	t = t2;

	float v = 0.0005f;

	for (int s = 0; s < (int)stars.size(); ++s) {
		stars[s].z -= v * dt;
		if (stars[s].z <= 0)
			stars[s].z += 1;
		if (stars[s].z > 1)
			stars[s].z -= 1;
	}
}