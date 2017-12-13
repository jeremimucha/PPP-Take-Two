
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

// using namespace Graph_lib;
namespace GL = Graph_lib;
//------------------------------------------------------------------------------

struct Simple_window : GL::Window {
    Simple_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop

private:
    GL::Button next_button;     // the "next" button
    bool button_pushed;     // implementation detail

    static void cb_next(GL::Address, GL::Address); // callback for next_button
    void next();            // action to be done when next_button is pressed

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
