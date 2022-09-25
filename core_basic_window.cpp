/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define EPSILON 1.e-6f

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

struct Polar {
	float rho;
	float theta;
};

struct Cylindrical {
	float rho; 
	float theta;
	float y;
};

struct Spherical {
	float rho;
	float theta;
	float phi;
};

Cylindrical CartesianToCylindrical(Vector3 cart)
{
	Vector2 xy = Vector2 {
		cart.x,
		cart.y
	};
	Cylindrical cyl = {
		cyl.y = cart.y,
		cyl.rho = Vector2Length(xy),
		cyl.theta = atan2f(cart.x, cart.z),
	};
	return cyl;
}

Vector3 CylindricalToCartesian(Cylindrical cyl)
{
	Vector3 cart = {
		cart.x = cyl.rho * cosf(cyl.theta),
		cart.y = cyl.rho * sinf(cyl.theta),
		cart.z = cyl.y,
	};
	return cart;
}

Spherical CartesianToSpherical(Vector3 cart)
{
	Spherical sph = Spherical {
		sph.rho = Vector3Length(cart),
		sph.theta = atan2f(cart.x, cart.z),
		sph.phi = acosf(cart.y / Vector3Length(cart)),
	};
	return sph;
}

Vector3 SphericalToCartesian(Spherical sph)
{
	Vector3 cart = {
		cart.x = sph.rho * cosf(sph.theta) * sinf(sph.phi),
		cart.y = sph.rho * sinf(sph.theta) * sinf(sph.phi),
		cart.z = sph.rho * cosf(sph.phi),
	};
	return cart;
}

Polar CartesianToPolar(Vector2 cart, bool keepThetaPositive = true)
{
	Polar polar = {
		Vector2Length(cart),
		atan2f(cart.y,cart.x),
	};
	if (keepThetaPositive && polar.theta < 0)
	{
		polar.theta += 2 * PI;
	}
	return polar;
}

Vector2 PolarToCartesian(Polar polar)
{
	return Vector2Scale({ cosf(polar.theta),sinf(polar.theta) }, polar.rho);
}


void MyUpdateOrbitalCamera(Camera* camera, float deltaTime)
{
	static Spherical sphPos = { 10,PI / 4.f,PI / 4.f };
	static Vector2 prevMousePos = { 0,0 };
	Vector2 mousePos = GetMousePosition();
	Vector2 mouseVect = Vector2Subtract(mousePos, prevMousePos);
	prevMousePos = mousePos;
	float rhoMin = 4;
	float rhoMax = 40;
	Spherical sphDelta = {

	};
	Spherical sphSpeed = {
		2.0f,
		0.04f,
		0.04f 
	};
}

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	float screenSizeCoef = .9f;
	const int screenWidth = 1920 * screenSizeCoef;
	const int screenHeight = 1080 * screenSizeCoef;

	InitWindow(screenWidth, screenHeight, "ESIEE - E3FI - 2022 - 2023 -Maths 3D");

	SetTargetFPS(60);

	//CAMERA
	Vector3 cameraPos = { 8.0f, 15.0f, 14.0f };
	Camera camera = { 0 };
	camera.position = cameraPos;
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.type = CAMERA_PERSPECTIVE;
	SetCameraMode(camera, CAMERA_CUSTOM);  // Set an orbital camera mode


	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		float deltaTime = GetFrameTime();
		float time = (float)GetTime();

		MyUpdateOrbitalCamera(&camera, deltaTime);

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
		{
			//
				
			//3D REFERENTIAL
			DrawGrid(20, 1.0f);        // Draw a grid
			DrawLine3D({ 0 }, { 0,10,0 }, DARKGRAY);
			DrawSphere({ 10,0,0 }, .2f, RED);
			DrawSphere({ 0,10,0 }, .2f, GREEN);
			DrawSphere({ 0,0,10 }, .2f, BLUE);
		}
		EndMode3D();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
