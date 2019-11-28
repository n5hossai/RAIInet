#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Observer.h"
#include "window.h"

class Graphics : public Observer {
	Xwindow theDisplay;
	int boardSize;
public:
	
}
class GraphicsDisplay : public Observer<Info, State> {
    
    int tileWidth;
public:
    // try to set this up similar to textdisplay?
    GraphicsDisplay(int n);
    ~GraphicsDisplay() = default;
    void notify(Subject<Info, State> &whoNotified) override;
};