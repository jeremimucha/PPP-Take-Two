#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
#include <cmath>

using Graph_lib::Axis;
using Graph_lib::Function;
using Graph_lib::Color;
using Graph_lib::Polygon;
using Graph_lib::Rectangle;
using Graph_lib::Line_style;
using std::sin;
namespace GL = Graph_lib;

int main()
{
    Point tl(100,100);

    Simple_window win(tl, 600, 400, "Canvas" );

    Axis xa(Axis::x, Point(20,300), 280, 10, "x axis");
    win.attach(xa);

    Axis ya(Axis::y, Point(20,300), 280, 10, "y axis");
    ya.set_color(Color::cyan);           // choose a color
    ya.label.set_color(Color::dark_red); // choose a color for the text
    win.attach(ya);

    Function sine(sin,0,100,Point(20,150),1000,50,50);    // sine curve
    // plot sin() in the range [0:100) with (0,0) at (20,150)
    // using 1000 points; scale x values *50, scale y values *50
    win.attach(sine);
    sine.set_color(Color::blue);         // we changed our mind about sine's color

    GL::Polygon poly;
    poly.add(Point(300,200));
    poly.add(Point(350,100));
    poly.add(Point(400,200));
    poly.set_color(Color::red);
    poly.set_style(GL::Line_style::dash);
    win.attach(poly);

    GL::Rectangle r(Point(200,200), 100, 50);
    win.attach(r);


    win.wait_for_button();               // Display!
}
