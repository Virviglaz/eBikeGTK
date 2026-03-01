#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>

static std::string path;

void setPath(const char *newPath)
{
        path = newPath;
	std::cout << "Using custom path: " << path << std::endl;
}

std::string& getPath()
{
        return path;
}

#endif // SETTINGS_H
