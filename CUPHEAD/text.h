#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
class Player;
class Coin;
class Text {
public:

	Text(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
	~Text();
	void display(int x, int y, SDL_Renderer * renderer) const;
	int scores(Coin* coin, Player* player);
	static SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
private:

	SDL_Renderer* renderer;
	const std::string& font_path;
	int font_size;
	const std::string& message_text;
	const SDL_Color& color;
	SDL_Texture* _text_texture = nullptr;
	mutable SDL_Rect _text_rect;
};