#include "Game.hpp"
#include <iostream>
#include <sstream>
//vanliga expanderings funktioner för spelare och fiender
void Game::pExpand(){
	this->playerCapacity = this->playerCapacity * 2;
	Projectile **tempArr = new Projectile*[this->playerCapacity];
	for (int i = 0; i < this->nrOfPlayerProjectiles; i++){
		tempArr[i] = this->playerProjectiles[i];
	}
	delete[] this->playerProjectiles;
	this->playerProjectiles = tempArr;

}
void Game::eExpand(){
	this->enemyCapacity = this->enemyCapacity * 2;
	Projectile **tempArr = new Projectile*[this->enemyCapacity];
	for (int i = 0; i < this->nrOfEnemyProjectiles; i++){
		tempArr[i] = this->enemyProjectiles[i];
	}
	delete[] this->enemyProjectiles;
	this->enemyProjectiles = tempArr;
}
void Game::cExpand(){
	this->canonCapacity = this->canonCapacity * 2;
	Projectile **tempArr = new Projectile*[this->canonCapacity];
	for (int i = 0; i < this->nrOfCanonProjectiles; i++){
		tempArr[i] = this->canonProjectiles[i];
	}
	delete[]this->canonProjectiles;
	this->canonProjectiles = tempArr;
}

Game::Game(const std::string &difficulty){
	//kollar vilken svårighetsgrad spelaren har valt
	//beroende på vad man väljer så får fiender mer hp och hastighet eller
	//lägre hastighet och hp
	if (difficulty == "easy"){
		pPlayer = new Player(10, 550.0);
		eEnemy = new EnemyHelicopter(5, 450.0);
		eCanon = new Canon(5);
	}
	if (difficulty == "medium"){
		pPlayer = new Player(7, 500.0);
		eEnemy = new EnemyHelicopter(7, 500.0);
		eCanon = new Canon(7);
	}
	if (difficulty == "hard"){
		pPlayer = new Player(5, 450.0);
		eEnemy = new EnemyHelicopter(10, 550.0);
		eCanon = new Canon(10);
	}
	//laddar in bakgrunden
	mBackgroundTex.loadFromFile("Resources/background.jpg");
	mBackgroundSprite.setTexture(mBackgroundTex);
	
	this-> counter = 0;
	this-> counter2 = 0;
	this-> counter3 = 0;

	this->playerCapacity = 10;
	this->nrOfPlayerProjectiles = 0;
	this->playerProjectiles = new Projectile*[this->playerCapacity];
	for (int i = 0; i < this->playerCapacity; i++){
		this->playerProjectiles[i] = nullptr;
	}

	this->enemyCapacity = 10;
	this->nrOfEnemyProjectiles = 0;
	this->enemyProjectiles = new Projectile*[this->enemyCapacity];
	for (int i = 0; i < this->nrOfEnemyProjectiles; i++){
		this->enemyProjectiles[i] = nullptr;
	}

	this->canonCapacity = 10;
	this->nrOfCanonProjectiles = 0;
	this->canonProjectiles = new Projectile*[this->canonCapacity];
	for (int i = 0; i < this->nrOfCanonProjectiles; i++){
		this->canonProjectiles[i] = nullptr;
	}

	filepath = "Resources/CanonBall.png";

	//initierar explosions animationen
	this->explosionText.loadFromFile("Resources/ExplosionStor.png");
	this->explosionSprite.setTexture(explosionText);
	this->explosionSprite.setOrigin(50, 35);
	this->explosionSprite.setTextureRect(sf::IntRect(0, 0, 100, 70));
	this->currentKeyFrame = sf::Vector2i(0, 0);
	this->keyFrameSize = sf::Vector2i(100, 70);
	this->spriteSheetWidth = 5;
	this->animationSpeed = 0.3f;
	this->keyFrameDuration = 0.0f;

	//variabler till rutan där ditt hp och din highscore står
	this->font.loadFromFile("Resources/arial.ttf");
	this->text1.setFont(font);
	this->text1.setColor(sf::Color::Red);
	
}

Game::~Game(){
	for (int i = 0; i < this->nrOfPlayerProjectiles; i++){
		delete this->playerProjectiles[i];
	}
	for (int i = 0; i < this->nrOfEnemyProjectiles; i++){
		delete this->enemyProjectiles[i];
	}
	for (int i = 0; i < this->nrOfCanonProjectiles; i++){
		delete this->canonProjectiles[i];
	}
	delete[]this->playerProjectiles;
	delete[]this->enemyProjectiles;
	delete[]this->canonProjectiles;
	delete[]this->pPlayer;
	delete[]this->eEnemy;
	delete[]this->eCanon;
}
void Game::Update(float dt, float score[]){
	pPlayer->Update(dt);

	this->keyFrameDuration += dt;
	/*kollar om spelaren trycker ner space för att skjuta
	varje gång man trycker ner space eller håller inne space så ökar counter så man kan skjuta*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		if (this->counter <= 0){
			this->addPlayerProjectiles(*pPlayer);
		}
		this->counter++;
	}
	//sätter rutan med ditt hp och highscore uppe i väsntra hörnet
	this->text1.setPosition(this->pPlayer->getPosition().x - 550, this->pPlayer->getPosition().y - 350);
	//uppdaterar rutan med ditt highscore
	this->highscore(score);
	//kollar om fienden lever, om fienden lever så uppdaterar den och skjuter
	if (this->eEnemy->getHp() >= 1){
	eEnemy->Update(dt, *pPlayer);
		if (this->eEnemy->proximity(*pPlayer, 50.0, 300.0) == true){
			if (this->counter2 <= 0){
				this->addEnemyProjectiles(*eEnemy);
			}
			this->counter2++;
		}
	}
	//samma sak för kanonen
	if (this->eCanon->getHp() >= 1){
		eCanon->Update(dt, *pPlayer); 
		if (this->eCanon[0].proximity(*pPlayer, 40, 500)){
			if (this->counter3 <= 0){
				this->addCanonProjectile(*eCanon);
			}
			this->counter3++;
		}
	}
	//uppdaterar alla projektiler
	for (int i = 0; i < this->nrOfEnemyProjectiles; i++){
		this->enemyProjectiles[i]->Update(dt);
	}
	for (int i = 0; i < this->nrOfPlayerProjectiles; i++){
		this->playerProjectiles[i]->Update(dt);
	}
	for (int i = 0; i < this->nrOfCanonProjectiles; i++){
		this->canonProjectiles[i]->Update(dt);
	}
	//sätter alla counters till 0 efter de nått 15
	if (this->counter >= 15){
		this->counter = 0;
	}
	if (this->counter2 >= 15){
		this->counter2 = 0;
	}
	if (this->counter3 >= 15){
		this->counter3 = 0;
	}
	//kollar kollision mellan fiender och spelar projektiler 
	//samt mellan spelare och fiende projektiler
	this->enemyCollision();
	this->playerCollision();
	
	//explosions animationen
	if (this->keyFrameDuration >= this->animationSpeed)
	{
		this->currentKeyFrame.x++;

		if (this->currentKeyFrame.x >= this->spriteSheetWidth){
			this->output = false;
			this->currentKeyFrame.x = 0;
		}

		this->explosionSprite.setTextureRect(sf::IntRect(this->currentKeyFrame.x * this->keyFrameSize.x,
			this->currentKeyFrame.y * this->keyFrameSize.y, this->keyFrameSize.x, this->keyFrameSize.y));
	}

}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(mBackgroundSprite, states);
	for (int i = 0; i < this->nrOfEnemyProjectiles; i++){
		target.draw(*this->enemyProjectiles[i], states);
	}
	for (int i = 0; i < this->nrOfPlayerProjectiles; i++){
		target.draw(*this->playerProjectiles[i], states);
	}
	for (int i = 0; i < this->nrOfCanonProjectiles; i++){
		target.draw(*this->canonProjectiles[i], states);
	}
	if (this->eCanon->getHp() >= 1){
		target.draw(this->eCanon[0], states);
	}
	if (this->output == true){
		target.draw(this->explosionSprite, states);
	}
	target.draw(this->pPlayer[0], states);
	if (this->eEnemy->getHp() >= 1){
		target.draw(this->eEnemy[0], states);
	}
	target.draw(text1, states);
}

sf::Vector2f Game::getPlayerPosition(){
	return this->pPlayer[0].getPosition();
}
/*denna funktionen gör så att "kameran" aldrig går utanför min bakgrunds sprite även
när spelaren närmar sig kanten*/
sf::View Game::cameraFollow(sf::View &player_view){
	this->text1.setPosition(player_view.getCenter().x-600, player_view.getCenter().y-400);
	float limitleft = 600;
	float limitRight = 2890;
	float limitTop =400;
	float limitBottom = 2070;

	float cameraX = pPlayer->getPosition().x;
	float cameraY = pPlayer->getPosition().y;

	if (cameraX < limitleft){
		cameraX = limitleft;
	}
	else if (cameraX>limitRight){
		cameraX = limitRight;
	}

	if (cameraY < limitTop){
		cameraY = limitTop;
	}
	else if (cameraY>limitBottom){
		cameraY = limitBottom;
	}
	player_view.setCenter(cameraX, cameraY);
	this->text1.setPosition(player_view.getCenter().x - 600, player_view.getCenter().y - 400);
	
	return player_view;
}
//lägger till projektiler
void Game::addEnemyProjectiles(EnemyHelicopter &enemy){
	if (this->nrOfEnemyProjectiles == this->enemyCapacity){
		this->eExpand();
	}
	this->enemyProjectiles[this->nrOfEnemyProjectiles] = new Projectile();
	this->enemyProjectiles[this->nrOfEnemyProjectiles]->setRotation(enemy.getRotation());
	this->enemyProjectiles[this->nrOfEnemyProjectiles]->setPosition(enemy.getPosition());
	this->nrOfEnemyProjectiles++;
}

void Game::addPlayerProjectiles(Player &player){
	if (this->nrOfPlayerProjectiles == this->playerCapacity){
		this->pExpand();
	}
	this->playerProjectiles[this->nrOfPlayerProjectiles] = new Projectile();
	this->playerProjectiles[this->nrOfPlayerProjectiles]->setRotation(player.getRotation());
	this->playerProjectiles[this->nrOfPlayerProjectiles]->setPosition(player.getPosition());
	this->nrOfPlayerProjectiles++;
}
void Game::addCanonProjectile(Canon &canon){
	if (this->nrOfCanonProjectiles == this->canonCapacity){
		this->cExpand();
	}
	this->canonProjectiles[this->nrOfCanonProjectiles] = new Projectile(this->filepath);
	this->canonProjectiles[this->nrOfCanonProjectiles]->setRotationCanon(canon.getRotation()-30);
	this->canonProjectiles[this->nrOfCanonProjectiles]->setPositionCanon(canon.getPosition());
	this->nrOfCanonProjectiles++;
}
//här jag kollar kollisioner mellan spelare och fiender
void Game::enemyCollision(){
	for (int i = 0; i < this->nrOfPlayerProjectiles; i++){
		if (this->playerProjectiles[i]->getGlobalBounds().intersects(eEnemy->getGlobalBounds())){
			this->output = true;
			this->explosionSprite.setPosition(this->playerProjectiles[i]->getPosition());
			delete this->playerProjectiles[i];
			this->playerProjectiles[i] = this->playerProjectiles[this->nrOfPlayerProjectiles - 1];
			this->nrOfPlayerProjectiles--;
			this->eEnemy->setHp(this->eEnemy->getHp() - 1);
		}
	}
	for (int i = 0; i < this->nrOfPlayerProjectiles;i++){
		if (this->playerProjectiles[i]->getGlobalBounds().intersects(eCanon->getGlobalBounds())){
			this->output = true;
			this->explosionSprite.setPosition(this->playerProjectiles[i]->getPosition());
			delete this->playerProjectiles[i];
			this->playerProjectiles[i] = this->playerProjectiles[this->nrOfPlayerProjectiles - 1];
			this->nrOfPlayerProjectiles--; 
			this->eCanon->setHp(this->eCanon->getHp() - 1);
		}
	}
}

void Game::playerCollision(){
	for (int i = 0; i < this->nrOfEnemyProjectiles; i++){
		if (this->enemyProjectiles[i]->getGlobalBounds().intersects(pPlayer->getGlobalBounds())){
			this->output = true;
			this->explosionSprite.setPosition(this->enemyProjectiles[i]->getPosition());
			delete this->enemyProjectiles[i];
			this->enemyProjectiles[i] = this->enemyProjectiles[this->nrOfEnemyProjectiles - 1];
			this->nrOfEnemyProjectiles--;
			this->pPlayer->setHp(this->pPlayer->getHp() - 1);
		}
	}
	for (int i = 0; i < this->nrOfCanonProjectiles; i++){
		if (this->canonProjectiles[i]->getGlobalBoundsCanon().intersects(pPlayer->getGlobalBounds())){
			this->output = true;
			this->explosionSprite.setPosition(this->canonProjectiles[i]->getPosition());
			delete this->canonProjectiles[i];
			this->canonProjectiles[i] = this->canonProjectiles[this->nrOfCanonProjectiles - 1];
			this->nrOfCanonProjectiles--;
			this->pPlayer->setHp(this->pPlayer->getHp() - 1);
		}
	}
}
/*denna funktionen tar in en arr med de 5 bästa scoren och lägger till din score
om du slår någon av de tidigare värden så uppdaters din highscore i slutet av spelet
den uppdaterar också så du ser din highscore medans du spelar*/
std::string Game::highscore(float score[]){
	std::stringstream output2;
	this->time = this->clock.getElapsedTime();
	score[5] = this->time.asSeconds();
	output2 << "Score: "<<time.asSeconds() << std::endl <<"HP: "<< this->pPlayer->getHp();
	this->text1.setString(output2.str().c_str());
	return output2.str().c_str();
	
}
/*här kolla jag om fienderna är döda eller om du är döda, 
händer något av detta avslutas spelet */
bool Game::gameEnd(){
	bool gameOver = false;
	if ((this->eCanon->getHp() <= 0 && this->eEnemy->getHp() <= 0) || this->pPlayer->getHp() <= 0){
		gameOver = true;
	}
	return gameOver;
}

