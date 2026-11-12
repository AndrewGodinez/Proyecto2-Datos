#include "CajaTexto.h"

CajaTexto* CajaTexto::cajaActiva = nullptr;

CajaTexto::CajaTexto() {
	limites = sf::FloatRect(0, 0, 150, 32);
	texto = "";
	placeholder = "";
	tieneFoco = false;
	maxCaracteres = 28;
}

CajaTexto::CajaTexto(float x, float y, float ancho, float alto, 
					 const string& placeholder, int maxCaracteres) {
	this->limites = sf::FloatRect(x, y, ancho, alto);
	this->texto = "";
	this->placeholder = placeholder;
	this->tieneFoco = false;
	this->maxCaracteres = maxCaracteres;
}

void CajaTexto::procesarEvento(const sf::Event& evento) {
	if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f punto(static_cast<float>(evento.mouseButton.x), static_cast<float>(evento.mouseButton.y));
		tieneFoco = limites.contains(punto);
		if (tieneFoco) {
			cajaActiva = this;
		} else if (cajaActiva == this) {
			cajaActiva = nullptr;
		}
	}
	
	if (tieneFoco && evento.type == sf::Event::TextEntered) {
		sf::Uint32 codigo = evento.text.unicode;
		
		if (codigo == 8) { 
			if (!texto.empty()) {
				texto.pop_back();
			}
		} else if (codigo == 13 || codigo == 27) { 
			tieneFoco = false;
			cajaActiva = nullptr;
		} else if (codigo >= 32 && codigo <= 126) { 
			if (static_cast<int>(texto.size()) < maxCaracteres) {
				texto += static_cast<char>(codigo);
			}
		}
	}
}

void CajaTexto::dibujar(sf::RenderWindow& ventana) {
	sf::Color borde = tieneFoco ? Dibujo::COLOR_CIAN_ACENTO : Dibujo::COLOR_BORDE;
	float grosorBorde = tieneFoco ? 2.0f : 1.0f;
	
	Dibujo::dibujarPanel(ventana, limites.left, limites.top, limites.width, limites.height, 
						 sf::Color(18, 24, 38), borde, grosorBorde);
	
	float textoX = limites.left + 8.0f;
	float textoY = limites.top + (limites.height / 2.0f) - 6.0f;
	
	if (texto.empty()) {
		Dibujo::dibujarTexto(ventana, placeholder, textoX, textoY, 12, Dibujo::COLOR_TEXTO_MUTED);
	} else {
		Dibujo::dibujarTexto(ventana, texto, textoX, textoY, 12, Dibujo::COLOR_TEXTO_TITULO);
	}
	
	if (tieneFoco) {
		int tiempoMs = relojCursor.getElapsedTime().asMilliseconds();
		if ((tiempoMs / 500) % 2 == 0) {
			sf::Text txtTmp;
			txtTmp.setFont(Dibujo::getFuente());
			txtTmp.setCharacterSize(12);
			txtTmp.setString(texto);
			float cursorX = textoX + txtTmp.getLocalBounds().width + 2.0f;
			sf::RectangleShape cursor(sf::Vector2f(2.0f, limites.height - 12.0f));
			cursor.setPosition(cursorX, limites.top + 6.0f);
			cursor.setFillColor(Dibujo::COLOR_CIAN_ACENTO);
			ventana.draw(cursor);
		}
	}
}

string CajaTexto::getTexto() const {
	return texto;
}

void CajaTexto::setTexto(const string& nuevoTexto) {
	texto = nuevoTexto;
}

void CajaTexto::limpiar() {
	texto = "";
}

bool CajaTexto::getTieneFoco() const {
	return tieneFoco;
}

void CajaTexto::setFoco(bool foco) {
	tieneFoco = foco;
}

bool CajaTexto::hayCajaActiva() {
	return cajaActiva != nullptr;
}

void CajaTexto::quitarFocoActivo() {
	if (cajaActiva != nullptr) {
		cajaActiva->tieneFoco = false;
		cajaActiva = nullptr;
	}
}
