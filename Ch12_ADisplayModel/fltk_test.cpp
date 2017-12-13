#include <iostream>
#include "Simple_window.h"
#include "Graph.h"

namespace GL = Graph_lib;

int main()
try{
    Point tl(100, 100);
    Simple_window win(tl, 600,400, "Canvas");
    win.wait_for_button();
}
catch( std::exception& e ){
    std::cerr << e.what() << std::endl;
    return 1;
}
catch( ... ){
    std::cerr << "Unknown exception" << std::endl;
    return 2;
}
