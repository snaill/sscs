
/* Simple program:  Fill a colormap with gray and stripe it down the screen */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "SDL.h"
#include "SSC/SDL_SimpleControls.h"
#include "SSC/ImageView/SDL_ImageView.h"
#include "View1.h"

int main(int argc, char *argv[])
{
	// Initialize SDL 
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
		exit(1);
	}

	SDL_WindowManager * screen = SDL_WindowManager::Create( 640, 480, 0, SDL_SWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF );
	screen->SetTheme( new SDL_DefaultTheme( "C:\\windows\\fonts\\simsun.ttc" ) );
	screen->SetDegree( 0 );

	CView1	mainView;

	mainView.SetTitle( "testSSC" );
	mainView.Show();

	SDL_Quit();
	return(0);
}
