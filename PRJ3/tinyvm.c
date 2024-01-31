#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Dylan Becraft & Jack Sweeney
// Euripides Montagne
// CGS 3269, Computer Architecture
// November 28, 2023

int debug = 0;
// Enum for opcodes
typedef enum {
    LOAD = 1,
    ADD,
    STORE,
    SUB,
    IN,
    OUT,
    END,
    JMP,
    SKIPZ
} Opcode;

// Struct for instructions
typedef struct instruction{
    Opcode opcode;
    int address;
} Instruction;

Instruction IR;
Instruction *instructionMemory;
Instruction mDR1;

int * data;
int data_elements_count;
int counter = 0, current_counter = 0;
int accumulator = 0;
int mAR1 = 0;
int mAR2 = 0;
int mDR2 = 0;
int x = 1;

// Function to load program from file
void loadProgram(char * file, int debug) {
    FILE * fp = fopen(file, "r");
    if (fp == NULL){
        printf("Error");
        exit(1);
    }

    printf("Assembling Program...\n\n");
    int i = 0;
    int opcode, address, max_address=0;

    // First pass: count the number of instructions and data addresses
    while (fscanf(fp, "%d %d", &opcode, &address ) != EOF) {
        // Finds the largest data only memory address
        if (address > max_address && (opcode == LOAD || opcode == STORE || opcode == ADD || opcode == SUB)) {
            max_address = address;
        }
        i++;
    }
    max_address++;
    data_elements_count = max_address;
    // Allocate memory based on the number of instructions and highest address
    // This could possibly allocate a lot of memory if you use high address numbers, but if you use sequential low numbers,
    // This uses the least amount of memory without having to set a static memory
    instructionMemory = calloc(i, sizeof(Instruction));
    data = calloc(max_address, sizeof(int));
    if (data == NULL || instructionMemory == NULL) {
        printf("Error: Not enough memory\n");
        exit(1);
    }

    // If debug flag is set, print the size of the memory allocated
    if (debug) {
        printf("Debug: Allocated instruction memory size: %lu bytes for %d instructions \n", i * sizeof(Instruction), i);
        printf("Debug: Allocated data memory size: %lu bytes for %d addresses\n", max_address * sizeof(int), max_address);
    }

    // Reset file pointer and counter
    rewind(fp);
    i = 0;

    // Second pass: load the instructions into memory
    while (fscanf(fp, "%d %d", &instructionMemory[i].opcode, &instructionMemory[i].address ) != EOF)
        i++;

    printf("Program Assembled\n");
    fclose(fp);
}

// Function to execute program
void executeProgram() {
    //Exits when x is set to zero for exiting case
    while(x == 1){ // Fetch
        mAR1 = counter;
        mDR1 = instructionMemory[mAR1];
        IR = mDR1;
        current_counter = counter;
        if (debug) {
            printf("\nDebug: X: %d Counter: %d Opcode: %d on addr: %d\n", x, current_counter, IR.opcode, IR.address);
        }
        // Execute instruction based on opcode
        counter++;
        switch(IR.opcode){

            case LOAD: // Load
                mAR2 = IR.address;
                printf("/* Loading accumulator from memory location %d */\n", mAR2);
                mDR2 = data[mAR2];
                accumulator = mDR2;
                break;

            case ADD: // Add
                mAR2 = IR.address;
                printf("/* Adding %d to accumulator value */\n", data[IR.address]);
                mDR2 = data[mAR2];
                accumulator += mDR2;
                break;

            case STORE: // Store
                mAR2 = IR.address;
                printf("/* Storing accumulator to memory location %d */\n", mAR2);
                mDR2 = accumulator;
                data[mAR2] = mDR2;
                break;

            case SUB: // Subtract
                mAR2 = IR.address;
                printf("/* Subtracting %d from accumulator value */\n", data[IR.address]);
                mDR2 = accumulator;
                accumulator -= data[IR.address];
                break;

            case IN: // Input
                printf("/* Input value */\n");
                scanf("%d", &accumulator);
                break;

            case OUT: // Output
                printf("/* Outputting accumulator to screen */\n");
                printf("%d\n", accumulator);
                break;

            case END: // End
                printf("Program has ended\n");
                x = 0;
                break;

            case JMP: // Jump
                printf("/* Jumping program to PC %d */\n", IR.address);
                counter = IR.address;
                break;

            case SKIPZ: // Skipz
                printf("/* Skip next line */\n");
                if(accumulator == 0)
                    counter++;
                break;

            default:
                printf("/* Opcode error */\n");
                break;
        };

        // print 
        printf("PC = %d | A = %d | DM = [", current_counter, accumulator);

        for(int i = 0; i < data_elements_count; i++){
            if(i == 0)
                printf("%d", data[i]);
            else
                printf(", %d", data[i]);
        }

        printf("]\n\n");
    }
}

int main(int argc, char * argv[]){
    if(argc < 2) {
        printf("No Argument for filename specified\n");
        return 1;
    }
    else if (argc > 2 && argc <= 3 && strcmp(argv[2], "-d") == 0){
        printf("Debug enabled\n");
        debug = 1;
    }

    loadProgram(argv[1], debug);
    executeProgram();

    free(data);
    free(instructionMemory);
}
