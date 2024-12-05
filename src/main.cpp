#include "woe.hpp"

int main()
{
    spk::GraphicalApplication app;

    spk::SafePointer<spk::Window> win = app.createWindow(L"WorldOfElectron", spk::Geometry2D(0, 0, { 600, 600 }));
    win->setUpdateRate(0);

    return app.run();
}
