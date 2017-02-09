#ifndef HELICOPTER_HPP
#define HELICOPTER_HPP
#include "SFML\Graphics.hpp"

class Helicopter: public sf::Drawable{
private:
	int hp;
	float speed;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const=0;
public:
	Helicopter();
	Helicopter(const int hp, const float speed);
	Helicopter(std::string filePath, std::string fliePath2);

	void setHp(const int hp);

	int getHp()const;
	float getSpeed()const;

	void Update(float dt);

};
#endif