#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <iostream>

bool collision ( SDL_Rect one , SDL_Rect two ) {

	if ( (one.y + one.h) <= two.y ) return false ;
	if ( one.y >= ( two.y + two.h ) ) return false ;
	if ( ( one.x + one.w ) <= two.x ) return false ;
	if ( one.x >= ( two.x + two.w ) ) return false ;

	return true ;

}

int main ( int argc , char** argv ) {

	SDL_Init( SDL_INIT_EVERYTHING ) ;

	SDL_Surface *screen = NULL ;
	SDL_Surface *ball = NULL ;
	SDL_Surface *enemy = NULL ;
	SDL_Event event ;
	SDL_Rect enemy_rect , ball_rect ;

	ball_rect.x = 320 ;
	ball_rect.y = 160 ;

	enemy_rect.x = 0 ;
	enemy_rect.y = 160 ;

	screen = SDL_SetVideoMode( 640 , 320 , 32 , SDL_SWSURFACE ) ;
	SDL_WM_SetCaption("Avoid the rocket!" , NULL ) ;
	ball = SDL_LoadBMP( "dot.bmp" ) ;
	enemy = SDL_LoadBMP( "rocket.bmp" ) ;

	SDL_BlitSurface( ball , NULL , screen , &ball_rect ) ;
	SDL_BlitSurface( enemy , NULL , screen , &enemy_rect ) ;
	SDL_Flip( screen ) ;
	SDL_LockSurface( screen ) ;

	for ( ;; ) {

		SDL_PollEvent( &event ) ;

		if ( event.type == SDL_QUIT ) break ;

		if ( event.type = SDL_KEYDOWN ) {

			switch( event.key.keysym.sym ) {

				case SDLK_UP : ball_rect.y-- ; break ;
				case SDLK_DOWN : ball_rect.y++ ; break ;
				case SDLK_RIGHT : ball_rect.x++ ; break ;
				case SDLK_LEFT : ball_rect.x-- ; break ;

			}

		}

		if ( ball_rect.x >= 640 ) ball_rect.x = 0 ;
		if ( ball_rect.y >= 320 ) ball_rect.y = 0 ;

		enemy_rect.x++ ;

		if ( enemy_rect.x >= 640 ) enemy_rect.x = 0 ;

		if ( collision( enemy_rect , ball_rect ) ) break ;


		SDL_UnlockSurface( screen ) ;
		SDL_BlitSurface( ball , NULL , screen , &ball_rect ) ;
		SDL_BlitSurface( enemy , NULL , screen , &enemy_rect ) ;
		SDL_Flip( screen ) ;
		SDL_LockSurface( screen ) ;
	
	}

	SDL_FreeSurface( ball ) ;
	SDL_FreeSurface( enemy ) ;
	SDL_Quit() ;

	return 0 ;

}


