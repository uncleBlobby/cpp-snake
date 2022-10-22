#include "Game.h"
#include <iostream>
#include <vector>

RulesetSettings::RulesetSettings(){
    foodSpawnChance = 0;
    minimumFood = 0;
    hazardDamagePerTurn = 0;
    shrinkEveryNTurns = 0;
    allowBodyCollisions = false;
    sharedElimination = false;
    sharedHealth = false;
    sharedLength = false;
}

Ruleset::Ruleset(){
    name = "";
    version = "";
    settings = RulesetSettings();
}

Ruleset::Ruleset(std::string n, std::string v){
    name = n;
    version = v;
    settings = RulesetSettings();
}

Game::Game(){
    id = "";
    ruleset = Ruleset();
    map = "";
    timeout = 0;
    source = "";
}

Game::Game(std::string i, Ruleset r, std::string m, unsigned int t, std::string s){
    id = i;
    ruleset = r;
    map = m;
    timeout = t;
    source = s;
}

std::string Game::getId() const {
    return id;
}

Ruleset Game::getRuleset() const {
    return ruleset;
}

std::string Game::getMap() const {
    return map;
}

unsigned int Game::getTimeout() const {
    return timeout;
}

std::string Game::getSource() const {
    return source;
}

void Game::setId(std::string i) {
    id = i;
}

void Game::setRuleset(Ruleset r) {
    ruleset = r;
}

void Game::setMap(std::string m) {
    map = m;
}

void Game::setTimeout(unsigned int t) {
    timeout = t;
}

void Game::setSource(std::string s) {
    source = s;
}

Board::Board(){
    height = 0;
    width = 0;
}

Board::Board(unsigned int h, unsigned int w){
    height = h;
    width = w;
}

unsigned int Board::getHeight() const {
    return height;
}

unsigned int Board::getWidth() const {
    return width;
}



Move::Move(){
    direction = "null";
    score = 0;
};

Move::Move(std::string d){
    direction = d;
    score = 0;
};

std::string Move::getDirection() const {
    return direction;
}

int Move::getScore() const {
    return score;
}

void Move::setScore(int s) {
    std::cout << "Direction: " << direction << std::endl;
    std::cout << "Score adjust: " << s << std::endl;
    score += s;
}


ScoredMoves::ScoredMoves() :left("left"), up("up"), right("right"), down("down") {

}

void ScoredMoves::printCurrentScoredMoves() const {
    std::cout << "Left:\t" << left.getScore() << std::endl;
    std::cout << "Up:\t" << up.getScore() << std::endl;
    std::cout << "Right:\t" << right.getScore() << std::endl;
    std::cout << "Down:\t" << down.getScore() << std::endl;
}

Move ScoredMoves::returnHighestScoreMove() const {
    Move bestMove = left;
    if (up.getScore() > bestMove.getScore()){
        bestMove = up;
    }
    if (right.getScore() > bestMove.getScore()){
        bestMove = right;
    }
    if (down.getScore() > bestMove.getScore()){
        bestMove = down;
    }
    return bestMove;
}

Snake::Snake(){

}

Snake::Snake(   std::string i,
                std::string n,
                int hlt,
                int l,
                Coord hd,
                int len) {
    
    id = i;
    name = n;
    health = hlt;
    latency = l;
    head = hd;
    length = len;
    
};

void Snake::setId(std::string i){
    id = i;
}

void Snake::setName(std::string n){
    name = n;
}
void Snake::setHealth(int h){
    health = h;
}
//void Snake::setBody();
//void Snake::setLatency();
void Snake::setHead(Coord h){
    head.x = h.x;
    head.y = h.y;
}
void Snake::setLength(int l){
    length = l;
}

std::string Snake::getId() const {
    return id;
}

std::string Snake::getName() const {
    return name;
}

int Snake::getHealth() const {
    return health;
}
//
//
Coord Snake::getHead() const {
    return head;
}

int Snake::getLength() const {
    return length;
}

void Snake::printBody() const {
    std::cout << "Printing body member of class:" << std::endl;
    for (int i = 0; i < length; i++){
        std::cout << "Body[" << i << "] X: " << body[i].x << ", Y: " << body[i].y << std::endl;
    }
}

Coord Snake::getBodyCoord(int i) const {
    return body[i];
}