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