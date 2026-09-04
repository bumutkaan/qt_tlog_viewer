#include <iostream>
#include <memory>
#include <cstdint>

#include <window.hpp>


class Controller
{
public:
    Controller() = default;
    ~Controller();

    // setup dosyası yazılımın kurulumunu kasteder
    void setup(int s,char * args[]);

    // run dosyası main'de ana dongunun donecegı fonksiyondur
    int run(int s,char * args[]);

private:
    // objeler
    // ------
    std::unique_ptr<QApplication> app;
    std::unique_ptr<Window> window_ptr;

    // kurucular
    // ---------
    void setup_objects(int s, char *args[]);
    void connect_pointers();
    void init_process();

};

