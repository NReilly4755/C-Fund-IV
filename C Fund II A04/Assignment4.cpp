
#include "assignment4.h"

int main(void) {
	printf("What's good playa? \n");
	return 0;
}

void Run(void) {
	int entryCount;
	int choice;
	Entry* EntryList = (Entry*)malloc(10 * sizeof(Entry));
	
}













//
// FUNCTION   : GetValidIntegerInput     
// DESCRIPTION: Makes sure that the input read from keyboard is a single int only between 1-6 inclusive  
//                    
// PARAMETERS : none     
// RETURNS    : value, which is the number isolated and meets the range of 1-6 inclusive.     
//
int GetValidIntegerInput(void) {

	// Declare the local variables
	int value;
	char buffer[100];

	while (1) {

		// Read the input from the user, make sure it is within bounds. 
		if (fgets(buffer, sizeof(buffer), stdin)) {

			// Use sscanf_s to parse the integer out of the input
			if (sscanf_s(buffer, "%d", &value) == 1) {

				// After parsing, initalize the pointer be equal to the buffer to get data.
				char* extra_char = buffer;

				// Skip over the number if it is more, increament the extra counter
				while (*extra_char >= '0' && *extra_char <= '9') {
					extra_char++;
				}

				// Check to see if after skipping the number, there are actual characters at the end.
				while (*extra_char != '\0') {
					if (*extra_char != ' ' && *extra_char != '\n') {
						break;
					}
					extra_char++;
				}

				// Check to confirm that the number entered ends with null\newline
				if (*extra_char == '\0' || *extra_char == '\n') {
					return value; // Valid input
				}
			}
		}
		printf("Invalid input! Please enter a valid number:\n");
	}
}

//
// FUNCTION   : clearBuffer
// DESCRIPTION: Consumes the newline character that is left in the buffer after scanf_s.
//                    
// PARAMETERS : none
// RETURNS    : none
//
void clearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//
// FUNCTION   : clearConsole  
// DESCRIPTION: Uses the Windows command prompt to clear the console screen.
//                    
// PARAMETERS : none
// RETURNS    : none
//
void clearConsole() {
	system("cls");
}

//
// FUNCTION   : systemListen  
// DESCRIPTION: To purposily lag the system when the user is prompted to enter 0 to go back to the main menu.
//                    
// PARAMETERS : none
// RETURNS    : none
//
void systemListen() {
	char* key;
	printf("Enter 0 to go back to the main menu...");
	scanf_s("%d", &key);
	return;
}

void addEntry(void) {
	printf("Name: \n");
	//Scan the stuff
	//Validate it with a function for regex
	//do a check if the Enter key was entered. If so, return and end program. 
	printf("Street Address: \n");
	//Scan the stuff
	//Validate it with a function for regex
	printf("City: \n");
	//Scan the stuff
	//Validate it with a function for regex
	printf("Province: \n");
	//Scan the stuff
	//Validate it with a function for regex
	printf("Postal Code: \n");
	//Scan the stuff
	//Validate it with a function for regex
	printf("Phone Number: \n");
	//Scan the stuff
	//Validate it with a function for regex

	//Call a function that takes in all the info and displays and gets a confirmation from the user

	//Append it to the array

	//Increament the counter. 
}