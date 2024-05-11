#include "Application.h"

int main()
{
    Application* application = new Application();
    application->Setup();
    application->Run();
    return 0;
}