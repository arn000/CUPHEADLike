#pragma once
#include <string>
#include <SDL.h>
#include <vector>
#include "timer.h"
class Window {
	friend class Player;
	friend class Pos;
	friend class Npc;
public:

	Window(const std::string &title, int width, int height);
	~Window();
	void pollEvents(SDL_Event& event);
	void clear() const;
	inline bool isClosed() const { return _closed; }
	SDL_Renderer* getrenderer();
	Timer* mTimer;
	void Update();
private:

	bool init();
	bool animated = false;
	int frames = 0;
	int speed = 100;
private:

	std::string _title;
	int _width = 800;
	int _height = 600;
	bool _closed = false;
	SDL_Window* _window = nullptr;
public:

	static SDL_Renderer* renderer;
};