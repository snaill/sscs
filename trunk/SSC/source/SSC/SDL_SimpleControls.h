/*
 * SDL_SimpleControls
 * Copyright (C) 2008 Snaill
 *
    SDL_SimpleControls is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SDL_SimpleControls is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Snaill  <snaill@jeebook.com>
 */

#ifndef SDL_SIMPLECONTROLS_H_INCLUDED
#define SDL_SIMPLECONTROLS_H_INCLUDED

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#ifdef __APPLE__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

#include "SDL_ImageList.h"
#include "SDL_BorderLayout.h"
#include "SDL_Screen.h"
#include "SDL_ProgressBar.h"
#include "SDL_ListBox.h"
#include "SDL_Toolbar.h"
#include "SDL_Theme.h"

#endif // SDL_SIMPLECONTROLS_H_INCLUDED
