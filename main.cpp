#include "httplib.h"
#include "json.hpp"
#include <stdio.h>

#include "Game.h"

using json = nlohmann::json;

httplib::Server svr;

void printDetails(const httplib::Request& req);

int main() {
    printf("Hello, cpp-snake!\n");

    svr.Get("/", [](const httplib::Request& req, httplib::Response &res) {
        //printDetails(req);

        /*
        SAMPLE RESPONSE 
        {
            "apiversion": "1",
            "author": "MyUsername",
            "color": "#888888",
            "head": "default",
            "tail": "default",
            "version": "0.0.1-beta"
        }
        */
        //  Build out valid json response.
        json jResponse = json::parse(R"(
            {"apiversion": "1",
            "author": "uncleBlobby",
            "color": "#292929",
            "head": "default",
            "tail": "default",
            "version": "0.0.1-alpha"}
        )");

        //  Convert json object to string.
        std::string s = jResponse.dump();

        //std::cout << "Response json as string: " << s << std::endl;

        // send string response to client
        res.set_content(s, "application/json");
    });

    svr.Get("/hi", [](const httplib::Request& req, httplib::Response &res) {
        printDetails(req);
        res.set_content("Hello World!", "text/plain");
    });

    svr.Post("/start", [](const httplib::Request& req, httplib::Response &res){
        //printDetails(req);
        
        json parsedReq = json::parse(req.body);
        json g = parsedReq["game"];
        json b = parsedReq["board"];
        json m = parsedReq["you"];
        
        RulesetSettings rulesetSettings = RulesetSettings();
        Ruleset ruleset = Ruleset(g["ruleset"]["name"], g["ruleset"]["version"]);
        Game game = Game(g["id"], ruleset, g["map"], g["timeout"], g["source"]);

        std::cout << "New game started!\nGame ID: " << game.getId() << std::endl;
        
        /*
        std::cout << "JSON game variable: " << game << std::endl;
        std::cout << std::endl;
        std::cout << "JSON board variable: " << board << std::endl;
        std::cout << std::endl;
        std::cout << "JSON you variable: " << me << std::endl;
        std::cout << std::endl;
        std::cout << "Game ID: " << game["id"] << std::endl;
        */
        res.set_content("ok", "application/json");
    });

    svr.Get("/move", [](const httplib::Request& req, httplib::Response &res) {
        printDetails(req);
        res.set_content("Hello, Battlesnake!", "text/plain");
    });

    svr.Post("/move", [](const httplib::Request& req, httplib::Response &res) {

        json parsedReq = json::parse(req.body);
        json g = parsedReq["game"];
        json b = parsedReq["board"];
        json m = parsedReq["you"];

        RulesetSettings rulesetSettings = RulesetSettings();
        Ruleset ruleset = Ruleset(g["ruleset"]["name"], g["ruleset"]["version"]);
        Game game = Game(g["id"], ruleset, g["map"], g["timeout"], g["source"]);
        Board board = Board(b["height"], b["width"]);
        std::cout << "Game ID in game class: " << game.getId() << std::endl;
        std::cout << "Board height in board class: " << board.getHeight() << std::endl;
        std::cout << "Board width in board class: " << board.getWidth() << std::endl;

        ScoredMoves scoredMoves;

        Coord myHead;
        myHead.x = m["head"]["x"];
        myHead.y = m["head"]["y"];

        Snake me;
        me.setHead(myHead);

        std::cout << "My head position x: " << me.getHead().x << std::endl;
        std::cout << "My head position y: " << me.getHead().y << std::endl;
        

        // AVOID WALLS //
        // get board size
        // board.getHeight(), board.getWidth()

        if (me.getHead().x + 1 >= board.getWidth()){
            scoredMoves.right.setScore(-50);
        };

        if (me.getHead().x == 0){
            scoredMoves.left.setScore(-50);
        };

        if (me.getHead().y + 1 >= board.getHeight()){
            scoredMoves.up.setScore(-50);
        };

        if (me.getHead().y == 0){
            scoredMoves.down.setScore(-50);
        };


        scoredMoves.printCurrentScoredMoves();

        Move best = scoredMoves.returnHighestScoreMove();

        /*
        SAMPLE RESPONSE 
        {
            "move": "up",
            "shout": "Moving up!" // optional
        }
        */
        //  Build out valid json response.
        json jResponse = json::parse(R"(
            {"move": "up"}
        )");

        json responseData;
        responseData["move"] = best.getDirection();

        //  Convert json object to string.
        std::string s = responseData.dump();

        std::cout << "Response json as string: " << s << std::endl;

        // send string response to client
        res.set_content(s, "application/json");
    });

    

    svr.listen("0.0.0.0", 8080);

    return 0;
}

void printDetails(const httplib::Request& req){
        std::cout << "Received request on: " << req.path << std::endl;
        printf("Req details:\n");
        
        //  Old fashioned C style printf statements can't parse the vars...
        //  printf("Req method %s: \n", req.method);
        
        std::cout << "Req method: " << req.method << std::endl;
        std::cout << "Req path: " << req.path << std::endl;
        httplib::Headers header = req.headers;
        
        //std::cout << "Req headers: " << req.headers << std::endl;

        
        
        
        //  printf("Req body %s: \n", req.body);
        std::cout << "Req body: " << req.body << std::endl;

        // for server

        std::cout << "For server: " << std::endl;
        std::cout << "Req version: " << req.version << std::endl;
        std::cout << "Req target: " << req.target << std::endl;
        //std::cout << "Req params: " << req.params. << std:: endl;

        
        //printf("Req remote address %s: \n", req.remote_addr);
        std::cout << "Req remote address: " << req.remote_addr << std::endl;
        
}