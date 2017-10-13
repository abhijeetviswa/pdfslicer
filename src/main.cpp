#include "window.hpp"
#include <gtkmm/application.h>

int main()
{
    auto app = Gtk::Application::create();
    Slicer::Window window;

    return app->run(window);
}
