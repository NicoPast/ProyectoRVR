#include "SDLGame.h"
#include "Color.h"
#include "NetClient.h"
#include "GameMessage.h"

SDLGame::SDLGame(const char *s, const char *p, const char *n = "Anonymous", int w = SCREEN_WIDTH, int h = SCREEN_HEIGHT) : screenW(w), screenH(h)
{
    if (!init())
    {
        throw("Failed to initialize!\n");
    }
    client = new NetClient(this, s, p, n);
    if (!client)
    {
        throw("Failed to initialize Client!\n");
    }
}

SDLGame::SDLGame() : SDLGame("localhost", "8080")
{
}

SDLGame::~SDLGame()
{
    delete client;
}

void SDLGame::run()
{
    bool quit = false;
    //Event handler
    SDL_Event e;

    client->run();

    //Set default current surface
    gCurrentColor = &gKeyPressColors[KEY_PRESS_SURFACE_DEFAULT];
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            //User presses a key
            else if (e.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:{
                    gCurrentColor = &gKeyPressColors[KEY_PRESS_SURFACE_UP];
                    MSGPlayerInfo msg(client->getName(), client->getMatchId());
                    client->send_Message(&msg);
                    break;
                }

                case SDLK_DOWN:
                    gCurrentColor = &gKeyPressColors[KEY_PRESS_SURFACE_DOWN];
                    break;

                case SDLK_LEFT:
                    gCurrentColor = &gKeyPressColors[KEY_PRESS_SURFACE_LEFT];
                    break;

                case SDLK_RIGHT:
                    gCurrentColor = &gKeyPressColors[KEY_PRESS_SURFACE_RIGHT];
                    break;

                case SDLK_ESCAPE:
                    quit = true;
                    break;

                default:
                    gCurrentColor = &gKeyPressColors[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }

        //Fill the surface white
        SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, gCurrentColor->r, gCurrentColor->g, gCurrentColor->b));

        //Update the surface
        SDL_UpdateWindowSurface(gWindow);
    }

    //Free resources and close SDL
    close();
}

bool SDLGame::loadColors()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressColors[KEY_PRESS_SURFACE_DEFAULT] = Color();

    //Load up surface
    gKeyPressColors[KEY_PRESS_SURFACE_UP] = Color(0xFF, 0, 0);

    //Load down surface
    gKeyPressColors[KEY_PRESS_SURFACE_DOWN] = Color(0, 0xFF, 0);

    //Load left surface
    gKeyPressColors[KEY_PRESS_SURFACE_LEFT] = Color(0, 0, 0xFF);

    //Load right surface
    gKeyPressColors[KEY_PRESS_SURFACE_RIGHT] = Color(0xFF, 0xFF, 0xFF);

    return success;
}

bool SDLGame::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);

            if (!loadColors())
            {
                printf("Couldn't create the colors for the diferent keys\n");
                success = false;
            }
        }
    }

    return success;
}

void SDLGame::manageMsg(GameMessage *msg)
{
    switch (msg->type)
    {
    case GameMessage::MessageType::PLAYER_INFO:
        std::cout << "PlayerName: " << static_cast<MSGPlayerInfo *>(msg)->name;
        break;

    case GameMessage::MessageType::SET_MATCH:
        client->setMatchId(msg->matchId);
        playerId = static_cast<MSGSetMatch*>(msg)->playerId;
        std::cout << "Match [" << client->getMatchId() << "] joined with id: " << playerId << "\n"; 
        break;

    case GameMessage::MessageType::PLAYER_WAIT:
        client->setMatchId(-1);
        playerId = -1;
        std::cout << "Player waiting for companion\n";
        break;

    default:
        break;
    }
}

void SDLGame::close()
{
    client->logout();

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}