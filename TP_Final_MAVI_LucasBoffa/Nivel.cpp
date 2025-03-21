#include "Nivel.h"
#include <iostream>

using namespace sf;
using namespace std;

Nivel::Nivel(){

    tiempoEntreDisparos = 200.f;

	
	
	
	_jugador = new Player(_wnd);
    deltaTime = 0;
    _bufferMusica.loadFromFile("../Sounds/temaJuego.mp3");
    _soundMusica.setBuffer(_bufferMusica);

    //acceder a los sonidos de explosiones con asteroides
    _explosion1.loadFromFile("../Sounds/explosion1.wav");
    _explosion2.loadFromFile("../Sounds/explosion2.wav");
    _explosion3.loadFromFile("../Sounds/explosion3.wav");
    _sonidoAsteroide1.setBuffer(_explosion1);
    _sonidoAsteroide2.setBuffer(_explosion2);
    _sonidoAsteroide3.setBuffer(_explosion3);

    //sonido de disparos
    _sonidoDisparo.loadFromFile("../Sounds/fire.wav");
    _sonidoBala.setBuffer(_sonidoDisparo);

    //textos
    _fuente.loadFromFile("../Fuentes/Hyperspace.ttf");
    _textoPuntos.setFont(_fuente);   
    _textoPuntos.setFillColor(Color::Yellow);
    _textoVidas.setFont(_fuente);    
    _textoVidas.setFillColor(Color::Red);

}

Nivel::~Nivel(){

}

void Nivel::Iniciar() {
    _wnd = new RenderWindow(VideoMode(1280, 1080), "Asteroids");
    size = Vector2u(_wnd->getSize().x, _wnd->getSize().y);
    _wnd->setFramerateLimit(120);
    _puntos = 0;
    _vidas = 5;
    _jugador->Iniciar(_wnd);
    _textoPuntos.setPosition(20, 25);
    _textoPuntos.setString("PUNTOS: " + (to_string(_puntos)));
    _textoVidas.setPosition(1000, 25);
    _textoVidas.setString("VIDAS: " + (to_string(_vidas)));
    
    PlayMusic();
    ProcesarEventos();
}

void Nivel::ProcesarEventos() {
    
    while (_wnd->isOpen())
    {
        sf::Event event;
        while (_wnd->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _wnd->close();
            }
			_jugador->ProcesarEventos();
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (timer > 0) continue; // Si el timer no ha terminado, no disparar
                timer = tiempoEntreDisparos;

                Disparo nuevaBala;
                nuevaBala.Iniciar(_jugador->GetPosition(), _jugador->GetRotation());

                _sonidoBala.play();
                balas.push_back(nuevaBala);
            }
        }

		deltaTime = _clock.restart().asMilliseconds();

        Actualizar();
        if (_vidas <= 0) {
            _soundMusica.stop();
            _jugador->MoveStop();
            sleep(sf::seconds(1.5f));
            _wnd->close();  // Cerrar la ventana.
            break;          // Salir del bucle principal.
        }
        Dibujar();

    }
}



void Nivel::Actualizar() {
	timer -= deltaTime;

    GenerarAsteroides();
	_jugador->Actualizar(size, deltaTime);

    // Reiniciar el flag de colisión al inicio de cada frame
    bool _jugadorHerido = false;

    //COLISIONES ENTRE JUGADOR Y ASTEROIDES
    for (int i = 0; i < asteroides.size(); i++)
    {
        asteroides[i].Actualizar(deltaTime, size);

        if (_jugador->GetSprite().getGlobalBounds().intersects(asteroides[i].GetSprite().getGlobalBounds())) {
            if (!_jugadorHerido) { // Solo restar una vida si el jugador no ha sido herido en este frame
                cout << "COLISION DETECTADA " << endl;
                _vidas--;
                ActualizarVidas();
                _jugador->Iniciar(_wnd);
                ReproducirExplosion(asteroides[i].GetNivel());
                _jugadorHerido = true; // Marcar al jugador como herido en este frame
            }
            if (asteroides[i].Esta_Vivo())
            {
                asteroides[i].Romperse(asteroides, size);
                asteroides.erase(asteroides.begin() + i); // Eliminar asteroide original
                i--; // Ajustar índice después de eliminar
            }
        }
        

    }
   
    //COLISION ENTRE DISPAROS Y ASTEROIDES
    for (int i = 0; i < asteroides.size(); i++)
    {
        for (int j = 0; j < balas.size(); j++)
        {
            if (balas[j].Esta_Vivo())
            {
                if (!balas[j]._bala.getGlobalBounds().intersects(asteroides[i].sprite_asteroide.getGlobalBounds()))
                {
                    balas[j].Actualizar(deltaTime);

                }
                else
                {
                    balas[j].Morir();
                    ReproducirExplosion(asteroides[i].GetNivel());
                    if (asteroides[i].Esta_Vivo())
                    {
                        switch (asteroides[i].GetNivel()) {
                        case 1:
                            _puntos += 25;
                            break;
                        case 2:
                            _puntos += 15;
                            break;
                        case 3:
                            _puntos += 10;
                            break;
                        }

                        ActualizarPuntos();

                        asteroides[i].Romperse(asteroides, size);
                        asteroides.erase(asteroides.begin() + i); // Eliminar asteroide original
                        i--; // Ajustar índice después de eliminar
                    }

                    

                }
            }
        }
    }

    // COLISIONES ENTRE ASTEROIDES
    for (int i = 0; i < asteroides.size(); i++) {
        for (int j = i + 1; j < asteroides.size(); j++) {
            if (asteroides[i].GetSprite().getGlobalBounds().intersects(asteroides[j].GetSprite().getGlobalBounds())) {
                // Cambiar la dirección de ambos asteroides
                CambiarDireccionAsteroide(asteroides[i]);
                CambiarDireccionAsteroide(asteroides[j]);

                // Mover los asteroides ligeramente para evitar que se superpongan
                MoverAsteroidesAparte(asteroides[i], asteroides[j]);
            }
        }
    }
}



// Método para cambiar la dirección de un asteroide
void Nivel::CambiarDireccionAsteroide(Asteroide& asteroide) {
    float anguloActual = asteroide.GetAngulo(); // Obtener el ángulo actual del asteroide
    float nuevoAngulo = anguloActual + (rand() % 60 - 30); // Cambiar el ángulo entre -30 y +30 grados
    asteroide.SetAngulo(nuevoAngulo); // Establecer el nuevo ángulo
}

// Método para mover los asteroides ligeramente y evitar que se superpongan
void Nivel::MoverAsteroidesAparte(Asteroide& asteroide1, Asteroide& asteroide2) {
    // Obtener las posiciones actuales de los asteroides
    Vector2f pos1 = asteroide1.GetSprite().getPosition();
    Vector2f pos2 = asteroide2.GetSprite().getPosition();

    // Calcular la dirección en la que deben moverse para separarse
    Vector2f direccion = pos1 - pos2;
    float distancia = sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
    if (distancia == 0) return; // Evitar división por cero

    // Normalizar la dirección y mover los asteroides
    direccion /= distancia;
    asteroide1.GetSprite().move(direccion * 5.f); // Mover asteroide1
    asteroide2.GetSprite().move(-direccion * 5.f); // Mover asteroide2 en dirección opuesta
}




void Nivel::GenerarAsteroides() {
    if (asteroides.size() < 6) { // Límite de asteroides en pantalla
        int cantidad = rand() % 2 + 1; // Agregar 1 o 2 asteroides
        for (int i = 0; i < cantidad; i++) {
            Asteroide nuevoAsteroide;
            nuevoAsteroide.Iniciar(size); // Método que debes definir en Asteroide.cpp
            asteroides.push_back(nuevoAsteroide);

            // Debug: Mostrar posición en consola
            Vector2f pos = nuevoAsteroide.sprite_asteroide.getPosition();
            cout << "Asteroide creado en: " << pos.x << ", " << pos.y << endl;
        }
    }
}

void Nivel::Dibujar() {

    _wnd->clear();

    _jugador->Dibujar(_wnd);

    _wnd->draw(_textoPuntos);
    _wnd->draw(_textoVidas);

    //dibujar asteroides
    for (int i = 0; i < asteroides.size(); i++)
    {
        if (asteroides[i].Esta_Vivo())
        {
            asteroides[i].Dibujar(_wnd);
        }
    }

    //dibujar balas
    for (int i = 0; i < balas.size(); i++)
    {
        if (balas[i].Esta_Vivo())
        {
            balas[i].Dibujar(_wnd);
        }
    }

	_wnd->display();
}

int Nivel::GetVidas() {
    return _vidas;
}

int Nivel::GetPuntos() {
    return _puntos;
}


void Nivel::ReproducirExplosion(int nivel) {
   
    switch (nivel) {
    case 1:
        _sonidoAsteroide1.setVolume(65);
        _sonidoAsteroide1.play();
        break;
    case 2:
        _sonidoAsteroide2.setVolume(75);
        _sonidoAsteroide2.play();
        break;
    case 3:
        _sonidoAsteroide3.setVolume(85);
        _sonidoAsteroide3.play();
        break;
    default:
        _sonidoAsteroide3.setVolume(85);
        _sonidoAsteroide3.play();
        break;
    }
    
}

void Nivel::ActualizarPuntos() {
    _textoPuntos.setString("PUNTOS: "+(to_string(_puntos)));
}

void Nivel::ActualizarVidas() {
    _textoVidas.setString("VIDAS: " + (to_string(_vidas)));
}

void Nivel::PlayMusic() {
    _soundMusica.setVolume(40);
    _soundMusica.setLoop(true);
    _soundMusica.play();
}




