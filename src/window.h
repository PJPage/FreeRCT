/* $Id$ */

/*
 * This file is part of FreeRCT.
 * FreeRCT is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * FreeRCT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with FreeRCT. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file window.h %Window handling data structures. */

#ifndef WINDOW_H
#define WINDOW_H

#include "geometry.h"

/**
 * %Window base class, extremely simple (just a viewport).
 * @todo Make it a real window with widgets, title bar, and stuff.
 */
class Window {
public:
	Window(int x, int y, uint w, uint h);
	virtual ~Window();

	int x;       ///< X position of top-left corner.
	int y;       ///< Y position of top-left corner.
	uint width;  ///< Width of the window.
	uint height; ///< Height of the window.

	Window *higher; ///< Window above this window (managed by #WindowManager).
	Window *lower;  ///< Window below this window (managed by #WindowManager).

	virtual void OnDraw();
};

/**
 * Class for displaying parts of the world.
 * @todo Make it a widget?
 */
class Viewport : public Window {
public:
	Viewport(int x, int y, uint w, uint h);

	virtual void OnDraw();

	FORCEINLINE Point ComputeXY(int32 x, int32 y, int32 z)
	{
		Point p;
		p.x = ((y - x) * this->tile_width / 2) >> 8;
		p.y = ((x + y) * this->tile_width / 4 - z * this->tile_height) >> 8;
		return p;
	}

	int32 xview; ///< X position of the center point of the viewport.
	int32 yview; ///< Y position of the center point of the viewport.
	int32 zview; ///< Z position of the center point of the viewport.

	uint16 tile_width;  ///< Width of a tile.
	uint16 tile_height; ///< Height of a tile.
};

class VideoSystem;

void SetVideo(VideoSystem *vid);
VideoSystem *GetVideo();

void UpdateWindows();

#endif