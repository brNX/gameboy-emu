#include "joystick.h"
#include "types.h"
#include "Z80.h"
#include <SDL/SDL.h>
#include <cstdio>

Joystick::Joystick()
{

    //TODO: SDL start

    if (SDL_Init(SDL_INIT_JOYSTICK) <0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    }


    printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    printf("The names of the joysticks are:\n");

    for(int i=0; i < SDL_NumJoysticks(); i++ )
    {
        printf("    %s\n", SDL_JoystickName(i));
    }


}

Joystick::~Joystick()
{
SDL_Quit();
}


void Joystick::poll()
{
    //uint8 temp = gbcpu.mem->IO[0];
    //temp ^= 0xFF;

}
