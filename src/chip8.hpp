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

	//JP addr
	void opcode_1nnn(uint16_t addr);

	//CALL addr
	void opcode_2nnn(uint16_t addr);

	//SE Vx, byte
	void opcode_3xkk(uint8_t Vx, uint8_t kk);

	//SNE Vx, byte
	void opcode_4xkk(uint8_t Vx, uint8_t kk);
	
	//SE Vx, Vy
	void opcode_5xy0(uint8_t Vx, uint8_t Vy);

	//LD Vx, byte
	void opcode_6xkk(uint8_t Vx, uint8_t kk);

	//ADD Vx, byte
	void opcode_7xkk(uint8_t Vx, uint8_t kk);

	//LD Vx, Vy
	void opcode_8xy0(uint8_t Vx, uint8_t Vy);

	//OR Vx, Vy
	void opcode_8xy1(uint8_t Vx, uint8_t Vy);

	//AND Vx, Vy
	void opcode_8xy2(uint8_t Vx, uint8_t Vy);

	//XOR Vx, Vy
	void opcode_8xy3(uint8_t Vx, uint8_t Vy);

	//ADD Vx, Vy
	void opcode_8xy4(uint8_t Vx, uint8_t Vy);

	//SUB Vx, Vy
	void opcode_8xy5(uint8_t Vx, uint8_t Vy);

	//SHR Vx {, Vy}
	void opcode_8xy6(uint8_t Vx);

	//SUBN Vx, Vy
	void opcode_8xy7(uint8_t Vx, uint8_t Vy);
	
	//SHL Vx {, Vy}
	void opcode_8xyE(uint8_t Vx);

	//SNE Vx, Vy
	void opcode_9xy0(uint8_t Vx, uint8_t Vy);

	//LD I, addr
	void opcode_Annn(uint16_t addr);
	
	//JP V0, addr
	void opcode_Bnnn(uint16_t addr);
	
	//RND Vx, byte
	void opcode_Cxkk(uint8_t Vx, uint8_t kk);
	
	//DRW Vx, Vy, nibble
	void opcode_Dxyn(uint8_t Vx, uint8_t Vy, uint8_t nibble);
	
	//SKP Vx
	void opcode_Ex9E(uint8_t Vx);
	
	//SKNP Vx
	void opcode_ExA1(uint8_t Vx);
	
	//LD Vx, DT
	void opcode_Fx07(uint8_t Vx);
	
	//LD Vx, K
	void opcode_Fx0A(uint8_t Vx);
	
	//LD DT, Vx
	void opcode_Fx15(uint8_t Vx);
	
	//LD ST, Vx
	void opcode_Fx18(uint8_t Vx);
	
	//ADD I, Vx
	void opcode_Fx1E(uint8_t Vx);
	
	//LD F, Vx
	void opcode_Fx29(uint8_t Vx);
	
	//LD B, Vx
	void opcode_Fx33(uint8_t Vx);
	
	//LD [I], Vx
	void opcode_Fx55(uint8_t Vx);
	
	//LD Vx, [I]
	void opcode_Fx65(uint8_t Vx);
};

#endif // CHIP8_HPP