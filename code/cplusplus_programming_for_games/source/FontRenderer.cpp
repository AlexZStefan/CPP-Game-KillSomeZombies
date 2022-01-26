#include "FontRenderer.h"

FontRenderer::FontRenderer(SDL_Renderer* sdlRenderer, int _screenWidth, int _screenHeight) {
	renderer = sdlRenderer;
	screenWidth =  _screenWidth;
	screenHeight =_screenHeight;
}

void FontRenderer::init() {

	int init = TTF_Init();
	if (init != 0) {
		std::cout << SDL_GetError() << std::endl;
	}

	font = TTF_OpenFont("assets/bloody.ttf", 120);
	if (font == NULL) {
		std::cout << "TTF COULD NOT BE LOADED " << SDL_GetError() << std::endl;
	}	
}
void FontRenderer::render(std::string text, int x, int y , int w, int h) {
	SDL_Color color = SDL_Color();
	color.r = 120;
	color.g = 0;
	color.b = 60;
	color.a = 255;

	SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textImage);

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(textImage);

}
void FontRenderer::clean() {
	TTF_CloseFont(font);
}

