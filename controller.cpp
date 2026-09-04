#include "controller.hpp"



Controller::~Controller()
{
    // eger actigin pointer'lar varsa burada mutlaka öldürmeyi unutma !
}

void Controller::setup(int s, char *args[])
{
    setup_objects(s,args);
    connect_pointers();
    init_process();
}

int Controller::run(int s, char *args[])
{
    app = std::unique_ptr<QApplication>(new QApplication(s,args));
    window_ptr = std::unique_ptr<Window>(new Window);
    
    window_ptr->setup_ui();
    // window_ptr->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // window_ptr->showFullScreen();
    window_ptr->show();
    int r = app->exec();
    return r;
}

void Controller::setup_objects(int s, char *args[]) 
{                                                
}

void Controller::connect_pointers() 
{
}

void Controller::init_process() 
{

}
