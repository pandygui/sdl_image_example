#include "SDL.h"
#include "SDL_image.h"

int main(int argc, char* argv[])
{
    SDL_Surface *screen = NULL;
	SDL_Surface *image = NULL;
	const SDL_VideoInfo *videoInfo = NULL;
	int width = 0;
	int height = 0;

	/*-----------------------------------------------------------------*/

	if (argc != 2)
	{
		fprintf(stderr, "single argument ... name of image to display\n");
		return 1;
	}

	/*-----------------------------------------------------------------*/

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL_Init failed - %s\n", SDL_GetError());
		return 1;
	}

	/*-----------------------------------------------------------------*/

	videoInfo = SDL_GetVideoInfo();

	if (videoInfo == 0)
	{
		fprintf(stderr, "SDL_GetVideoInfo failed - %s\n", SDL_GetError());
    	SDL_Quit();
	 	return 1;
	}

	/*-----------------------------------------------------------------*/

	image = IMG_Load(argv[1]);

	if (!image)
	{
		fprintf(stderr, "IMG_Load failed - %s\n", IMG_GetError());
	}

	/*-----------------------------------------------------------------*/

	if (image->w < videoInfo->current_w)
	{
		width = image->w;
	}
	else
	{
		width = videoInfo->current_w;
	}

	if (image->h < videoInfo->current_h)
	{
		height = image->h;
	}
	else
	{
		height = videoInfo->current_h;
	}

	/*-----------------------------------------------------------------*/

    screen = SDL_SetVideoMode(width,
							  height,
							  videoInfo->vfmt->BitsPerPixel,
							  SDL_HWSURFACE);

    if (!screen)
    {
		fprintf(stderr, "SetVideoMode failed - %s\n", SDL_GetError());
		SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

	/*-----------------------------------------------------------------*/

	SDL_BlitSurface(image, 0, screen, 0);
	
    SDL_Delay(5000);

	SDL_FreeSurface(image);

    SDL_Quit();

    return 0;
}
