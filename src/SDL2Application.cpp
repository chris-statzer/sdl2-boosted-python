
#include <boost/python.hpp>

#include <iostream>
#include <stdlib.h>

#include <SDL.h>
#include "SDL_image.h"


class SDL2Application {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *sheet;
  bool running;
public:
  void init(int width, int height) {
    running = true;
    std::cout << "SDL2Application::init" << std::endl;
  	if (SDL_Init(SDL_INIT_VIDEO) != 0){
  		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
  	}

    window = SDL_CreateWindow("Foo", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr){
    	std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    	SDL_Quit();
    }
    renderer = SDL_CreateRenderer(window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
    	SDL_DestroyWindow(window);
    	std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    	SDL_Quit();
    }
    sheet = loadTexture("../assets/alpha-sheet.png");
  }

  void clear(void) {
    SDL_RenderClear(renderer);
  }

  void flip(void) {
    SDL_RenderPresent(renderer);
  }

  void quit(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  SDL_Texture* loadTexture(const std::string &file){
      std::cout << "SDL2Application::loadTexture " << file << std::endl;
      SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
      return texture;
  }

  void drawChar(int x, int y, int c) {
    SDL_Rect src;
    src.x = (c%16) * 16;
    src.y = (c/16) * 16;
    src.w = 16;
    src.h = 16;

    SDL_Rect dest;
    dest.x = x * 16;
    dest.y = y * 16;
    dest.w = 16;
    dest.h = 16;
    SDL_RenderCopy(renderer, sheet, &src, &dest);
  }

  void update(void) {
    if (!running)
      quit();
    SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				std::cout << "SDL_QUIT" << std::endl;
				running = false;
			}
		}
  }

  bool isRunning(void) {
    return running;
  }
};


BOOST_PYTHON_MODULE(sdlapp)
{
    using namespace boost::python;
    class_<SDL2Application>("SDL2Application")
        .def("init", &SDL2Application::init)
        .def("draw_char", &SDL2Application::drawChar)
        .def("flip", &SDL2Application::flip)
        .def("clear", &SDL2Application::clear)
        .def("update", &SDL2Application::update)
        .def("quit", &SDL2Application::quit)
        .def("is_running", &SDL2Application::isRunning)
    ;
}
