#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <random>

const int SCREEN_WIDTH  = 100*5;
const int SCREEN_HEIGHT = 100*5;
const int ARRAY_SIZE    = 100;

void draw_state(SDL_Renderer* gRenderer,
			    std::vector<int>& arr,
			    size_t red,
				size_t blue)
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gRenderer);

	for( size_t i = 0; i < ARRAY_SIZE; ++i )
	{
		if( i == red )
		{
			SDL_SetRenderDrawColor( gRenderer, 255, 0, 0 , 255 );
		}
		else if (i == blue)
		{
			SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 255 );
		}
		else
		{
			SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
		}
		SDL_RenderDrawLine( gRenderer, i, SCREEN_HEIGHT - 1, i, arr[ i ]);
	}
	SDL_RenderPresent(gRenderer);

	SDL_Delay(15);
	return;
}


void insertion_sort(SDL_Window*       gWindow,
					SDL_Renderer*     gRenderer,
					std::vector<int>& arr)
{
	for( size_t i = 0; i < arr.size(); ++i )
	{
		int smallest          = arr[ i ];
		size_t smallest_index = i;

		for( size_t j = i; j < arr.size(); ++j )
		{
			if( arr[ j ] < smallest )
			{
				smallest       = arr[ j ];
				smallest_index = j;
			}
		}
		std::swap( arr[ i ], arr[ smallest_index ] );

		draw_state( gRenderer, arr, i, smallest_index );
	}

	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		draw_state ( gRenderer, arr, i, -1 );
	}

	return;
}


int main( int argc, char* args[] )
{
	SDL_Window* gWindow         = NULL;
	SDL_Renderer* gRenderer     = NULL;
	SDL_CreateWindowAndRenderer( SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gWindow, &gRenderer );
	SDL_RenderSetScale( gRenderer, 5, 5 );
	
	bool running = true;
	SDL_Event e;
	SDL_FlushEvent( SDL_KEYDOWN );

	std::random_device rd;
	std::uniform_int_distribution<> d( 1, ARRAY_SIZE );
	std::vector<int> arr( ARRAY_SIZE );
	for ( int i = 0; i < ARRAY_SIZE; ++i )
	{
		arr[ i ] = d( rd );
	}

	while( running )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				running = false;
			}
			if( e.type != SDL_KEYDOWN ) continue;
			else
			{
				// printf("%d\n", e.type);
				switch( e.key.keysym.sym )
				{
					case SDLK_1:
						// Insertion Sort
						printf( "Insertion Sort \n" );
						insertion_sort( gWindow, gRenderer, arr );
						SDL_FlushEvent( SDL_TEXTINPUT );
						running = false;
						break;

					case SDLK_2:
						// Selection Sort
						// SelectionSort();
						running = false;
						break;

					case SDLK_3:
						// Bubble Sort
						// BubbleSort();
						running = false;
						break;

					case SDLK_4:
						// Merge Sort
						// MergeSort();
						running = false;
						break;

					case SDLK_5:
						// Quick Sort
						// QuickSort();
						running = false;
						break;

					default:
						// do nothing
						break;
				} // switch
			} // else
		} // while event
	} // while running

	return 0;
}
