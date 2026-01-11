#include <exception>
#include <iostream>
#include <ostream>

#include "example01.h"

int main()
{
    Example01 app;

    app.Init();

    app.InitResources();

    int result = 0;
    try
    {
        result = app.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    app.Shutdown();

    return result;
}
