/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author ...
  **/
#include "Application.h"
int main(void)
{
    Application* app = new Application();
    app->initialization();

    app->run();

 }