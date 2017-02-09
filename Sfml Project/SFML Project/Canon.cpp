#include "Canon.hpp"
//laddar sprite och textur, sätter även boundingbox
Canon::Canon(int hp){
	canonTexture.loadFromFile("Resources/Canon.png");
	canonSprite.setTexture(canonTexture);
	canonSprite.setTextureRect(sf::IntRect(0, 0, 60, 85));
	canonSprite.setOrigin(30, 42);
	canonSprite.setPosition(1000, 1500);
	rect.setSize(sf::Vector2f(50, 85));
	rect.setOrigin(25, 42);
	rect.setFillColor(sf::Color::Transparent);

	this->hp = hp;
}

void Canon::Update(float dt, Player p){
	//sätter boundiung box på kanones position
	rect.setPosition(canonSprite.getPosition());
	rect.setRotation(canonSprite.getRotation()-30);
	float angle = atan2(p.getPosition().y - canonSprite.getPosition().y,
		p.getPosition().x - canonSprite.getPosition().x);
	//även här kollar jag om helikoptern är tillräkligt nära för att börja skjuta på spelaren
	if (proximity(p,50,500)){
		canonSprite.setRotation((angle * 180 / (float)3.141) + 120);
	}
}

void Canon::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(canonSprite, states);
}
//räknar avståndet
bool Canon::proximity(Player p, float radius1, float radius2){
	sf::Vector2f dist = p.getPosition() - canonSprite.getPosition();
	float radius = radius1 + radius2;
	return (dist.x*dist.x + dist.y*dist.y) < (radius*radius);

}

sf::Vector2f Canon::getPosition(){
	return this->canonSprite.getPosition();
}
float Canon::getRotation(){
	return this->canonSprite.getRotation();
}
//hämtar boundingbox positionen
sf::FloatRect Canon::getGlobalBounds(){
	return this->rect.getGlobalBounds();
}

void Canon::setHp(const int hp){
	this->hp = hp;
}
int Canon::getHp()const{
	return this->hp;
}