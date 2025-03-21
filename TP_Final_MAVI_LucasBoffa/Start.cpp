#include "Start.h"

Start::Start() {
	_wnd = new RenderWindow(VideoMode(1280, 1080), "Asteroids");
	_crosshair = new PlayerCrosshair();
	_buffer.loadFromFile("../Sounds/temaInicio.mp3");
	_sound.setBuffer(_buffer);
	_font.loadFromFile("../Fuentes/Hyperspace.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(200);
	_text.setPosition(100,150);
	_text.setString("ASTEROIDS");
	_btnStart = new Button("START",_font,50,Vector2f(450,600),Vector2f(300,150));    //string& text, Font& font, unsigned int characterSize, Vector2f& position, Vector2f& size
	_btnTutorial = new Button("TUTORIAL", _font, 50, Vector2f(450, 850), Vector2f(300, 150));
	_start = false;
	_wnd->setMouseCursorVisible(false);
	_tutorial = false;
}

void Start::ProcesarEventos() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	Event evt;
	while (_wnd->pollEvent(evt)) {

		if (_tutorial) {
			_text.setCharacterSize(28);
			_text.setPosition(60, 150);
			_text.setString("Dispara a los asteroides utilizando la barra espaciadora,\npero ten cuidado!!!\n"
				"Los asteroides pueden romperse en fragmentos mas peque�os.\n"
				"Despl�zate con teclas W y S, y rota con teclas A y D para esquivarlos.\n"
				"Compite con tus amigos para ver quien gana mas puntos \n(los m�s peque�os dan m�s puntos).\n"
				"Chocar un asteroide hacer perder una vida, tienes 5\n\n\n"
			"W = DESPLAZAR HACIA ADELANTE\nS = DESPLAZAR HACIA ATR�S\nA - D = ROTACI�N\nSPACE = DISPARAR");
			_btnTutorial->setText("VOLVER");
		}
		else {
			_text.setPosition(100, 150);
			_text.setCharacterSize(200);
			_text.setString("ASTEROIDS");
			_btnTutorial->setText("TUTORIAL");
		}


		if (evt.type == Event::Closed) {
			_wnd->close();
		}
		if (evt.type == Event::MouseMoved) {
			_crosshair->Posicionar(evt.mouseMove.x, evt.mouseMove.y);
		}
		if (evt.type == Event::MouseButtonPressed && evt.mouseButton.button == Mouse::Left) {
			if (_btnStart->isMouseOver(*_wnd) && !_tutorial) {
				IniciarJuego(); 
			}
			if (_btnTutorial->isMouseOver(*_wnd)) {
				_tutorial = !_tutorial;
			}
		}
	}
}

void Start::Loop() {
	
	PlayMusic();
	while (_wnd->isOpen()) {
		ProcesarEventos();
		Dibujar();
	}
}


void Start::Dibujar() {
	_wnd->clear();
	if (!_tutorial) {
		_btnStart->Dibujar(_wnd);
	}
	_btnTutorial->Dibujar(_wnd);
	_crosshair->Dibujar(_wnd);
	_wnd->draw(_text);
	_wnd->display();
}

void Start::PlayMusic() {
	_sound.setVolume(60);
	_sound.setLoop(true);
	_sound.play();
}

void Start::IniciarJuego() {
	_start = true;
	_sound.stop();
	_wnd->close();
}

bool Start::GetStart() {
	return _start;
}