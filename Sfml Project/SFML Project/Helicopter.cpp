#include "Helicopter.hpp"

Helicopter::Helicopter(){
	this->hp = 0;
	this->speed = 0.0;
}
Helicopter::Helicopter(const int hp, const float speed){
	this->hp = hp;
	this->speed = speed;
}
void Helicopter::draw(sf::RenderTarget &target, sf::RenderStates states) const{

}

void Helicopter::setHp(const int hp){
	this->hp = hp;
}

int Helicopter::getHp()const{
	return this->hp;
}
float Helicopter::getSpeed()const{
	return this->speed;
}