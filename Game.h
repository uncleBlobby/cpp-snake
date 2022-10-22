#include <string>
#include <vector>

struct Coord {
    unsigned int x;
    unsigned int y;
};

class RulesetSettings {
    private:
        int foodSpawnChance;
        int minimumFood;
        int hazardDamagePerTurn;

        // don't need royale prefix?
        int shrinkEveryNTurns;

        // don't need squad prefix?
        bool allowBodyCollisions;
        bool sharedElimination;
        bool sharedHealth;
        bool sharedLength;
        
    
    public:
        RulesetSettings();

        int getFoodSpawnChance() const;
        int getMinimumFood() const;
        int getHazardDamagePerTurn() const;

        int getShrinkEveryNTurns() const;

        bool getAllowBodyCollision() const;
        bool getSharedElimination() const;
        bool getSharedHealth() const;
        bool getSharedLength() const;
};

class Ruleset {
    private:
        std::string name;
        std::string version;
        RulesetSettings settings;
    
    public:
        Ruleset();
        Ruleset(std::string n, std::string v);

        std::string getName() const;
        std::string getVersion() const;

        void setName(std::string n);
        void setVersion(std::string v);


};

class Game {
    private:
        std::string id;
        Ruleset ruleset;
        std::string map;
        unsigned int timeout;
        std::string source;
    
    public:
        Game();
        Game(std::string i, Ruleset r, std::string m, unsigned int t, std::string s);

        std::string getId() const;
        Ruleset getRuleset() const;
        std::string getMap() const;
        unsigned int getTimeout() const;
        std::string getSource() const;

        void setId(std::string i);
        void setRuleset(Ruleset r);
        void setMap(std::string m);
        void setTimeout(unsigned int t);
        void setSource(std::string s);
};

struct Customizations {
    std::string color;
    std::string head;
    std::string tail;
};

class Snake {
    private:
        std::string id;
        std::string name;
        int health;
        std::vector<Coord> body;
        int latency;
        Coord head;
        unsigned int length;
        std::string shout;
        std::string squad;
        Customizations customizations;
};

class Board {
    private:
        unsigned int height;
        unsigned int width;

        // vector<type> name;

        std::vector<Coord> food;
        std::vector<Coord> hazards;
        std::vector<Snake> snakes;
    
    public:
        Board();
        Board(unsigned int h, unsigned int w);

        unsigned int getWidth() const;
        unsigned int getHeight() const;

};