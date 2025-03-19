#include "Asteroide.h"
#include "random"
#include "ctime"
#include "iostream"
#include "stdafx.h"

using namespace std;
using namespace sf;

// Definir el mapa de texturas estático
std::map<int, sf::Texture> Asteroide::texturas;


Asteroide::Asteroide() {
	int numero = rand() % 3 + 1;

	

	// Cargar la textura solo si no está en el mapa
	if (texturas.find(numero) == texturas.end()) {
		sf::Texture tex;
		if (!tex.loadFromFile("../Assets/Asteroid" + to_string(numero) + ".png")) {
			cout << "Error al cargar la textura: " << numero << endl;
		}
		texturas[numero] = tex; // Guardar la textura en el mapa
	}
	sprite_asteroide.setTexture(texturas[numero]); // Usar la textura del mapa

	//sprite_asteroide.setTexture(tex_asteroide);
	angulo = 0;
	nivel = 3;
	esta_vivo = true;
}
Asteroide::~Asteroide() {

}

void Asteroide::Iniciar(Vector2u size) {
	
	//posicion
	Vector2f posicion = Aparecer(size);
	sprite_asteroide.setPosition(posicion);

	//direccion
	angulo = rand() % 360;
	direccion.x = -cos(angulo * 3.14159f / 180.0f);
	direccion.y = sin(angulo * 3.14159f / 180.0f);
}


bool Asteroide::Esta_Vivo() const {
	return esta_vivo;
}

float Asteroide::Obtener_Angulo() const {
	return angulo;
}

void Asteroide::ManejarBordes(Vector2u size) {
	Vector2f positon;
	positon = sprite_asteroide.getPosition();

	if (positon.x < -160.f)
		positon.x = size.x + 100.f;
	else if (positon.x > size.x + 100.f)
		positon.x = -160.f;

	if (positon.y < -160.f)
		positon.y = size.y + 100.f;
	else if (positon.y > size.y + 100.f)
		positon.y = -160.f;

	sprite_asteroide.setPosition(positon);
}

Vector2f Asteroide::Aparecer(Vector2u size) {
	int max = 100;
	int min = 150;

	//casteo float porque me dice que hay perdida de datos
	Vector2f right;
	right.x = static_cast<float>(rand() % max + (size.x + 200));
	right.y = static_cast<float>(rand() % size.y);

	Vector2f left;
	left.x = static_cast<float>((rand() % max) - 250);
	left.y = static_cast<float>(rand() % size.y);

	Vector2f top;
	top.y = static_cast<float>((rand() % max) - 250);
	top.x = static_cast<float>(rand() % size.x);

	Vector2f bottom;
	bottom.y = static_cast<float>(rand() % max + (size.y + 200));
	bottom.x = static_cast<float>(rand() % size.x);

	

	int choice = rand() % 4 + 1;

	switch (choice)
	{
	case 1:
		return right;
		break;

	case 2:
		return left;
		break;

	case 3:
		return top;
		break;

	case 4:
		return bottom;
		break;

	default:
		return Vector2f(0, 0);
		break;
	}

}

void Asteroide::Actualizar(float deltaTime, Vector2u size) {
	velocidad = rand() % 1 + 0.05f;
	Vector2f desplazamiento = direccion * velocidad * deltaTime;

	ManejarBordes(size);
	sprite_asteroide.move(desplazamiento);

}

void Asteroide::Romperse(std::vector<Asteroide>& asteroides, Vector2u size) {
	cout << "Reproduciendo sonido para el nivel: " << nivel << endl;
	//nivel--;
	int nivelNuevo = nivel - 1;
	if (nivelNuevo <= 0) {
		esta_vivo = false;
		return;
	}
	Vector2f posicion = sprite_asteroide.getPosition();

	// Reducir tamaño a la mitad
	Vector2f newSize = sprite_asteroide.getScale();
	newSize.x /= 2;
	newSize.y /= 2;


	// Ángulo aleatorio dentro de un rango de ±45° desde el ángulo original
	float angleOffset = (rand() % 61) - 30;  // Valor aleatorio entre -30° y +30°
	float newAngle = angulo + angleOffset;

	// Crear dos nuevos asteroides más pequeños
	for (int i = 0; i < 3; i++)
	{
		Asteroide newAsteroid;
		newAsteroid.sprite_asteroide.setScale(newSize);
		newAsteroid.sprite_asteroide.setPosition(posicion);
		newAsteroid.nivel=nivelNuevo;

		// Generar direcciones opuestas
		if (i == 0) {
			// El primer asteroide va en la dirección original
			newAsteroid.direccion.x = -cos(newAngle * 3.14159f / 180.0f);
			newAsteroid.direccion.y = sin(newAngle * 3.14159f / 180.0f);
		}
		else if (i == 1) {
			// El segundo asteroide va en la dirección opuesta (180 grados)
			newAngle += 180;  // Invertir dirección (añadir 180° al ángulo)
			newAsteroid.direccion.x = -cos(newAngle * 3.14159f / 180.0f);
			newAsteroid.direccion.y = sin(newAngle * 3.14159f / 180.0f);
		}
		else {
			// El tercer asteroide va en la dirección de 90° con respecto al original
			newAngle += 90;  // Desplazamiento de 90° para generar una dirección perpendicular
			newAsteroid.direccion.x = -cos(newAngle * 3.14159f / 180.0f);
			newAsteroid.direccion.y = sin(newAngle * 3.14159f / 180.0f);
		}
		

		// Agregar el nuevo asteroide a la lista
		asteroides.push_back(newAsteroid);
	}

	// Marcar el asteroide original como eliminado
	esta_vivo = false;
}

void Asteroide::Dibujar(RenderWindow* wnd) {
	if (esta_vivo) {
		wnd->draw(sprite_asteroide);
	}
	
}

Sprite& Asteroide::GetSprite() {
	return sprite_asteroide;
}

int Asteroide::GetNivel() {
	return nivel;
}

