BUILDDIR		:= build
TARGET			:= eBikeGTK

SRC				:= main.cpp
SRC				+= Server/server.cpp
CPPFLAGS		+= -std=c++17 -O0
CPPFLAGS		+= `pkg-config gtkmm-4.0 --cflags`
LDFLAGS			:= `pkg-config gtkmm-4.0 --libs`

include BuildServices/Makefile.common

install_deps:
	sudo apt update
	sudo apt install libgtkmm-4.0-dev --fix-missing