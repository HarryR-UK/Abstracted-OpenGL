#include "Application.h"



int main(int argc, char* argv[])
{

    std::srand(static_cast<unsigned>(time(nullptr)));
    ge::Application app;

    app.run();


}