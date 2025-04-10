#include "Window.h"
#include "Controller.h"


int main(int argc, char **argv) {

    Controller controller = Controller();
    Window window = Window(controller);
    return 0;
}
