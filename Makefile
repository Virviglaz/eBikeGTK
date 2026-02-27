BUILDDIR		?= build
TARGET			:= eBikeGTK
GTKMM_VERSION	?= 4

ifeq ($(GTKMM_VERSION), 4)
    DEF			+= GTKMM4
	INSTALL_CMD	:= libgtkmm-4.0-dev
else
	INSTALL_CMD	:= libgtkmm-3.0-dev
endif

SRC				:= main.cpp
SRC				+= Server/server.cpp
CPPFLAGS		+= -std=c++17 -O0
CPPFLAGS		+= `pkg-config gtkmm-$(GTKMM_VERSION).0 --cflags`
LDFLAGS			:= `pkg-config gtkmm-$(GTKMM_VERSION).0 --libs`

install_deps:
	sudo apt update
	sudo apt install $(INSTALL_CMD) --fix-missing

include BuildServices/Makefile.common