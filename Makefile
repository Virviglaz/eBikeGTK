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
	sudo apt install libgtkmm-4.0-dev --fix-missing# Download and install the Raspberry Pi cross-compilation toolchain if not already present
install_gcc4_raspberryPiZero: /opt/cross-pi-gcc/bin/arm-linux-gnueabihf-gcc

# Download and install the Raspberry Pi cross-compilation toolchain if not already present
/opt/cross-pi-gcc/bin/arm-linux-gnueabihf-gcc:
	wget https://github.com/Pro/raspi-toolchain/releases/latest/download/raspi-toolchain.tar.gz
	sudo tar xfz raspi-toolchain.tar.gz --strip-components=1 -C /opt
	rm raspi-toolchain.tar.gz

# Build for Raspberry Pi Zero
raspberryPiZero: install_gcc4_raspberryPiZero
	@make all CROSS_COMPILE=/opt/cross-pi-gcc/bin/arm-linux-gnueabihf-