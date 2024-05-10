#include "woe_server.hpp"

int main()
{
    spk::Application app = spk::Application("World Of Electron - Server", spk::Vector2UInt(800, 640), spk::Application::Mode::Multithread);

    return (app.run());
}