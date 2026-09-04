#include <iostream>
#include "controller.hpp"

int main (int s,char * args[])
{
    Controller controller;
    controller.setup(s,args);
    return controller.run(s,args);
}
