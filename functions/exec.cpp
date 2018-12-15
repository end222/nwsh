/*
 * nwsh
 * By end222
 * File: exec.cpp
 */

#include <memory>

#include "exec.hpp"

using namespace std;

string exec(const char* cmd) {
	array<char, 128> buffer;
	string result;
	shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);	
	if (!pipe) throw runtime_error("popen() failed!");
	while (!feof(pipe.get())) 
	{
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr) result += buffer.data();
	}
	return result;
}

