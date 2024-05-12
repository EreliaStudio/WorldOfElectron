#include "woe.hpp"

int main()
{
    spk::Application app = spk::Application("World Of Electron", spk::Vector2UInt(800, 640), spk::Application::Mode::Multithread);

	MainWidget mainWidget(nullptr);
	mainWidget.setGeometry(0, app.size());
	mainWidget.activate();

    return (app.run());
}