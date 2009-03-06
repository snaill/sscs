
/* Simple program:  Fill a colormap with gray and stripe it down the screen */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "SDL.h"
#include "SSC/SDL_SimpleControls.h"
#include "SSC/ImageView/SDL_ImageView.h"
#include "FileView.h"
#include "ImageView.h"

int main(int argc, char *argv[])
{
	// Initialize SDL 
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
		exit(1);
	}

	SDL_WindowManager * screen = SDL_WindowManager::Create( 640, 480, 0, SDL_SWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF );
	screen->SetTheme( new SDL_DefaultTheme( "C:\\windows\\fonts\\simsun.ttc" ) );

	CFileView	fileView;
	CImageView	imageView;

	fileView.SetCaption( "testSSC", "test.bmp" );
	fileView.Show();

	//screen->Add( &fileView );
	//screen->SetActiveWidget( &fileView );
//	screen->Add( imageView );

	/* Wait for a keystroke */
	int			done = 0;
	SDL_Event	event;

	while ( !done && SDL_WaitEvent(&event) ) {
		switch (event.type) {
			/* Any other key quits the application... */
			case SDL_QUIT:
				done = 1;
				break;			
			default:
				screen->HandleEvent( &event, 0 );
				break;
		}
	}
	SDL_Quit();
	return(0);
}
