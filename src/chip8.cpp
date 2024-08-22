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

//Clear display
void Chip8::opcode_00E0() {
	display.fill(0);
	PC +=2;
}

//Return from subroutine
void Chip8::opcode_00EE() {
	if (sp>0) {
		--sp; // Decrement stack pointer
		PC = stack[sp]; //Set program counter to top of the stack
		PC += 2; //Go to next instruction
	} else { 
		std::cerr << "Stack underflow error.\n";
	}
}

//Set program counter to given address
void Chip8::opcode_1nnn(uint16_t addr) {
	PC = addr; 
}

//Call subroutine
void Chip8::opcode_2nnn(uint16_t addr) {
	if(sp < stack.size()) {
		stack[sp] = PC; //Save current program counter
		++sp; //Increase stack pointer 
		PC = addr; //Call subroutine at address
	} else {
		std::cerr << "Stack overflow error.\n";
	}
}

//Skip next instruction if register Vx equals kk
void Chip8::opcode_3xkk(uint8_t Vx, uint8_t kk) {
	if(V[Vx] == kk) {
		PC += 2;
	}
	PC += 2;
}

//Skip next instruction if register Vx not equal to kk
void Chip8::opcode_4xkk(uint8_t Vx, uint8_t kk) {
	if(V[Vx] != kk) {
		PC += 2;
	}
	PC += 2;
}

//Skip next instruction, if register Vx equals to register Vy
void Chip8::opcode_5xy0(uint8_t Vx, uint8_t Vy) {
	if(V[Vx] == V[Vy]) {
		PC += 2;
	}
	PC += 2;
}

//Store value in register
void Chip8::opcode_6xkk(uint8_t Vx, uint8_t kk) {
	V[Vx] = kk;
	PC += 2;
}

//Add value to register
void Chip8::opcode_7xkk(uint8_t Vx, uint8_t kk) {
	V[Vx] += kk;
	PC += 2;
}

//Store value from register Vy in register Vx
void Chip8::opcode_8xy0(uint8_t Vx, uint8_t Vy) {
	V[Vx] = V[Vy];
	PC += 2;
}

//Perform bitwise OR on register Vx and Vy
void Chip8::opcode_8xy1(uint8_t Vx, uint8_t Vy) {
	V[Vx] |= V[Vy];
	PC += 2;
}

//Perform bitwise AND on register Vx and Vy
void Chip8::opcode_8xy2(uint8_t Vx, uint8_t Vy) {
	V[Vx] &= V[Vy];
	PC += 2;
}

//Perform bitwise XOR on register Vx and Vy
void Chip8::opcode_8xy2(uint8_t Vx, uint8_t Vy) {
	V[Vx] ^= V[Vy];
	PC += 2;
}

//Add Vy to Vx, set VF Byte for overflow
void Chip8::opcode_8xy4(uint8_t Vx, uint8_t Vy) {
	uint16_t sum = V[Vx] + V[Vy];
    V[15] = (sum > 255) ? 1 : 0;
    V[Vx] = sum & 0xFF;
    PC += 2;
}

//Subtract Vy from Vx and store potential negative overflow
void Chip8::opcode_8xy5(uint8_t Vx, uint8_t Vy) {
	V[15] = (V[Vx] > V[Vy]) ? 1 : 0;
	V[Vx] -= V[Vy];
	PC += 2;
}

//If the least significant bit is set, then set VF-Flag and shift register right
void Chip8::opcode_8xy6(uint8_t Vx) {
	V[15] = ((V[Vx] & 0x01) == 1) ? 1 : 0;
	V[Vx] >>= 1;
	PC += 2;
}

//Subtract Vx from Vy and store potential negative overflow
void Chip8::opcode_8xy7(uint8_t Vx, uint8_t Vy) {
	V[15] = (V[Vy] > V[Vx]) ? 1 : 0;
	V[Vx] = V[Vy] - V[Vx];
	PC += 2;
}

//If the most significant bit is set, then set VF-Flag and shift register left
void Chip8::opcode_8xyE(uint8_t Vx) {
	uint8_t msb = (V[Vx] >> 7) & 0x01;
	V[15] = (msb == 1) ? 1 : 0;
	V[Vx] <<= 1;
	PC += 2;
}

void Chip8::drawDisplay() {

}

void Chip8::setKey(uint8_t key, bool pressed) {
	
}
