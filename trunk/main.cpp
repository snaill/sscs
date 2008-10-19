/*
 * main.cpp
 * Copyright (C) Snaill 2008 <snaill@jeebook.com>
 *
    main.cpp is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    main.c is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SDL_SimpleControls.h"

SDL_Setting * SDL_Setting::m_this = 0;

SDL_Glyph * CreateTestScreen()
{
//    SDL_Container * p = new SDL_Container();
//    p->Add( new SDL_Image("cb.bmp") );
  //  p->Add( new SDL_Text("this is a test!") );
  SDL_Rect  rc;
  rc.x = rc.y = 100;
  rc.w = 100;
  rc.h = 100;
    SDL_Button * pButton = new SDL_Button("cb.bmp");
    pButton->SetBounds( &rc );
    return pButton;
//    return p;
}

int main ( int argc, char** argv )
{
    //
    SDL_Setting * _setting = SDL_Setting::Get();

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Glyph * gWnd = CreateTestScreen();

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if ( gWnd->HandleEvent( &event ) )
                continue;

            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

        // draw bitmap
        gWnd->Draw( screen );

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    gWnd->Release();

    //
    _setting->Release();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
