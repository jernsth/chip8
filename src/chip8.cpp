// chip8.cpp
#include "chip8.hpp"
#include <fstream>
#include <iostream>

Chip8::Chip8() {
	initialize();
}

void Chip8::initialize() {
	//initialize registers, memory and timer
	PC=0x200; //programm starts at 0x200
	I=0;
	sp=0;
	V.fill(0);
	display.fill(0);
	stack.fill(0);
	delayTimer=0;
	soundTimer=0;
	keys.fill(0);
}

void Chip8::loadROM(const char* filename) {
	std::ifstream file(filename, std::ios::binary);
	if (file) {
		file.read(reinterpret_cast<char*>(memory.data()+0x200), memory.size()-0x200);
	} else {
		std::cerr << "Failed to open ROM file.\n";
	}
}

void Chip8::emulateCycle() {
	//fetch opcode
	uint16_t opcode = memory[PC] << 8 | memory[PC + 1];
	PC +=2;

	//decode and execute opcode
	executeOpcode(opcode);
}

void Chip8::executeOpcode(uint16_t opcode) {
	switch (opcode & 0xF000) {
		case 0x0000:
			break;
		
		default:
			std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
			break;
	}
}

void Chip8::drawDisplay() {

}

void Chip8::setKey(uint8_t key, bool pressed) {
	
}
