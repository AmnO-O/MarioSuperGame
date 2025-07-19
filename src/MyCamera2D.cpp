#include "Character/MyCamera2D.h"
#include <algorithm>
#include <cmath> 
#include <iostream>
#include "Exceptions.h"

MyCamera2D::MyCamera2D(float width, float height){
	camera.target = { 0, 0 };
	camera.offset = { width / 2.0f, height / 2.0f};
	camera.rotation = 0.0f; 
	camera.zoom = zoomLevel;
}

void MyCamera2D::setTarget(Vector2 newTarget) {
	camera.target = newTarget;
}

void MyCamera2D::setTarget(float x, float y) {
	camera.target = Vector2{ x, y };
}

void MyCamera2D::setZoom(float zoomLevel_) {
  	camera.zoom = zoomLevel_;
	zoomLevel = zoomLevel_;
}

void MyCamera2D::update(Vector2 playerPos){
	float screenW = (float)GetScreenWidth();
	float screenH = (float)GetScreenHeight();

	float mapW = 3584.0f;
	float mapH = 240.0f;
	float playerW = 16.0f;

	if (playerPos.x < 0.0f)                     
		playerPos.x = 0.0f;

	if (playerPos.x > mapW - playerW)           
		playerPos.x = mapW - playerW;

	camera.target = { playerPos.x, playerPos.y - 100.0f };


	float scaleX = screenW / mapW;
	float scaleY = screenH / mapH;
	camera.zoom = std::max(scaleX, scaleY);

	float halfW = screenW * 0.5f / camera.zoom;
	float halfH = screenH * 0.5f / camera.zoom;

	if (mapW > 2 * halfW) {
		if (camera.target.x < halfW)        camera.target.x = halfW;
		if (camera.target.x > mapW - halfW) camera.target.x = mapW - halfW;
	}
	else 
		camera.target.x = mapW / 2;  

	if (mapH > 2 * halfH) {
		if (camera.target.y < halfH)        camera.target.y = halfH;
		if (camera.target.y > mapH - halfH) camera.target.y = mapH - halfH;
	}
	else {
		camera.target.y = mapH / 2;
	}
}
