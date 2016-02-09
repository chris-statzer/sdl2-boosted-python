
#include <boost/python.hpp>

#include <iostream>
#include <stdlib.h>

#include <SDL.h>
#include "SDL_image.h"


enum KEYS {
  KEY_ESC = SDL_SCANCODE_ESCAPE,
  KEY_UP = SDL_SCANCODE_UP,
  KEY_DOWN = SDL_SCANCODE_DOWN,
  KEY_LEFT = SDL_SCANCODE_LEFT,
  KEY_RIGHT = SDL_SCANCODE_RIGHT
 };


class KeyboardEvent {
public:
  int scancode;
  std::string keycode;
};


class SDL2Application {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *sheet;
  bool running;
  boost::python::list keyboardEvents;

public:
  void init(int width, int height) {
    std::cout << "SDL2Application::init" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
  		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
  	}

    window = SDL_CreateWindow("Foo", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
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
    running = true;
  }

  void clear(void) {
    SDL_RenderClear(renderer);
  }

  void flip(void) {
    SDL_RenderPresent(renderer);
  }

  void quit(void) {
    running = false;
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
			if (e.type == SDL_QUIT)
				quit();
      if (e.type == SDL_KEYDOWN)
        onKeydown(e.key.keysym.scancode);
		}
  }

  boost::python::list pollKeys(void) {
    boost::python::list listToReturn = keyboardEvents;
    keyboardEvents = boost::python::list();
    return listToReturn;
  }

  bool isRunning(void) {
    return running;
  }

  void onKeydown(SDL_Scancode k) {
    KeyboardEvent key;
    key.scancode = k;
    key.keycode = SDL_GetScancodeName(k);
    keyboardEvents.append(key);
  }
};



BOOST_PYTHON_MODULE(sdlapp)
{
    using namespace boost::python;
    enum_<KEYS>("keys")
    .value("KEY_ESC", KEY_ESC)
    .value("KEY_UP", KEY_UP)
    .value("KEY_DOWN", KEY_DOWN)
    .value("KEY_LEFT", KEY_LEFT)
    .value("KEY_RIGHT", KEY_RIGHT)
        ;

    class_<KeyboardEvent>("KeyboardEvent")
        .add_property("scancode", &KeyboardEvent::scancode)
        .add_property("keycode", &KeyboardEvent::keycode);

    class_<SDL2Application>("SDL2Application")
        .def("init", &SDL2Application::init)
        .def("draw_char", &SDL2Application::drawChar)
        .def("flip", &SDL2Application::flip)
        .def("clear", &SDL2Application::clear)
        .def("update", &SDL2Application::update)
        .def("quit", &SDL2Application::quit)
        .def("is_running", &SDL2Application::isRunning)
        .def("poll_keys", &SDL2Application::pollKeys)
    ;
}
