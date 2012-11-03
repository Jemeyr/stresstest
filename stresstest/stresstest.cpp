#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <time.h>
#include <iostream>

//giraffe count
#define NUM 30

//frames to average it over
#define FRAMES 1000


int main (int argc, char* args[])
{

	SDL_Surface* jraf 	=	NULL;
	SDL_Surface* screen 	=	NULL;
	SDL_Surface* loadImage 	=	NULL;


	SDL_Init(SDL_INIT_EVERYTHING);

	//Set up screen 
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE ); 
	SDL_WM_SetCaption( "GIRAFFE", NULL);


	//Load image 
	loadImage = SDL_LoadBMP( "jraf.bmp" );

	//set to display format so we don't convert every blit
	jraf = SDL_DisplayFormat(loadImage);
	
	//make magenta transparent
        Uint32 colorkey = SDL_MapRGB( jraf->format, 0xFF, 0, 0xFF );
	
	//remove magenta here
	SDL_SetColorKey( jraf, SDL_SRCCOLORKEY, colorkey );



	//background is black
        Uint32 bgcolor = SDL_MapRGB( screen->format, 0, 0, 0 );
	

	//places for things
	SDL_Rect things[NUM];
		
	//initialize places
	for(int i = 0; i < NUM; i++)
	{
		things[i].x = (i % 10) * 32;		//offsets images a bit
		things[i].y = (i / 10) * 24;		
	}

	//timers
	clock_t begin,end;
	
	//stats stuff
	double max, avg, delta;
	max = 0.0;
	avg = 0.0;	

	//Commenting every line
	for(int i = 0; i < FRAMES; i++)
	{
		//get start time
		begin = clock();

		//clear last frame (optional here because we're not moving anything)
		SDL_FillRect(screen, NULL, bgcolor);

		//still commenting every line
		for(int j = 0; j < NUM; j++)
		{
		 	//Apply image to screen 
			SDL_BlitSurface( jraf, NULL, screen, &(things[j]) ); 
		}
		
		//get end time
		end = clock();

		//convert to ms
		delta = ((end - begin) * 1000) / CLOCKS_PER_SEC;

		//add to average
		avg += delta;

		//reset max
		if(delta > max)
		{
			max = delta;
		}

		//Update Screen 
		SDL_Flip( screen ); 

	}
	
	//make average average and print
	avg /= FRAMES;
	std::cout << "Avg " << avg << "\nmax " << max << "\n";

 	//Free the loaded image 
	SDL_FreeSurface( jraf ); 

	//Quit SDL 
	SDL_Quit(); 
	return 0; 
}



