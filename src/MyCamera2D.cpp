#include "MyCamera2D.h"
#include <algorithm>
#include <cmath> 
#include <iostream>
#include "raymath.h"
#include "Exceptions.h"

MyCamera2D::MyCamera2D(float width, float height){
	camera.target = { 0, 0 };
	camera.offset = { width / 2.0f, height / 2.0f};
	camera.rotation = 0.0f; 
	camera.zoom = zoomLevel;
}

void MyCamera2D::save(std::ostream &os) {
    float halfW = GetScreenWidth() * 0.5f / camera.zoom;
    os << camera.target.x - halfW << " " << camera.target.y - mapSize.y / 2 << "\n";
}

void MyCamera2D::setTarget(Vector2 newTarget) {
    float halfW = GetScreenWidth() * 0.5f / camera.zoom;
	camera.target = {newTarget.x + halfW, newTarget.y + mapSize.y / 2};
}

void MyCamera2D::setTarget(float x, float y) {
    float halfW = GetScreenWidth() * 0.5f / camera.zoom;
	camera.target = Vector2{ x + halfW, y + mapSize.y / 2};
}

void MyCamera2D::setZoom(float zoomLevel_) {
  	camera.zoom = zoomLevel_;
	zoomLevel = zoomLevel_;
}

void MyCamera2D::setMapSize(Vector2 mapSize) { 
    this->mapSize = mapSize; 
    float screenW = (float)GetScreenWidth();
    float screenH = (float)GetScreenHeight();
	
    // --- Zoom so whole map fits (optional) ---
    float scaleX = screenW / mapSize.x;
    float scaleY = screenH / mapSize.y;
    setZoom(std::max(scaleX, scaleY));
    setTarget(0.0f, 0.0f);
}

void MyCamera2D::update(Player* player){
    float screenW = (float)GetScreenWidth();
    float screenH = (float)GetScreenHeight();
	
    // --- Zoom so whole map fits (optional) ---
    float scaleX = screenW / mapSize.x;
    float scaleY = screenH / mapSize.y;
    setZoom(std::max(scaleX, scaleY));

    float halfW = screenW * 0.5f / camera.zoom;
    float halfH = screenH * 0.5f / camera.zoom;

    Rectangle playerHitBox = player->getHitbox();

    // --- Clamp Mario inside map ---
    if (playerHitBox.x < camera.target.x - halfW) 
		player->setPosition({camera.target.x - halfW, playerHitBox.y});
    if (playerHitBox.x > mapSize.x - playerHitBox.width)
        player->setPosition({mapSize.x - playerHitBox.width, playerHitBox.y});

    // --- Camera follows Mario ---
	if (playerHitBox.x > camera.target.x)
    	camera.target.x = playerHitBox.x;

    // --- Clamp camera inside map ---
    camera.target.x = Clamp(camera.target.x, halfW, mapSize.x - halfW);
    // camera.target.y = Clamp(camera.target.y, halfH, mapSize.y - halfH);
}
