#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct color{
    int r;
    int g;
    int b;

    color(int r, int g, int b) : r(r), g(g), b(b) {
        
    };

    color() : color(0,0,0){
        
    };
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//The images that correspond to a keypress
color* gKeyPressColors[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
color* gCurrentColor = NULL;

bool loadColors(){
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressColors[ KEY_PRESS_SURFACE_DEFAULT ] = new color();
    if( gKeyPressColors[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default color!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressColors[ KEY_PRESS_SURFACE_UP ] = new color(0xFF,0,0);
    if( gKeyPressColors[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up color!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressColors[ KEY_PRESS_SURFACE_DOWN ] = new color(0,0xFF,0);
    if( gKeyPressColors[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down color!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressColors[ KEY_PRESS_SURFACE_LEFT ] = new color(0,0,0xFF);
    if( gKeyPressColors[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left color!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressColors[ KEY_PRESS_SURFACE_RIGHT ] = new color(0xFF,0xFF,0xFF);;
    if( gKeyPressColors[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right color!\n" );
        success = false;
    }

    return success;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );

            if(!loadColors()){
                printf("Couldn't create the colors for the diferent keys\n");
                success = false;
            }
        }
    }

    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char **argv){
    if(!init()){
        printf( "Failed to initialize!\n" );
        return -1;
    }
    else
    {
        bool quit = false;
        //Event handler
        SDL_Event e;

        //Set default current surface
        gCurrentColor = gKeyPressColors[ KEY_PRESS_SURFACE_DEFAULT ];
        while(!quit){
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                //User presses a key
                else if( e.type == SDL_KEYDOWN )
                {
                    //Select surfaces based on key press
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_UP:
                        gCurrentColor = gKeyPressColors[ KEY_PRESS_SURFACE_UP ];
                        break;

                        case SDLK_DOWN:
                        gCurrentColor = gKeyPressColors[ KEY_PRESS_SURFACE_DOWN ];
                        break;

                        case SDLK_LEFT:
                        gCurrentColor = gKeyPressColors[ KEY_PRESS_SURFACE_LEFT ];
                        break;

                        case SDLK_RIGHT:
                        gCurrentColor = gKeyPressColors[ KEY_PRESS_SURFACE_RIGHT ];
                        break;

                        case SDLK_ESCAPE:
                        quit = true;
                        break;

                        default:
                        gCurrentColor = gKeyPressColors[ KEY_PRESS_SURFACE_DEFAULT ];
                        break;
                    }
                }

            }

            //Fill the surface white
            SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, gCurrentColor->r, gCurrentColor->g, gCurrentColor->b) );
        
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );
        }

        //Free resources and close SDL
        close();

        return 0;
    }
}