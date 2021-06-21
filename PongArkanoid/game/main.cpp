// cntrl shift i -> tabulate

#include <SDL.h>
#include <stdio.h>
#include <string>

#include "NetServer.h"
#include "SDLGame.h"

void printArgsError()
{
    printf("Argumentos insuficientes o no validos\n");
    printf("El programa necesita los siguientes argumentos:\n");
    printf("./PongArkanoid client IpAddr port\n");
    printf("./PongArkanoid server port\n\n");
    printf("Ejemplos para ejecutar el programa:\n");
    printf("./PongArkanoid client localhost 8080\n");
    printf("./PongArkanoid server 8080\n");
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printArgsError();
        return 0;
    }
    if (strcmp(argv[1], "client") == 0)
    {
        if(argc < 4){
            printArgsError();
            return 0;
        }
        SDLGame game;
        game.run();
    }
    else if(strcmp(argv[1], "server") == 0){
        if(argc < 3){
            printArgsError();
            return 0;
        }

        printf("Server, start!\n");
        NetServer server("0.0.0.0", argv[2]);

        server.do_messages();
    }
    else{
        printArgsError();
        return 0;
    }

    return 0;
}