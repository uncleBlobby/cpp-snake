#include "httplib.h"
#include "json.hpp"

#include <stdio.h>
#include <ctime>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

#include "Game.h"

using json = nlohmann::json;

httplib::Server svr;

void printDetails(const httplib::Request& req);

int main() {
    printf("Hello, cpp-snake!\n");

    svr.Get("/", [](const httplib::Request& req, httplib::Response &res) {
        //printDetails(req);

        // HERE ARE SOME CHANGES IN MAIN....


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
            "color": "#DFFF00",
            "head": "shades",
            "tail": "bolt",
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

        time_t turnStart = time(NULL);
        auto turn_start = Clock::now();
        
        json parsedReq = json::parse(req.body);
        json g = parsedReq["game"];
        json b = parsedReq["board"];
        json m = parsedReq["you"];

        //std::cout << "Me object in request: " << m << std::endl;
        //std::cout << "My body: " << m["body"] << std::endl;
        //std::cout << "My length: " << m["length"] << std::endl;

        

        RulesetSettings rulesetSettings = RulesetSettings();
        Ruleset ruleset = Ruleset(g["ruleset"]["name"], g["ruleset"]["version"]);
        Game game = Game(g["id"], ruleset, g["map"], g["timeout"], g["source"]);
        Board board = Board(b["height"], b["width"]);
        //std::cout << "Game ID in game class: " << game.getId() << std::endl;
        //std::cout << "Board height in board class: " << board.getHeight() << std::endl;
        //std::cout << "Board width in board class: " << board.getWidth() << std::endl;

        ScoredMoves scoredMoves;

        Coord myHead;
        myHead.x = m["head"]["x"];
        myHead.y = m["head"]["y"];

        Snake me;
        me.setHead(myHead);
        me.setLength(m["length"]);

        for (int i = 0; i < m["length"]; i++){
            //std::cout << "My body [" << i << "]: " << m["body"][i] << std::endl;
            me.body.push_back((struct Coord){.x=m["body"][i]["x"], .y=m["body"][i]["y"]});
        }

        //std::cout << "Board food: " << b["food"] << std::endl;
        std::cout << "Board food length: " << b["food"].size() << std::endl;

        for (int i = 0; i < b["food"].size(); i++){
            board.food.push_back((struct Coord){.x=b["food"][i]["x"], .y=b["food"][i]["y"]});
            std::cout << "Board food[" << i << "] X: " << board.food[i].x << " Y: " << board.food[i].y << std::endl; 
        }

        //  TODO: figure out this food stuff -- currently seems to print even when the food value is null
        /*
        for(int i = 0; i < board.getHeight() * board.getWidth(); i++){
            if ((b["food"][i]["x"] < board.getWidth()) && (b["food"][i]["y"] < board.getHeight())){
                std::cout << "Food at [" << i << "]: " << b["food"][i] << std::endl;
                std::cout << "Food: X:" << b["food"][i]["x"] << " Y:" << b["food"][i]["y"] << std::endl;
                //board.food.push_back((struct Coord){.x=b["food"][i]["x"], .y=b["food"][i]["y"]});

                //std::cout << "Food inside board class: X:" << board.food[i].x << " Y:" << board.food[i].y << std::endl;
            }
            
        }
        */

        //std::cout << "Food inside board class: " << board.food << std::endl;
        

        //std::cout << "My head position x: " << me.getHead().x << std::endl;
        //std::cout << "My head position y: " << me.getHead().y << std::endl;

        //me.printBody();
        

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

        // AVOID NECK //
        // need to implement body position array //

        if (me.getHead().x + 1 == me.getBodyCoord(1).x){
            scoredMoves.right.setScore(-100);
        };

        if (me.getHead().x - 1 == me.getBodyCoord(1).x){
            scoredMoves.left.setScore(-100);
        };

        if (me.getHead().y + 1 == me.getBodyCoord(1).y){
            scoredMoves.up.setScore(-100);
        };

        if (me.getHead().y - 1 == me.getBodyCoord(1).y){
            scoredMoves.down.setScore(-100);
        };

        // AVOID OWN BODY //

        for (int i = 1; i < me.getLength(); i++){
            if ((me.getHead().x + 1 == me.getBodyCoord(i).x) && (me.getHead().y == me.getBodyCoord(i).y)){
                scoredMoves.right.setScore(-100);
            }
            if ((me.getHead().x - 1 == me.getBodyCoord(i).x) && (me.getHead().y == me.getBodyCoord(i).y)){
                scoredMoves.left.setScore(-100);
            }
            if ((me.getHead().x == me.getBodyCoord(i).x) && (me.getHead().y + 1 == me.getBodyCoord(i).y)){
                scoredMoves.up.setScore(-100);
            }
            if ((me.getHead().x == me.getBodyCoord(i).x) && (me.getHead().y - 1 == me.getBodyCoord(i).y)){
                scoredMoves.down.setScore(-100);
            }
        }


        //scoredMoves.printCurrentScoredMoves();

        Move best = scoredMoves.returnHighestScoreMove();

        /*
        SAMPLE RESPONSE 
        {
            "move": "up",
            "shout": "Moving up!" // optional
        }
        */
        //  Build out valid json response.
        json responseData;
        responseData["move"] = best.getDirection();

        //  Convert json object to string.
        std::string s = responseData.dump();

        //std::cout << "Response json as string: " << s << std::endl;

        time_t turnEnd = time(NULL);
        auto turn_end = Clock::now();

        time_t turnTimeElapsed = turnEnd - turnStart;

        auto turn_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(turn_end - turn_start);

        //std::cout << "Time elapsed to move: " << turnTimeElapsed << std::endl;
        std::cout << "Time elapsed to move (chrono): " << turn_duration.count() << "ns" << std::endl;
        //std::cout << "Time elapsed to move (chrono): " << turn_duration.count() / 1000000000 << "s" << std::endl;

        // send string response to client
        res.set_content(s, "application/json");
    });


    svr.Post("/end", [](const httplib::Request& req, httplib::Response &res) {
        json parsedReq = json::parse(req.body);
        json g = parsedReq["game"];
        json b = parsedReq["board"];
        json m = parsedReq["you"];

        std::cout << "Game ended.\n" << "Details:\n";

        std::cout << "Game ID: "<< g["id"] << std::endl;
        std::cout << "Data: " << parsedReq << std::endl;
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