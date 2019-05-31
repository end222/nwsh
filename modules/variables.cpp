#include <string>
#include <cstring>
#include <iostream>

using namespace std;

/*
 * There are 2 types of variables:
 *
 * $variable: will be stored in memory and are lost whenever the shell
 * session is closed
 *
 * ?variable: will be stored in disk inside the ~/.config/nwsh folder.
 * They are available in different nwsh session and can also be used
 * to connect 2 nwsh sessions.
 * They are stored using a tree scheme, like a filesystem. Then, a leaf can
 * be accesed by ?notleafnode/leaf
 */

void readVar(char* variable)
{

}
