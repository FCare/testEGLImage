#pragma once

#include "assert.h" 
#include "os_types.h"
#include <string>
#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "EGL/egl.h"

class CAVWindow
{
	int m_cx, m_cy, m_PosX, m_PosY;
	std::wstring m_windowName;
	Colormap m_colormap;
	XVisualInfo *m_visual;
    Window m_window;
    Display* m_display;

	static Bool wait_for_map(Display *display, XEvent *event, char *windowPointer) 
    {
    	return (event->type == MapNotify && event->xmap.window == (*((Window*)windowPointer)));
    }
public:
	CAVWindow()
	{
		m_display = NULL;
	}
	~CAVWindow()
	{
		ChiudiFinestra();
	}
	void CreaFinestra(int windowWidth, int windowHeight, const std::wstring &wName, int posx, int posy)
	{
		XSetWindowAttributes windowAttributes;
		XSizeHints sizeHints;
		XEvent event;
		XVisualInfo visualInfoTemplate;

		unsigned long mask;
		long screen;

		int visualID, numberOfVisuals;

		m_display = XOpenDisplay(NULL);
		if (!m_display)
			throw "Couldn't XOpenDisplay";


		Window root = DefaultRootWindow( m_display );

		windowAttributes.event_mask = StructureNotifyMask | ExposureMask;

		m_window = XCreateWindow(m_display, root, 0, 0, windowWidth, windowHeight,
			0, CopyFromParent, InputOutput, CopyFromParent, CopyFromParent, &windowAttributes);
		sizeHints.flags = USPosition;
		sizeHints.x = 10;
		sizeHints.y = 10;

		XMapWindow(m_display, m_window);
		XIfEvent(m_display, &event, wait_for_map, (char*)(&m_window));
		XSetWMColormapWindows(m_display, m_window, &m_window, 1);
		XFlush(m_display);

		XSelectInput(m_display, m_window, KeyPressMask | ExposureMask | EnterWindowMask
			| LeaveWindowMask | PointerMotionMask | VisibilityChangeMask | ButtonPressMask
			| ButtonReleaseMask | StructureNotifyMask);
	}

	void ChiudiFinestra()
	{
		if (m_display)
		{
			XDestroyWindow(m_display, m_window);
			XFreeColormap(m_display, m_colormap);
			XFree(m_visual);
			XCloseDisplay(m_display);
			m_display = NULL;
		}
	}
	HWND GethWnd()
	{
		return (unsigned long)m_window;
	}

	Display* GetXDisplayPtr()
	{
		return m_display;
	}
};



