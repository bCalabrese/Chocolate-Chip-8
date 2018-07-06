#include<cstdint>
/*
0x000 -> 0x1FF -- Interpreter space

0x200		-- Start of most Chip-8 programs
0x600		-- Start of ETI 660 Chip-8 programs

0x200 -> 0xFFF -- Program + Data space
*/
#define MEMORY_SIZE 4096
#define DISPLAY_SIZE 2048
#define STACK_SIZE 16
#define NUM_REGISTERS 16
#define NUM_INPUTS 16
// Offset for hex font sprites in interpreter memory
#define SPRITE_OFFSET 0

// Full memory space
uint8_t memory[MEMORY_SIZE] = { 0 };
// Display buffer
uint8_t display[DISPLAY_SIZE] = { 0 };
// Stack
uint16_t stack[STACK_SIZE] = { 0 };
// Keyboard states
bool keyboard[NUM_INPUTS] = { 0 };


// Registers V0 -> VF
uint8_t registers[16] = { 0 };
// Sound timer register
uint8_t soundRegister = 0;
// Delay timer register
uint8_t delayRegister = 0;

// 16-bit register, usually used for 12-bit memory addresses
uint16_t largeRegister = 0;

// Program Counter
uint16_t programCounter = 0;
// Stack pointer
uint16_t stackPointer = 0;
void initializeSpriteMemory() {
	// 0
	uint16_t offset = SPRITE_OFFSET;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x90;
	memory[offset + 2] = 0x90;
	memory[offset + 3] = 0x90;
	memory[offset + 4] = 0xF0;
	// 1
	offset += 5;
	memory[offset + 0] = 0x20;
	memory[offset + 1] = 0x60;
	memory[offset + 2] = 0x20;
	memory[offset + 3] = 0x20;
	memory[offset + 4] = 0x70;
	// 2
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x10;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x80;
	memory[offset + 4] = 0xF0;
	// 3
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x10;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x10;
	memory[offset + 4] = 0xF0;
	// 4
	offset += 5;
	memory[offset + 0] = 0x90;
	memory[offset + 1] = 0x90;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x10;
	memory[offset + 4] = 0x10;
	// 5
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x80;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x10;
	memory[offset + 4] = 0xF0;
	// 6
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x80;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x90;
	memory[offset + 4] = 0xF0;
	// 7
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x10;
	memory[offset + 2] = 0x20;
	memory[offset + 3] = 0x40;
	memory[offset + 4] = 0x40;
	// 8
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x90;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x90;
	memory[offset + 4] = 0xF0;
	// 9
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x90;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x10;
	memory[offset + 4] = 0xF0;
	// A
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x90;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x90;
	memory[offset + 4] = 0x90;
	// B
	offset += 5;
	memory[offset + 0] = 0xE0;
	memory[offset + 1] = 0x90;
	memory[offset + 2] = 0xE0;
	memory[offset + 3] = 0x90;
	memory[offset + 4] = 0xE0;
	// C
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x80;
	memory[offset + 2] = 0x80;
	memory[offset + 3] = 0x80;
	memory[offset + 4] = 0xF0;
	// D
	offset += 5;
	memory[offset + 0] = 0xE0;
	memory[offset + 1] = 0x90;
	memory[offset + 2] = 0x90;
	memory[offset + 3] = 0x90;
	memory[offset + 4] = 0xE0;
	// E
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x80;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x80;
	memory[offset + 4] = 0xF0;
	// F
	offset += 5;
	memory[offset + 0] = 0xF0;
	memory[offset + 1] = 0x80;
	memory[offset + 2] = 0xF0;
	memory[offset + 3] = 0x80;
	memory[offset + 4] = 0x80;
}


void performInstruction(uint16_t inst) {
	if (inst < 0x1000) {
		switch (inst) {
		case 0x00E0: // CLS -- Clear the screen
			break;
		case 0x00EE: // RET -- Return from a subroutine
			// TODO: Set program counter to address at top of stack
			// Sub 1 from stack pointer
			break;
		default: break; // SYS addr -- jump to routine at nnn in 0x0nnn. Unused.
		}
	}
	else if (inst < 0x2000) { // JP addr 0x1nnn
		// TODO: Set program counter to nnn from 0x1nnn
	}
	else if (inst < 0x3000) { // CALL addr 0x2nnn
		// TODO: Call subroutine at nnn from 0x2nnn
		// Increment stack pointer, place current Program Counter on stack
		// Set Program Counter to nnn
	}
	else if (inst < 0x4000) { // SE Vx, byte 0x3kk
		// TODO: If value at register Vx == kk, increment Program Counter by 2
		// Skips next instruction
	}
	else if (inst < 0x5000) { // SNE Vx, byte 0x4xkk
		// TODO: If value at register Vx != kk, increment Program Counter by 2
		// Skips next instruction
	}
	else if (inst < 0x6000) { // SE Vx, Vy 0x5xy0
		// TODO: Skip next instruction if Vx == Vy, increment Program Counter by 2
	}
	else if (inst < 0x7000) { // LD Vx, byte 0x6xkk
		// TODO: Store byte kk into register Vx
	}
	else if (inst < 0x8000) { // ADD Vx, byte 0x7xkk
		// TODO: Vx += kk
	}
	else if (inst < 0x9000) { // Various operations with 2 registers 0x8xyP
		switch (inst && 0xF) { // Lower 4 bits determine the op
		case 0x0: // LD Vx, Vy
			// TODO: Set Vx = Vy
			break;
		case 0x1: // OR Vx Vy
			// TODO: Vx = Vx | Vy
			break;
		case 0x2: // AND Vx Vy
			// TODO: Vx = Vx & Vy
			break;
		case 0x3: // XOR Vx Vy
			// TODO: Vx ^ Vy
			break;
		case 0x4: // ADD Vx, Vy
			// TODO: Vx += Vy
			// If > 255, only keep lowest 8 bits and set VF = 1, else VF = 0
			break;
		case 0x5: // SUB VX, VY
			// TODO: Vx -= Vy
			// VF = (Vx > Vy)
			break;
		case 0x6: // SHR Vx {, Vy}
			// TODO:  Vx >>= Vx
			// Set VF to last bit of Vx, then divide Vx by 2
			break;
		case 0x7: // SUBN Vx, Vy
			// TODO: Vx = Vy - Vx
			// VF = (Vy > Vx)
			break;
		case 0xE: // SHL Vx {, Vy}
			// TODO: Vx <<= 1
			// Set VF to first bit of Vx, then multiply Vx by 2
			break;
		default:
			//Invalid operation
			break;
		}
	}
	else if (inst < 0xA000) { // SNE Vx, Vy 0x9xy0
		// TODO: if Vx != Vy, inc Program Counter by 2
		// This skips next instruction
	}
	else if (inst < 0xB000) { // LD I, addr 0xAnnn
		// TODO: Set register I to nnn
	}
	else if (inst < 0xC000) { // JP V0, addr 0xBnnn
		// TODO: Program Counter is set to nnn offset by V0
	}
	else if (inst < 0xD000) { // RND Vx, byte
		// TODO: Gen random number between 0 and 255, and with byte kk, store in Vx
	}
	else if (inst < 0xE000) { // DRW Vx, Vy, nibble 0xDxyn
		// TODO: Display n byte sprite at memory location I, at coordinates (Vx, Vy)
		// Bytes are read from memory and XORed onto display
		// If any pixels are erased by this, set collision flag VF = 1, else VF = 0
	}
	else if (inst < 0xF000) { // Skip instructions
		switch (inst & 0xFF) {
		case 0x9E: // SKP Vx
			// TODO: If keypad key with value at Vx is DOWN, increase PC by 2
			break;
		case 0xA1: // SKNP Vx
			// TODO: If keypad key with value at Vx is UP, increase PC by 2
			break;
		}
	}
	else { // 0xF000 - 0xFFFF
		switch (inst & 0xFF) {
		case 0x07: // LD Vx, DT
			// TODO: Vx is set to delay timer value
			break;
		case 0x0A: // LD Vx, K
			// TODO: Wait for a key to be pressed, store value of key in Vx
			// Everything is stopped until a key is pressed
			break;
		case 0x15: // LD DT, Vx
			// TODO: Set delay timer = Vx
			break;
		case 0x18: // LD ST, Vx
			// TODO: Set sound timer = Vx
			break;
		case 0x1E: // ADD I, Vx
			// TODO: I += Vx
			break;
		case 0x29: // LD F, Vx
			// TODO: I = location of sprite for digit Vx
			// (Hex font in interpreter memory)
			break;
		case 0x33: // LD B, Vx
			// TODO: BCD of value in Vx, conv to decimal, hundres in location I, tens location I+1, ones at I+2
			break;
		case 0x55: // LD [I], Vx
			// TODO: Store all registers starting at location I.
			break;
		case 0x65: // LD Vx, [I]
			// TODO; Load all registers starting from location I.
			break;
		default: // Unknown?
		}
	}
}

int main() {
	return 0;
}