#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {
	d = XOpenDisplay(NULL);
	if (d == NULL) {
		cerr << "Cannot open display" << endl;
		exit(1);
	}
	
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(
		d, RootWindow(d, s), 10, 10, width, height, 
		1, BlackPixel(d, s), WhitePixel(d, s)
	);

	XSelectInput(d, w, ExposureMask | KeyPressMask);

	Pixmap pix = XCreatePixmap(
		d, w, width, height, 
		DefaultDepth(d, DefaultScreen(d))
	);

	gc = XCreateGC(d, pix, 0, 0);

	// Set up colours.
	XColor xcolour;
	Colormap cmap;

	const size_t numColours = 6;
	char color_vals[numColours][10] = {
		"white", "black", "red", 
		"green", "blue", "yellow"
	};

	cmap = DefaultColormap(d, DefaultScreen(d));
	
	for(unsigned int i = 0; i < numColours; ++i) {
		XParseColor(d, cmap, color_vals[i], &xcolour);
		XAllocColor(d, cmap, &xcolour);
		colours[i] = xcolour.pixel;
	}

	XSetForeground(d, gc, colours[Black]);

	 // Make window non-resizeable.
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);

	// map window and flush
	XMapRaised(d, w);
	XFlush(d);
	
	// wait 1 second for setup
	sleep(1);
}

Xwindow::~Xwindow() {
	XFreeGC(d, gc);
	XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}
void Xwindow::drawRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);
	XDrawRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

void Xwindow::drawString(int x, int y,  string msg, int colour) {
	// WILL COME BACK TO CHANGE FONT LATER
	// /* this pointer will hold the returned font structure. */
	// XFontStruct* font_info;

	// /* try to load the given font. */
	// //char* font_name = "*-helvetica-*-12-*";
	// font_info = XLoadQueryFont(d, font_name);
	// if (!font_info) {
	//     fprintf(stderr, "XLoadQueryFont: failed loading font '%s'\n", font_name);
	// }
	// XSetFont(d, gc, font_info->fid);
	XSetForeground(d, gc, colours[colour]);
	XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
	XFlush(d);
}

