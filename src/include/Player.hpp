/*
* Nome: Marlon Baptista de Quadros
*/
#ifndef CGF_PLAYER_H_
#define CGF_PLAYER_H_

#include "Sprite.hpp"

namespace cgf{
	class Player{
		public:
			Player(char* local_image, int x, int y, int id, int velocidade);
            virtual void draw(sf::RenderWindow* screen);
            virtual void move(float dirx, float diry);
			int getId() { return id; };
		private:
            cgf::Sprite sprite;
			int id;

		protected:
			Player();
			~Player();
	};
}
#endif