#include "Player.hpp"
#include <iostream>

Player::Player(const int hp, const float speed):Helicopter(hp, speed) {
	//laddar in player helicopter spriten
	playerTextUp.loadFromFile("Resources/ChopperUp.png");
	
	playerSprite.setTexture(playerTextUp);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 221, 221));
	
	playerSprite.setOrigin(221/2, 221/2);
	playerSprite.setPosition(2690, 1910);
	playerSprite.setRotation(30);
	
	//laddar in roterbladen
	rotorText.loadFromFile("Resources/Blades.png");
	rotorSprite.setTexture(rotorText);
	rotorSprite.setTextureRect(sf::IntRect(0, 0, 76, 76));
	//players boundingbox
	rect.setSize(sf::Vector2f(60, 147));
	rect.setOrigin(30, 40);
	rect.setFillColor(sf::Color::Transparent);

	//h�r �r variabler f�r animationen f�r rotorbladen
	pCurrentKeyFrame = sf::Vector2i(0, 0);
	pKeyFrameSize = sf::Vector2i(76, 76);
	pSpriteSheetWidth = 4;
	pAnimationSpeed = 0.1f;
	pKeyFrameDuration = 0.0f;

}


void Player::Update(float dt){
	//s�tter players boundingbox p� players position
	rect.setRotation(playerSprite.getRotation());
	rect.setPosition(playerSprite.getPosition());

	pKeyFrameDuration += dt;
	//h�r ser jag till att om spelaren f�rs�ker �ka utanf�r sprite bakgrunden 
	//s� v�nder helikoptern 180grader
	if (playerSprite.getPosition().x > 3490){
		playerSprite.setRotation(playerSprite.getRotation()+180);
	}
	if (playerSprite.getPosition().x < 0){
		playerSprite.setRotation(playerSprite.getRotation() + 180);
	}
	if (playerSprite.getPosition().y > 2470){
		playerSprite.setRotation(playerSprite.getRotation() + 180);
	}
	if (playerSprite.getPosition().y < 0){
		playerSprite.setRotation(playerSprite.getRotation() + 180);
	}
	//h�r kollar jag spelarens r�relse
	//v�nster och h�ger roterar helikoptern
	//up och ner r�r helikoptern i fram och bak i den grad helikoptern �r roterad
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerSprite.setRotation(playerSprite.getRotation() - (dt* 80));	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerSprite.setRotation(playerSprite.getRotation() + (dt * 80));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerSprite.move((float)sin(3.14159265 * playerSprite.getRotation() / 180.0f)*
			this->getSpeed() * dt, -1 * (float)cos(3.14159265 * playerSprite.getRotation() /
			180.0f)* this->getSpeed() * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		playerSprite.move(-(float)sin(3.14159265 * playerSprite.getRotation() / 180.0f)*
			this->getSpeed() * dt, -1 * -(float)cos(3.14159265 * playerSprite.getRotation() /
			180.0f)* this->getSpeed() * dt);
	}
	//s�tter rotorbladen p� helikopterns position
	rotorSprite.setPosition(playerSprite.getPosition().x-40,
		playerSprite.getPosition().y-40);

	//f�r rotorbladen att r�ra sig
	if (pKeyFrameDuration >= pAnimationSpeed)
	{
		pCurrentKeyFrame.x++;

		if (pCurrentKeyFrame.x >= pSpriteSheetWidth)
			pCurrentKeyFrame.x = 0;

		rotorSprite.setTextureRect(sf::IntRect(pCurrentKeyFrame.x * pKeyFrameSize.x,
			pCurrentKeyFrame.y * pKeyFrameSize.y, pKeyFrameSize.x, pKeyFrameSize.y));
	}
}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(playerSprite, states);
	target.draw(rotorSprite, states);
	
}

sf::Vector2f Player::getPosition(){
	return playerSprite.getPosition();
}
float Player::getRotation(){
	return this->playerSprite.getRotation();
}
//f� global position p� helikopterns bounding box
sf::FloatRect Player::getGlobalBounds(){
	return this->rect.getGlobalBounds();
}