#include <stdio.h>
#include <SDL.h>

void fill(unsigned *pixels, int pitch, int width, int height, unsigned color) {
	int x, y;
	for (y = 0; y < height; y++) 
		for (x = 0; x < width; x++) 
			pixels[y*pitch+x] = color;
}

const char *winTitle = "RedFlicker";
int winWidth = 800, winHeight = 600;

int main() {
	SDL_Window *window = SDL_CreateWindow(winTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	if (!window) {
		fprintf(stderr, "main: %s\n", SDL_GetError());
		return -1;
	}

	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		fprintf(stderr, "main: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Texture *tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!tex) {
		fprintf(stderr, "main: %s\n", SDL_GetError());
		return -1;
	}

	for (;;) {
		SDL_Event event;
		SDL_Event quitEvent = { type: SDL_QUIT };
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				return 0;
			case SDL_KEYUP:
				SDL_PushEvent(&quitEvent);
				break;
			}
		}

		void *pixels;
		int pitch;
		if (SDL_LockTexture(tex, NULL, &pixels, &pitch) != 0) {
			fprintf(stderr, "main: %s\n", SDL_GetError());
			return -1;
		}

		fill(pixels, pitch / 4, width, height, 0xFF0000);	// Red
		fill(pixels, pitch / 4, width, height, 0x000080);	// Medium blue
		SDL_UnlockTexture(tex);

		if (SDL_RenderClear(renderer) != 0) {
			fprintf(stderr, "main: %s\n", SDL_GetError());
			return -1;
		}

		if (SDL_RenderCopy(renderer, tex, NULL, NULL) != 0) {
			fprintf(stderr, "main: %s\n", SDL_GetError());
			return -1;
		}

		SDL_RenderPresent(renderer);
	}

	return 0;
}
