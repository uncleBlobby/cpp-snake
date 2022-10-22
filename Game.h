#include <string>

class RulesetSettings {
    private:
        int foodSpawnChance;
        int minimumFood;
        int hazardDamagePerTurn;
        struct royale {
            int shrinkEveryNTurns;
        };
        struct squad {
            bool allowBodyCollisions;
            bool sharedElimination;
            bool sharedHealth;
            bool sharedLength;
        };
    
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
