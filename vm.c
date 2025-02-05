/*
 * Robert Barroso
 * 4252151
 * COP 3402: System Software
 * Homework 1: P-Machine
*/

#include <stdio.h>

#define ARRAY_TYPE 500

int base( int BP, int L, int pas[]);

int main(int argc, char * argv[]) {

// Initializing Variables
int BP = 499;
int SP = BP + 1;
int PC = 10;

int pas[ARRAY_TYPE + 1] = {0};                                  // Creating PAS
char ir[ARRAY_TYPE] = {0};                                      // Creating IR Holder
int incLevel[ARRAY_TYPE] = {0};                                 // Keep track of how many CAL ops are called

int opCode = 0;                                                 // Initializing OPCode Variable
int lexLevel = 0;                                               // Initializing LexLevel Variable
int mValue = 0;                                                 // Initializing 'M' Value Variable
int grabValueFrom = 0;                                          // Holds the value from input.txt to be copied
int currentCounter = (PC * 3);                                  // Only used in the scan
int incIndex = 0;                                               // Keep track of the index of incLevel

FILE * inputFile = fopen(argv[1], "r");
if (inputFile == NULL) {
    printf("Error: Opening file has failed!\n");
    return -1;
}

while (fscanf(inputFile, "%d", &grabValueFrom) == 1) {
      ir[currentCounter] = grabValueFrom;
      currentCounter++;
}


fclose(inputFile);

// Default Output
printf("                 PC  BP   SP  stack\n");
printf("Initial values:  %-2d  %-3d  %-3d\n", PC, BP, SP);
printf("\n");

// Initial Command                                              // Only used for the first command
int loc = (PC * 3);
opCode = ir[loc];
lexLevel = ir[loc + 1];
mValue = ir[loc + 2];
int eop = 1;

 while (eop != 0) {

// 01 - LIT
     if (opCode == 1) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         SP = SP - 1;
         pas[SP] = mValue;
         PC += 3;
         incLevel[incIndex]++;

         // Return Selection
         printf("    LIT  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         for (int i = 0; i < incLevel[0]; i++) {
             printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

         }

         for (int i = 0; i < incLevel[incIndex]; i++) {
             if (incLevel[i + 1] > 0) {
                 printf(" |");
                 for (int j = ((ARRAY_TYPE - 1) - incLevel[0]); j > (((ARRAY_TYPE - 1) - incLevel[0]) - incLevel[incIndex]); j--) {
                     printf(" %d", pas[j]);
                 }
             }
         }

         printf("\n");
         opCode = ir[loc + PC];
     }

// 02 - OPR
     if (opCode == 2) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         if (mValue == 0 && lexLevel == 0) {
             SP = BP + 1;
             BP = pas[SP - 2];
             PC = pas[SP - 3];

             printf("    RTN  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 1) {
             pas[SP + 1] = pas[SP + 1] + pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    ADD  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 2) {
             pas[SP + 1] = pas[SP + 1] - pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    SUB  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 3) {
             pas[SP + 1] = pas[SP + 1] * pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    MUL  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 4) {
             pas[SP + 1] = pas[SP + 1] / pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    DIV  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 5) {
             pas[SP + 1] = pas[SP + 1] == pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    EQL  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 6) {
             pas[SP + 1] = pas[SP + 1] != pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    NEQ  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 7) {
             pas[SP + 1] = pas[SP + 1] < pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    LSS  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 8) {
             pas[SP + 1] = pas[SP + 1] <= pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    LEQ  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 9) {
             pas[SP + 1] = pas[SP + 1] > pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    GTR  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }
         if (mValue == 10) {
             pas[SP + 1] = pas[SP + 1] >= pas[SP];
             SP = SP + 1;
             PC += 3;
             incLevel[incIndex]--;
             printf("    GEQ  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         }


         // Return Section
         for (int i = 0; i < incLevel[0]; i++) {
             printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

         }
    if (mValue > 0) {
        for (int i = 0; i < incLevel[incIndex]; i++) {
            if (incLevel[i + 1] > 0) {
                printf(" |");
                for (int j = ((ARRAY_TYPE - 1) - incLevel[0]); j > (((ARRAY_TYPE - 1) - incLevel[0]) - incLevel[incIndex]); j--) {
                    printf(" %d", pas[j]);
                }
            }
        }
    }

         printf("\n");
         opCode = ir[loc + PC];
     }

// 03 - LOD
     if (opCode == 3) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         SP = SP - 1;
         pas[SP] = pas[base(BP, lexLevel, pas) - mValue];
         PC += 3;
         incLevel[incIndex]++;

         // Return Selection
         printf("    LOD  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         for (int i = 0; i < incLevel[0]; i++) {
             printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

         }

         for (int i = 0; i < incLevel[incIndex]; i++) {
             if (incLevel[i + 1] > 0) {
                 printf(" |");
                 for (int j = ((ARRAY_TYPE - 1) - incLevel[0]); j > (((ARRAY_TYPE - 1) - incLevel[0]) - incLevel[incIndex]); j--) {
                     printf(" %d", pas[j]);
                 }
             }
         }

         printf("\n");
         opCode = ir[loc + PC];
     }

// 04 - STO
     if (opCode == 4) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         pas[base(BP, lexLevel, pas) - mValue] = pas[SP];
         SP = SP + 1;
         PC += 3;
         incLevel[incIndex]--;

         // Return Selection
         printf("    STO  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         for (int i = 0; i < incLevel[0]; i++) {
             printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

         }

         for (int i = 0; i < incLevel[incIndex]; i++) {
             if (incLevel[i + 1] > 0) {
                 printf(" |");
                 for (int j = ((ARRAY_TYPE - 1) - incLevel[0]); j > (((ARRAY_TYPE - 1) - incLevel[0]) - incLevel[incIndex]); j--) {
                     printf(" %d", pas[j]);
                 }
             }
         }

         printf("\n");
         opCode = ir[loc + PC];
     }

// 05 - CAL
     if (opCode == 5) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         pas[SP - 1] = base(BP, lexLevel, pas);
         pas[SP - 2] = BP;
         PC += 3;
         pas[SP - 3] = PC;
         BP = SP - 1;
         PC = mValue;
         incLevel[incIndex] = mValue;

         // Return Selection
         printf("    CAL  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         for (int i = 0; i < incLevel[0]; i++) {
             printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

         }

         for (int i = 0; i < incLevel[incIndex]; i++) {
             if (incLevel[i + 1] > 0) {
                 printf(" |");
                 for (int j = ((ARRAY_TYPE - 1) - incLevel[0]); j > (((ARRAY_TYPE - 1) - incLevel[0]) - incLevel[incIndex]); j--) {
                     printf(" %d", pas[j]);
                 }
             }
         }

         printf("\n");
         opCode = ir[loc + PC];
         incIndex++;
     }

// 06 - INC
     if (opCode == 6) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         SP = SP - mValue;
         PC += 3;
         incLevel[incIndex] = mValue;



         // Return Selection
         printf("    INC  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
            for (int i = 0; i < incLevel[0]; i++) {
                printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

        }

         for (int i = 0; i < incLevel[incIndex]; i++) {
             if (incLevel[i + 1] > 0) {
                 printf(" |");
                 for (int j = ((ARRAY_TYPE - 1) - incLevel[0]); j > (((ARRAY_TYPE - 1) - incLevel[0]) - incLevel[incIndex]); j--) {
                     printf(" %d", pas[j]);
                 }
             }
         }

         printf("\n");
         opCode = ir[loc + PC];


     }

// 07 - JMP
     if (opCode == 7) {
         // Update Values
         lexLevel = ir[loc + 1];
         mValue = ir[loc + 2];

         // Main Activity
         PC = mValue;

         // Return Section
         printf("    JMP  %d   %-2d  %-2d  %-3d  %-3d\n", lexLevel, mValue, PC, BP, SP);

         opCode = ir[loc + PC];
     }

// 08 - JPC
     if (opCode == 8) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         if (ir[SP] == 0) {
             PC = mValue;
             SP = SP + 1;
         }
         incLevel[incIndex]--;


         // Return Selection
         printf("    JPC  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         for (int i = 0; i < incLevel[0]; i++) {
             printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

         }

         for (int i = 0; i < incLevel[incIndex]; i++) {
             if (incLevel[i + 1] > 0) {
                 printf(" |");
                 for (int j = ((ARRAY_TYPE - 1) - incLevel[0]); j > (((ARRAY_TYPE - 1) - incLevel[0]) - incLevel[incIndex]); j--) {
                     printf(" %d", pas[j]);
                 }
             }
         }

         printf("\n");
         opCode = ir[loc + PC];
     }

// 09 - SYS
     if (opCode == 9) {
         // Update Values
         lexLevel = ir[(loc + PC) + 1];
         mValue = ir[(loc + PC) + 2];

         // Main Activity
         if (mValue == 1) {
             printf("Output result is: %d\n", pas[SP]);
             SP = SP + 1;

         }
         if (mValue == 2) {
             SP = SP - 1;
             printf("Please Enter an Integer: ");
             int userEntry = 0;
             scanf("%d", &userEntry);
             pas[SP] = userEntry;
         }

         PC += 3;

         // Return Selection
         printf("    SYS  %d   %-2d  %-2d  %-3d  %-3d", lexLevel, mValue, PC, BP, SP);
         for (int i = 0; i < incLevel[0]; i++) {
             printf(" %d", pas[(ARRAY_TYPE - 1)- i]);

         }

if (mValue == 3) {
    eop--;
}
         printf("\n");
         opCode = ir[loc + PC];

     }

 }
    return 0;
} // End of program


int base(int BP, int L, int pas[])
{
    int arb = BP; // arb = activation record base
    while ( L > 0) //find base L levels down
    {
        arb = pas[arb];
        L--;
    }
    return arb;
}
