#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "classes/Rectangle.h"
#include "classes/Circle.h"
#include "classes/Pixel.h"
#include <eigen3/Eigen/Core>
#include "sdlgui/screen.h"
#include "sdlgui/window.h"
#include "sdlgui/layout.h"
#include "sdlgui/label.h"
#include "sdlgui/checkbox.h"
#include "sdlgui/button.h"
#include "sdlgui/toolbutton.h"
#include "sdlgui/popupbutton.h"
#include "sdlgui/combobox.h"
#include "sdlgui/dropdownbox.h"
#include "sdlgui/progressbar.h"
#include "sdlgui/entypo.h"
#include "sdlgui/messagedialog.h"
#include "sdlgui/textbox.h"
#include "sdlgui/slider.h"
#include "sdlgui/imagepanel.h"
#include "sdlgui/imageview.h"
#include "sdlgui/vscrollpanel.h"
#include "sdlgui/colorwheel.h"
#include "sdlgui/graph.h"
#include "sdlgui/tabwidget.h"
#include "sdlgui/switchbox.h"
#include "sdlgui/formhelper.h"
#include<memory>
using namespace DPDrawing;
using namespace sdlgui;
using std::vector;
using std::string;
using sdlgui::Button;
namespace DPDrawing {
	class Main {
		public:
			int Quit();
			int Init(const int SCREEN_WIDTH = 1280, const int SCREEN_HEIGHT = 720);
			void Update(SDL_Window*& window, SDL_Renderer*& gRenderer);
			int main(int argc, char* argv[]);
	};
}
