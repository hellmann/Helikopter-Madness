#include "Projectile.hpp"

void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states)const{
	target.draw(projectileSprite, states);
	target.draw(projectileSpriteCanon, states);
}
//laddar text och sprite för båda helikoptrarnas projektiler samt sätter boundingbox
Projectile::Projectile(){
	projectileTexture.loadFromFile("Resources/Rocket3.png");
	projectileSprite.setTexture(projectileTexture);
	rect.setFillColor(sf::Color::Transparent);
	rect.setSize(sf::Vector2f(13,25));
	rect.setOrigin(0, 10);
}
//laddar spriten på kanonens projektiler och sätter boundingbox på den
Projectile::Projectile(std::string filepath){
	projectileTextureCanon.loadFromFile(filepath);
	projectileSpriteCanon.setTexture(projectileTextureCanon);
	rect2.setSize(sf::Vector2f(14, 14));
	rect2.setFillColor(sf::Color::Transparent);
}

void Projectile::Update(float dt){
	//sätter alla boundingboxes på helikopter och kanonens projektiler
	rect.setRotation(projectileSprite.getRotation());
	rect.setPosition(projectileSprite.getPosition());
	rect2.setRotation(projectileSpriteCanon.getRotation());
	rect2.setPosition(projectileSpriteCanon.getPosition());
	//räknar ut hur projektilerna ska röra sig
	projectileSprite.move((float)sin(3.14159265 * projectileSprite.getRotation() / 180.0f)*
		prSpeed * dt, -1 * (float)cos(3.14159265 * projectileSprite.getRotation() /
		180.0f)* prSpeed * dt);
	projectileSpriteCanon.move((float)sin(3.14159265 * projectileSpriteCanon.getRotation() / 180.0f)*
		prSpeed * dt, -1 * (float)cos(3.14159265 * projectileSpriteCanon.getRotation() /
		180.0f)* prSpeed * dt);
}

void Projectile::setPosition(sf::Vector2f position){
	this->projectileSprite.setPosition(position);
	
}

void Projectile::setRotation(float rotation){
	this->projectileSprite.setRotation(rotation);
}

void Projectile::setPositionCanon(sf::Vector2f position){
	this->projectileSpriteCanon.setPosition(position);
}
void Projectile::setRotationCanon(float rotation){
	this->projectileSpriteCanon.setRotation(rotation);
}
sf::Vector2f Projectile::getPosition()const{
	return this->projectileSprite.getPosition();
}

sf::FloatRect Projectile::getGlobalBounds(){
	return this->rect.getGlobalBounds();
}
sf::FloatRect Projectile::getGlobalBoundsCanon(){
	return this->rect2.getGlobalBounds();
}
