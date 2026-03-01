#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

static std::string path;

void setPath(const std::string& newPath)
{
        path = newPath;
}

std::string& getPath()
{
        return path;
}

#endif // SETTINGS_H
