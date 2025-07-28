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

void MyCamera2D::update(Player* player){
	float screenW = (float)GetScreenWidth();
	float screenH = (float)GetScreenHeight();

	Rectangle playerHitBox = player->getHitbox();

	if (playerHitBox.x < 0.0f)                     
		playerHitBox.x = 0.0f;

	if (playerHitBox.x > mapSize.x - playerHitBox.width)           
		playerHitBox.x = mapSize.x - playerHitBox.width;

	camera.target = { playerHitBox.x, playerHitBox.y - 100.0f };


	float scaleX = screenW / mapSize.x;
	float scaleY = screenH / mapSize.y;
	camera.zoom = std::max(scaleX, scaleY);

	float halfW = screenW * 0.5f / camera.zoom;
	float halfH = screenH * 0.5f / camera.zoom;

	if (mapSize.x > 2 * halfW) {
		if (camera.target.x < halfW)        camera.target.x = halfW;
		if (camera.target.x > mapSize.x - halfW) camera.target.x = mapSize.x - halfW;
	}
	else 
		camera.target.x = mapSize.x / 2;  

	if (mapSize.y > 2 * halfH) {
		if (camera.target.y < halfH)        camera.target.y = halfH;
		if (camera.target.y > mapSize.y - halfH) camera.target.y = mapSize.y - halfH;
	}
	else {
		camera.target.y = mapSize.y / 2;
	}
}
