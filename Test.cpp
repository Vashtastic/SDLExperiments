#include "SDL2/SDL.h"
#include <memory>
#include <iostream>
#include <stdio.h>
#include <vector>

#define TRACE_FUNCTION() std::cout << __PRETTY_FUNCTION__ << std::endl;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string RESOURCE_NAME = "/OwO.bmp";
const std::vector<std::string> randomResources = {"awef3.bmp", "awef2.bmp", "Test.bmp"};

using RawWindow = SDL_Window;
using RawRenderer = SDL_Renderer;
using RawSurface = SDL_Surface;
using RawTexture = SDL_Texture;

enum : uint8_t
{
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_TOTAL
};

struct WindowAttrbutes
{
    std::string windowName;
    int xPos;
    int yPos;
    int width;
    int height;
    uint32_t bit_mask;
};

struct SurfaceAttributes
{
    int index;
    uint32_t bit_mask;
};

class WindowWrapper
{
public:
    WindowWrapper() = delete;

    WindowWrapper(WindowAttrbutes windowAttribs)
    {
        m_Window = SDL_CreateWindow(windowAttribs.windowName.c_str(), windowAttribs.xPos, windowAttribs.yPos,
                                  windowAttribs.width, windowAttribs.height, windowAttribs.bit_mask);
    }

    WindowWrapper(RawWindow* window) /*Should be just a window*/
    {
        m_Window = window;
    }
    ~WindowWrapper()
    {
        SDL_DestroyWindow(m_Window);
    }
    RawWindow* getWindow()
    {
        return m_Window;
    }
private:
    RawWindow* m_Window {};
};

class RendererWrapper
{
public:
    RendererWrapper(RawWindow* window, SurfaceAttributes attribs)
    {
        rawRenderer = SDL_CreateRenderer(window, attribs.index, attribs.bit_mask);
        if (!rawRenderer)
        {

        }
    }
    ~RendererWrapper()
    {
        SDL_DestroyRenderer(rawRenderer);
    }
private:
    RawRenderer* rawRenderer{};
};

class SurfaceWrapper
{
public:
    SurfaceWrapper(RawSurface* rawSurface)
    {
        surface = rawSurface;
    }

    ~SurfaceWrapper()
    {

    }
private:
    RawSurface* surface;
};

class TextureWrapper
{
public:
    TextureWrapper()
    {

    }

    ~TextureWrapper()
    {

    }
private:
    RawTexture* texture;
};

RawSurface* loadSurface(const std::string& path)
{
    SDL_Surface* surfaceToLoad = SDL_LoadBMP(path.c_str()); //i think this should allocate to heap, lets check
    return surfaceToLoad;
}

void loadSurfacePool(std::vector<RawSurface*>& screenPool)
{
    TRACE_FUNCTION();
    for (auto& resource : randomResources)
    {
        auto* surfaceToLoad = loadSurface(resource);
        if( surfaceToLoad == NULL )
        {
            printf( "Unable to load image %s! SDL Error: %s\n", resource.c_str(), SDL_GetError() );
        }
        screenPool.push_back(surfaceToLoad);
        printf("BMP File %s Loaded! \n", resource.c_str());
    }
}

int main(int argc, char* args[])
{
    RawSurface* screenSurface = NULL;
    RawSurface screenSurfaces[KEY_PRESS_TOTAL] {}; //[OwO] Pool of screenSurfaces.
    std::vector<RawSurface*> screenSurfacePool {};

    //Ganon pala yung implementation ng linked list haha, iz kewl

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) //initialize various subsystems in SDL depending on the flags in the partial_sort()meter
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        loadSurfacePool(screenSurfacePool);
        WindowAttrbutes windowAttribs{"りりか", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN};

        printf("Initializing Window");
        std::unique_ptr<WindowWrapper> awef;
        awef = std::make_unique<WindowWrapper>(windowAttribs);
        WindowWrapper window(windowAttribs);

        auto* RawWindow = window.getWindow();

        screenSurface = SDL_GetWindowSurface(RawWindow);
        RawSurface* surfaceWithImage = SDL_LoadBMP("Test.bmp");
        SDL_BlitSurface( surfaceWithImage, NULL, screenSurface, NULL );
        if(!RawWindow)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            bool quit = false;
            SDL_Event event {};

            while (!quit)
            {
                while (SDL_PollEvent(&event) != 0)
                {
                    printf("\n[OwO] quit value is: %d", quit);
                    if (SDL_QUIT == event.type)
                    {
                        printf("\n[OwO] Quit event has been polled");
                        quit = true;
                    }

                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            printf("\n[OwO] Up pressed");
                            break;
                        case SDLK_DOWN:
                            surfaceWithImage = screenSurfacePool[2];
                            printf("\n[OwO] Down pressed");
                            break;
                        case SDLK_LEFT:
                            printf("\n[OwO] Changing the screen ");
                            surfaceWithImage = screenSurfacePool[0];
                            break;
                        case SDLK_RIGHT:
                            printf("\n[OwO] Changing the screen  again ");
                            surfaceWithImage = screenSurfacePool[1];
                            printf("\n'[OwO] Right pressed");
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            printf("\n[OwO] escape pressed");
                            break;
                        default:
                            printf("\n[OwO] event logged");
                            break;
                    }
                }

                if (!surfaceWithImage)
                {
                    printf("\nUnable to load image %s", SDL_GetError());
                    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFA, 0xDF, 0xEF));
                }

                RawSurface* optimizedSurface {};
                optimizedSurface = SDL_ConvertSurface(surfaceWithImage, screenSurface->format, 0);
                // SDL_FreeSurface(surfaceWithImage);
                // SDL_BlitSurface(optimizedSurface, NULL, screenSurface, NULL); //it can blit it over our current screen hahaha
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled( optimizedSurface, NULL, screenSurface, &stretchRect );
                SDL_UpdateWindowSurface(RawWindow);
            }

            printf("\n[OwO]Thanks for using!");
            SDL_Delay(5000);
        }
    }
    return 0;
}
