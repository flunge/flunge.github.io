//standard includes
#include <iostream>
//ZED includes
#include <zed/Camera.hpp>


int main(int argc, char** argv)
{
    sl::zed::Camera* zed = new 
    sl::zed::Camera(sl::zed::HD720);
    // define a struct of parameters for the initialization
    sl::zed::InitParams params;
    std::cout << "Hello World! My ZED works!" << std::endl;
    delete zed;
}
