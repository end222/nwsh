#ifndef COLORS_HPP
#define COLORS_HPP

#include <cstring>
#include <string>

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

/*
 * Return a colored string given the colorCode explained above
 */
string paintText(string text, int colorCode);

#endif
