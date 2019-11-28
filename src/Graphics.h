#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Observer.h"
#include "window.h"

class Graphics : public Observer {
	Xwindow theDisplay;
	int boardSize;
public:
    // try to set this up similar to textdisplay?
    Graphics(int n);
    ~Graphics() = default;
    void notify(Subject &whoNotified) override;
};

#endif