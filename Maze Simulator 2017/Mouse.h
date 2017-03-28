#ifndef __MOUSE_H__
#define __MOUSE_H__
class Mouse {
	//direction of Mouse
	int north;
	int west;
	int south;
	int east;

	//the current position of Mouse, should be identical to the Cell'x and y
	int mouse_x;
	int mouse_y;

};
#endif