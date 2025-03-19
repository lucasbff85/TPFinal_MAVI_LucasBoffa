#pragma once
#include "stdafx.h"
#include "Player.h"

using namespace sf;

Player::Player(RenderWindow* wnd) {
    h_move = 0;
    v_move = 0;

    tex_nave.loadFromFile("../Assets/player.png");
    sprite_nave.setTexture(tex_nave);
	Iniciar(wnd);
	
   _soundbuffer.loadFromFile("../Sounds/thrust.wav");
   _sound.setBuffer(_soundbuffer);
}

Player::~Player(){

}

void Player::Iniciar(RenderWindow* wnd) {
	esta_vivo = true;
	sprite_nave.setOrigin(sprite_nave.getLocalBounds().width / 2, sprite_nave.getLocalBounds().height / 2);
	Posicionar(Vector2u(wnd->getSize().x / 2, wnd->getSize().y / 2));
}

bool Player::EstaVivo() {
    return esta_vivo;
}

void Player::Morir() {
    esta_vivo = false;
}


void Player::Dibujar(RenderWindow* wnd) {
    wnd->draw(sprite_nave);
}

void Player::ProcesarEventos()
{

	{
		h_move = 0;  //horizontal move
		v_move = 0;   //vertical move
		
		if (Keyboard::isKeyPressed(Keyboard::W)) v_move = 1;
		if (Keyboard::isKeyPressed(Keyboard::S)) v_move = -1;
		if (Keyboard::isKeyPressed(Keyboard::D)) h_move = 1;
		if (Keyboard::isKeyPressed(Keyboard::A)) h_move = -1;
	}


}

void Player::Actualizar(Vector2u size, float deltaTime) {

	//rotacion
	if (h_move != 0)
	{
		sprite_nave.rotate(h_move * rotateSpeed * deltaTime);
	}

	//aceleracion y movimiento
	if (v_move != 0)
	{
		if (play_thrust == false)
		{
			play_thrust = true;
			MovePlay();
		}

		x_dir = -cos(sprite_nave.getRotation() * 3.14159f / 180.0f);
		y_dir = -sin(sprite_nave.getRotation() * 3.14159f / 180.0f);

		velocity.x += v_move * acceleration * deltaTime * x_dir / 1000;
		velocity.y += v_move * acceleration * deltaTime * y_dir / 1000;


	
		//limite de velocidad
		if ((velocity.x * velocity.x) > (max_velocity.x * max_velocity.x))
			velocity.x = velocity.x > 0 ? max_velocity.x : -max_velocity.x;

		if ((velocity.y * velocity.y) > (max_velocity.y * max_velocity.y))
			velocity.y = velocity.y > 0 ? max_velocity.y : -max_velocity.y;
	}
	else
	{
		velocity.x *= 0.99f;  // Reduce la velocidad en cada frame
		velocity.y *= 0.99f;
		//si deja de acelerar, detiene el sonido de empuje
		play_thrust = false;
		MoveStop();
	}

	ManejarBordes(size);

	sprite_nave.move(velocity);

}


void Player::ManejarBordes(Vector2u size) {
	if (sprite_nave.getPosition().x < 0) sprite_nave.setPosition(size.x, sprite_nave.getPosition().y);
	if (sprite_nave.getPosition().x > size.x) sprite_nave.setPosition(0, sprite_nave.getPosition().y);
	if (sprite_nave.getPosition().y < 0) sprite_nave.setPosition(sprite_nave.getPosition().x, size.y);
	if (sprite_nave.getPosition().y > size.y) sprite_nave.setPosition(sprite_nave.getPosition().x, 0);
}

void Player::MovePlay()
{
	_sound.setVolume(60);
	_sound.setLoop(true);
	_sound.play();
}

void Player::MoveStop()
{
	_sound.setVolume(0);
	_sound.stop();
}

void Player::Posicionar(Vector2u posicion) {
	sprite_nave.setPosition(posicion.x, posicion.y);
}
    
Sprite& Player::GetSprite() {
	return sprite_nave;
}