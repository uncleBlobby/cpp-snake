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
        printDetails(req);

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

        std::cout << "Response json as string: " << s << std::endl;

        // send string response to client
        res.set_content(s, "application/json");
    });

    svr.Get("/hi", [](const httplib::Request& req, httplib::Response &res) {
        printDetails(req);
        res.set_content("Hello World!", "text/plain");
    });

    svr.Post("/start", [](const httplib::Request& req, httplib::Response &res){
        printDetails(req);
        json parsed = json::parse(req.body);
        json game = parsed["game"];
        json board = parsed["board"];
        json me = parsed["you"];
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

        json parsed = json::parse(req.body);
        json game = parsed["game"];
        json board = parsed["board"];
        json me = parsed["you"];

        RulesetSettings rulesetSettings = RulesetSettings();
        Ruleset ruleset = Ruleset(game["ruleset"]["name"], game["ruleset"]["version"]);
        Game GAME = Game(game["id"], ruleset, game["map"], game["timeout"], game["source"]);
        Board BOARD = Board(board["height"], board["width"]);
        std::cout << "Game ID in game class: " << GAME.getId() << std::endl;
        std::cout << "Board height in board class: " << BOARD.getHeight() << std::endl;
        std::cout << "Board width in board class: " << BOARD.getWidth() << std::endl;

        // AVOID WALLS //
        // get board size


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

        //  Convert json object to string.
        std::string s = jResponse.dump();

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