#include "colors.hpp"
#include <cstring>

using namespace std;

/*
 * Color Code
 * 0: Black
 * 1: Red
 * 2: Green
 * 3: Yellow
 * 4: Blue
 * 5: Magenta
 * 6: Cyan
 * 7: Light Gray
 * 8: Dark Gray
 * 9: Light Red
 * 10: Light Green
 * 11: Light Yellow
 * 12: Light Blue
 * 13: Light Magenta
 * 14: Light Cyan
 * 15: White
 */

int colors[16] = {30,31,32,33,34,35,36,37,90,91,92,93,94,95,96,97};

string paintText(string text, int colorCode)
{
	return "\033[" + to_string(colors[colorCode]) + "m" + text + "\033[0m";
}
