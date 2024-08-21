// chip8.hpp
#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>
#include <array>
#include <vector>

class Chip8 {
public:
    // Constructor
    Chip8();

    // Method to load ROMs
    void loadROM(const char* filename);

    // Method to emulate cpu-cycle
    void emulateCycle();

    // Method to draw on display
    void drawDisplay();

    // Method to set keys
    void setKey(uint8_t key, bool pressed);

private:
    // registers and memory
    std::array<uint8_t, 16> V;    // register V0 to VF
    uint16_t I;                  // index-register
    uint16_t PC;                 // program counter
    std::array<uint8_t, 4096> memory; // 4KB memory
    std::array<uint8_t, 64 * 32> display; // 64x32 display

    // stack and stack-pointer
    std::array<uint16_t, 16> stack;
    uint8_t sp; // stack pointer

    // timer
    uint8_t delayTimer;
    uint8_t soundTimer;

    // input
    std::array<uint8_t, 16> keys;

    void initialize();
    void executeOpcode(uint16_t opcode);

	//opcode-specific methods
	
	// CLS
	void opcode_00E0();

	//RET
	void opcode_00EE();

	//SYS addr
	void opcode_0nnn();

	//JP addr
	void opcode_1nnn();

	//CALL addr
	void opcode_2nnn();

	//SE Vx, byte
	void opcode_3xkk();

	//SNE Vx, byte
	void opcode_4xkk();
	
	//SE Vx, Vy
	void opcode_5xy0();

	//LD Vx, byte
	void opcode_6xkk();

	//ADD Vx, byte
	void opcode_7xkk();

	//LD Vx, Vy
	void opcode_8xy0();

	//OR Vx, Vy
	void opcode_8xy1();

	//AND Vx, Vy
	void opcode_8xy2();

	//XOR Vx, Vy
	void opcode_8xy3();

	//ADD Vx, Vy
	void opcode_8xy4();

	//SUB Vx, Vy
	void opcode_8xy5();

	//SHR Vx {, Vy}
	void opcode_8xy6();

	//SUBN Vx, Vy
	void opcode_8xy7();
	
	//SHL Vx {, Vy}
	void opcode_8xyE();

	//SNE Vx, Vy
	void opcode_9xy0();

	//LD I, addr
	void opcode_Annn();
	
	//JP V0, addr
	void opcode_Bnnn();
	
	//RND Vx, byte
	void opcode_Cxkk();
	
	//DRW Vx, Vy, nibble
	void opcode_Dxyn();
	
	//SKP Vx
	void opcode_Ex9E();
	
	//SKNP Vx
	void opcode_ExA1();
	
	//LD Vx, DT
	void opcode_Fx07();
	
	//LD Vx, K
	void opcode_Fx0A();
	
	//LD DT, Vx
	void opcode_Fx15();
	
	//LD ST, Vx
	void opcode_Fx18();
	
	//ADD I, Vx
	void opcode_Fx1E();
	
	//LD F, Vx
	void opcode_Fx29();
	
	//LD B, Vx
	void opcode_Fx33();
	
	//LD [I], Vx
	void opcode_Fx55();
	
	//LD Vx, [I]
	void opcode_Fx65();
};

#endif // CHIP8_HPP