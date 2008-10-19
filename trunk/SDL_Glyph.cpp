/*
 * SDL_Glyph.cpp
 * Copyright (C) Snaill 2008 <snaill@jeebook.com>
 *
    SDL_Glyph.cpp is free software: you can redistribute it and/or modify it
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

#include "SDL_Glyph.h"

void SDL_Glyph::DrawPixel(SDL_Surface *screen, int x, int y, Uint32 color )
{
    switch (screen->format->BytesPerPixel)
    {
        case 1: // Assuming 8-bpp
        {
            Uint8 *bufp;
            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *bufp = color;
        }
        break;
        case 2: // Probably 15-bpp or 16-bpp
        {
            Uint16 *bufp;
            bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
            *bufp = color;
        }
        break;
        case 3: // Slow 24-bpp mode, usually not used
        {
            Uint8 *bufp;
            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
            if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
            {
                bufp[0] = color;
                bufp[1] = color >> 8;
                bufp[2] = color >> 16;
            } else {
                bufp[2] = color;
                bufp[1] = color >> 8;
                bufp[0] = color >> 16;
            }
        }
        break;
        case 4: // Probably 32-bpp
        {
            Uint32 *bufp;
            bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
}

void SDL_Glyph::DrawLine( SDL_Surface *screen, int x0, int y0, int x1, int y1, Uint32 color )
{
    int dx,         // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2,
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping

    // compute horizontal and vertical deltas
    dx = x1-x0;
    dy = y1-y0;

    // test which direction the line is going in i.e. slope angle
    if (dx>=0)
    {
        x_inc = 1;
    } // end if line is moving right
    else
    {
        x_inc = -1;
        dx    = -dx;  // need absolute value
    } // end else moving left

    // test y component of slope
    if (dy>=0)
    {
        y_inc = 1;
    } // end if line is moving down
    else
    {
        y_inc = -1;
        dy    = -dy;  // need absolute value
    } // end else moving up

    // compute (dx,dy) * 2
    dx2 = dx << 1;
    dy2 = dy << 1;

    // now based on which delta is greater we can draw the line
    int x = x0;
    int y = y0;
    if (dx > dy)
    {
        // initialize error term
        error = dy2 - dx;

        // draw the line
        for (index=0; index <= dx; index++)
        {
            // set the pixel
            DrawPixel( screen, x, y, color );

            // test if error has overflowed
            if (error >= 0)
            {
                error-=dx2;

                // move to next line
                y+=y_inc;

            } // end if error overflowed

            // adjust the error term
            error+=dy2;

            x+=x_inc;
       } // end for

    } // end if |slope| <= 1
    else
    {
        // initialize error term
        error = dx2 - dy;

        // draw the line
        for (index=0; index <= dy; index++)
        {
            // set the pixel
            DrawPixel( screen, x, y, color );

            // test if error overflowed
            if (error >= 0)
            {
                error-=dy2;

                // move to next line
                x+=x_inc;

            } // end if error overflowed

            // adjust the error term
            error+=dx2;

            y+=y_inc;
        } // end for

    } // end else |slope| > 1
}

void SDL_Glyph::DrawRgn( SDL_Surface *screen, int* xs, int* ys, int count, Uint32 color, bool bClose )
{
    for ( int i = 1; i < count; i++ )
    {
        DrawLine( screen, xs[i-1], ys[i-1], xs[i], ys[i], color );
    }

    if ( bClose )
    {
        DrawLine( screen, xs[count - 1], ys[ count - 1 ], xs[0], ys[0], color );
    }
}

void SDL_Glyph::DrawRect( SDL_Surface *screen, SDL_Rect rect, Uint32 color )
{
    int x[4];
    int y[4];

    x[0] = rect.x; y[0] = rect.y;
    x[1] = rect.x; y[1] = rect.y + rect.h - 1;
    x[2] = rect.x + rect.w - 1;  y[2] = rect.y + rect.h - 1;
    x[3] = rect.x + rect.w - 1; y[3] = rect.y;

    DrawRgn( screen, x, y, 4, color, true );
}

void SDL_Glyph::Draw3DRect( SDL_Surface *screen, SDL_Rect rect, Uint32 clrTopLeft, Uint32 clrBottomRight )
{
    int x[5];
    int y[5];

    x[0] = rect.x + rect.w - 1; y[0] = rect.y;
    x[1] = rect.x; y[1] = rect.y;
    x[2] = rect.x; y[2] = rect.y + rect.h - 1;
    x[3] = rect.x + rect.w - 1;  y[3] = rect.y + rect.h - 1;
    x[4] = rect.x + rect.w - 1; y[4] = rect.y;

    DrawRgn( screen, x, y, 3, clrTopLeft, false );
    DrawRgn( screen, &x[2], &y[2], 3, clrBottomRight, false);
}

