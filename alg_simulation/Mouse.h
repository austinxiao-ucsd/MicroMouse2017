#define NORTH 0;
#define SOUTH 1;
#define WEST 2;
#define EAST 3;

class Mouse{
	//direction of Mouse

	public:
		int direction; //initial direction is north

		//the current position of Mouse, should be identical to the Cell'x and y
		int mouse_x;
		int mouse_y;
		
		Mouse ();
		
		void set_direction(int dir);
		
		int get_direction();

};
