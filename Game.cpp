#include "Game.h"

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