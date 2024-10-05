#include <iostream>
#include "window.h"
#include "controller.h"


int main(int argc, char **argv) {

    Controller controller = Controller();
    Window window = Window(controller);
    return 0;
}
