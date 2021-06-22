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
    logic_ = new Logic(this);
    
    bool quit = false;
    //Event handler
    SDL_Event e;

    client->run();

    //Set default current surface
    while (!quit)
    {
        Uint32 startTime = getTime();
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( gRenderer );

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
                break;
            }

            if(playerId != -1){
                //User presses a key
                if (e.type == SDL_KEYDOWN)
                {
                    //Select surfaces based on key press
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:{
                            quit = true;
                            break;
                        }
                        case SDLK_UP:{
                            logic_->movePaddle(playerId, true);
                            //MSGPlayerInfo msg(client->getName(), client->getMatchId());
                            //client->send_Message(&msg);
                            
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            logic_->movePaddle(playerId, false);
                        }
                    }
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    logic_->shoot(playerId, x, y);
                }
            }
        }
        if(playerId != -1){
            logic_->Update();
        }
        
        SDL_RenderPresent(gRenderer);

        Uint32 frameTime = getTime() - startTime;
        if (frameTime < 10)
            SDL_Delay(10 - frameTime);
    }

    //Free resources and close SDL
    close();
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
            gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

void SDLGame::manageMsg(GameMessage *msg)
{
    switch (msg->type)
    {
    case GameMessage::MessageType::UPDATE_PLAYER:
        break;
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

    case GameMessage::MessageType::SHOOT:{
        MSGShoot* m = static_cast<MSGShoot*>(msg);
        logic_->spawnBullet(m->pos, m->dir, m->bulletId);
        break;
    }
    case GameMessage::MessageType::MOVE_PADDLE:{
        MSGMovePaddle* m = static_cast<MSGMovePaddle*>(msg);
        logic_->setPaddlePos(m->playerId, m->pos);
        break;
    }
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