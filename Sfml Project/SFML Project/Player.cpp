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

	//här är variabler för animationen för rotorbladen
	pCurrentKeyFrame = sf::Vector2i(0, 0);
	pKeyFrameSize = sf::Vector2i(76, 76);
	pSpriteSheetWidth = 4;
	pAnimationSpeed = 0.1f;
	pKeyFrameDuration = 0.0f;

}


void Player::Update(float dt){
	//sätter players boundingbox på players position
	rect.setRotation(playerSprite.getRotation());
	rect.setPosition(playerSprite.getPosition());

	pKeyFrameDuration += dt;
	//här ser jag till att om spelaren försöker åka utanför sprite bakgrunden 
	//så vänder helikoptern 180grader
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
	//här kollar jag spelarens rörelse
	//vänster och höger roterar helikoptern
	//up och ner rör helikoptern i fram och bak i den grad helikoptern är roterad
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
	//sätter rotorbladen på helikopterns position
	rotorSprite.setPosition(playerSprite.getPosition().x-40,
		playerSprite.getPosition().y-40);

	//får rotorbladen att röra sig
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
//få global position på helikopterns bounding box
sf::FloatRect Player::getGlobalBounds(){
	return this->rect.getGlobalBounds();
}