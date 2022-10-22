#include "httplib.h"
#include <stdio.h>

httplib::Server svr;

void printDetails(const httplib::Request& req);

int main() {
    printf("Hello, cpp-snake!\n");

    svr.Get("/", [](const httplib::Request& req, httplib::Response &res) {
        printDetails(req);
        res.set_content("Hello, c++ webserver!", "text/plain");
    });

    svr.Get("/hi", [](const httplib::Request& req, httplib::Response &res) {
        printDetails(req);
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/move", [](const httplib::Request& req, httplib::Response &res) {
        printDetails(req);
        res.set_content("Hello, Battlesnake!", "text/plain");
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