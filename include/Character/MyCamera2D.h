#pragma once
#include <raylib.h>
#include "Character.h"

class MyCamera2D {
private:
	Camera2D camera = { 0 }; 
	float zoomLevel = 1; 
public:
	MyCamera2D(float baseWidth_, float baseHeight_);

	Camera2D getCamera() {return camera;}
	void update(Vector2 playerPos); 
	void setTarget(Vector2 newTarget);
	void setTarget(float x, float y);
	void setZoom(float zoomLevel_); 
}; 

