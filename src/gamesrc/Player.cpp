/*
* Nome: Marlon Baptista de Quadros
*/
#include "include/Player.hpp"

namespace cgf{
	Player::Player(char* local_image, int x, int y, int id, int velocidade){
		sprite.load(local_image);
		sprite.setPosition(x, y);
		this->id = id;
	}

	Player::Player(char* local_xml){
		sprite.loadXML(local_xml);
	}

	void Player::draw(sf::RenderWindow* window){
		window->draw(sprite);
	}

	void Player::move(float dirx, float diry){
		sprite.move(dirx, diry);
	}
} // namespace cgf
