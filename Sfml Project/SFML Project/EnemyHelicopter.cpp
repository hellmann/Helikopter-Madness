#include "EnemyHelicopter.hpp"

//laddar in texturen, spriten och s�tter boundingbox
//s�tter �ven v�rden p� variablerna till rotorblads animationen
EnemyHelicopter::EnemyHelicopter(const int hp, const float speed):Helicopter(hp,speed){
	enemyText.loadFromFile("Resources/EnemyHelicopter.png");
	rotorText.loadFromFile("Resources/EnemyBlades.png");

	enemySprite.setTexture(enemyText);
	enemySprite.setTextureRect(sf::IntRect(0, 0, 219, 219));
	enemySprite.setOrigin(110, 110);
	enemySprite.setPosition(1500, 1000);
	
	rotorSprite.setTexture(rotorText);
	rotorSprite.setTextureRect(sf::IntRect(0, 0, 66, 66));

	rect.setSize(sf::Vector2f(60, 147));
	rect.setOrigin(30, 40);
	rect.setFillColor(sf::Color::Transparent);

	eCurrentKeyFrame = sf::Vector2i(0, 0);
	eKeyFrameSize = sf::Vector2i(66, 66);
	eSpriteSheetWidth = 4;
	eAnimationSpeed = 0.1f;
	eKeyFrameDuration = 0.0f;
}

void EnemyHelicopter::Update(float dt, Player p){
	//s�tter boundingbox positionen p� helikoptern
	rect.setRotation(enemySprite.getRotation());
	rect.setPosition(enemySprite.getPosition());
	//r�knar ut vinkeln 1 g�ng s� jag slipper r�kna ut de p� alla st�llen
	float angle = atan2(p.getPosition().y - enemySprite.getPosition().y,
			p.getPosition().x - enemySprite.getPosition().x);

	eKeyFrameDuration += dt;
	//kollar om helikoptern �r n�ra spelaren
	//om den �r sann s� stannar helikoptern och b�rjar skjuta
	if (proximity(p, 50.0, 300.0) == true){
		enemySprite.setRotation((angle * 180 / (float)3.141) + 90);
	}
	//�r den inte tillr�kligt n�ra s� f�ljer den efter helikoptern
	else if (proximity(p, 50.0, 700.0) == true){
		enemySprite.move(cos(angle) *  this->getSpeed() * dt, 0);
		enemySprite.move(0, sin(angle)* this->getSpeed() * dt);
		enemySprite.setRotation((angle * 180 / (float)3.141) + 90);

	}
	
	rotorSprite.setPosition(enemySprite.getPosition().x - 33,
		enemySprite.getPosition().y - 33);

	if (eKeyFrameDuration >= eAnimationSpeed)
	{
		eCurrentKeyFrame.x++;

		if (eCurrentKeyFrame.x >= eSpriteSheetWidth)
			eCurrentKeyFrame.x = 0;

		rotorSprite.setTextureRect(sf::IntRect(eCurrentKeyFrame.x * eKeyFrameSize.x,
			eCurrentKeyFrame.y * eKeyFrameSize.y, eKeyFrameSize.x, eKeyFrameSize.y));
	}
	
}

void EnemyHelicopter::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(enemySprite, states);
	target.draw(rotorSprite, states);
}
//h�r r�knar jag avst�nd mellan spelare och fiende
bool EnemyHelicopter::proximity(Player p, float radius1, float radius2){
	sf::Vector2f dist = p.getPosition() - enemySprite.getPosition();
	float radius = radius1 + radius2;
	return (dist.x*dist.x + dist.y*dist.y) < (radius*radius);

}
//position f�r fiendens boundingbox
sf::FloatRect EnemyHelicopter::getGlobalBounds(){
	return this->rect.getGlobalBounds();
}

sf::Vector2f EnemyHelicopter::getPosition(){
	return this->enemySprite.getPosition();
}

float EnemyHelicopter::getRotation(){
	return this->enemySprite.getRotation();
}