/*
* FILE		    : Assignemnt4.cpp
* PROJECT	    : SENG 1050 Assignment 4
* PROGRAMMER	: NICHOLAS REILLY
* FIRST VERSION	: 2025-04-02
* DESCRIPTION	: A program that allows the user to enter and validate personal information such as name, address, city, province, postal code, and phone number. The program also provides a menu for adding entries and displaying them.
* REFERENCING   : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc.
*/

#include "assignment4.h"

int main(void) {
	Run();
	return 0;
}

//
// FUNCTION   : Run 
// DESCRIPTION: Acts as the main function that runs the program
//                    
// PARAMETERS : none. 
// RETURNS    : none.   
//
void Run(void) {
	int choice;
	int entryCount = 0;
	Entry* EntryList = (Entry*)malloc(10 * sizeof(Entry));
	if (EntryList == NULL) {
		printf("Memory allocation failed!\n");
		return;
	}
	InitializeEntryList(EntryList);

	while (1) {
		mainMenu();
		printf("Enter your choice: \n");
		choice = GetValidIntegerInput();
		switch (choice) {
		case 1:
			addEntry(EntryList, &entryCount);
			break;
		case 2:
			displayEntries(EntryList, entryCount);
			break;
		case 3:
			printf("Exiting the program...\n");
			free(EntryList);
			return;
		default:
			printf("Invalid choice! Please try again.\n");
			break;
		}
	}
}

//
// FUNCTION   : GetValidIntegerInput
// DESCRIPTION: Reads an integer input from the user and validates it.
// PARAMETERS : none.
// RETURNS    : int - the valid integer input from the user.
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
				// After parsing, initialize the pointer to be equal to the buffer to get data.
				char* extra_char = buffer;

				// Skip over the number if it is more, increment the extra counter
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
// DESCRIPTION: Clears the input buffer to remove any unwanted characters.
// PARAMETERS : none.
// RETURNS    : none.
void clearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//
// FUNCTION   : clearConsole
// DESCRIPTION: Clears the console screen.
// PARAMETERS : none.
// RETURNS    : none.
void clearConsole() {
	system("cls");
}

//
// FUNCTION   : systemListen
// DESCRIPTION: Waits for the user to press Enter before continuing.
// PARAMETERS : none.
// RETURNS    : none.
void systemListen() {
	int key;
	printf("Enter 0 to go back to the main menu...");
	scanf_s("%d", &key);
	return;
}

//
// FUNCTION   : addEntry
// DESCRIPTION: Adds a new entry to the entry list after validating user input.
// PARAMETERS : EntryList - pointer to the list of entries
//              entryCount - pointer to the number of entries in the list
// RETURNS    : none.
void addEntry(Entry* EntryList, int* entryCount) {
    bool nameCheck, addressCheck, cityCheck, provinceCheck, postalCheck, phoneCheck, enterStatus;
    char nameBuffer[32];       
    char addressBuffer[61];    
    char cityBuffer[61];       
    char provinceBuffer[4];    
    char postalBuffer[9];      
    char phoneBuffer[14];      
    int length;
    clearConsole();

    //First check to make sure there are not any more than 10 user entries
    while (1) {
        if (*entryCount >= 10) {
            printf("Entry list is full. Cannot add more entries.\n");
            return;
        }

        //Name Entry code
        while (1) {
            printf("Name (Alphabetical, 30 MAX): \n");
            if (fgets(nameBuffer, sizeof(nameBuffer), stdin) == NULL) {
                printf("Error reading name. Try again.\n");
                continue;
            }
            if (strchr(nameBuffer, '\n') == NULL) {
                printf("Input too long. Max 31 characters allowed.\n");
                clearBuffer();
                continue;
            }
            nameBuffer[strcspn(nameBuffer, "\n")] = '\0';
            length = strlen(nameBuffer);
            if (length > 31) {
                printf("Name too long. Max 31 characters allowed.\n");
                continue;
            }
            enterStatus = enterCheck(nameBuffer);
            if (enterStatus) {
                return;
            }
            nameCheck = validateName(nameBuffer);
            if (!nameCheck) {
                printf("Invalid name entry. Please try again.\n");
            }
            else {
                break;
            }
        }

        //Street Address Entry code
        while (1) {
            printf("Street Address (Alphanumerical, 60 MAX): \n");
            if (fgets(addressBuffer, sizeof(addressBuffer), stdin) == NULL) {
                continue;
            }
            if (strchr(addressBuffer, '\n') == NULL) {
                printf("Input too long. Max 60 characters allowed.\n");
                clearBuffer();
                continue;
            }
            addressBuffer[strcspn(addressBuffer, "\n")] = '\0';
            length = strlen(addressBuffer);
            if (length > 60) {
                printf("Address too long. Max 60 characters allowed.\n");
                continue;
            }
            addressCheck = validateAddress(addressBuffer);
            if (!addressCheck) {
                printf("Invalid address format. Please try again.\n");
            }
            else {
                break;
            }
        }

        //City Entry code
        while (1) {
            printf("City (Alphabetical, 60 MAX): \n");
            if (fgets(cityBuffer, sizeof(cityBuffer), stdin) == NULL) {
                continue;
            }
            if (strchr(cityBuffer, '\n') == NULL) {
                printf("Input too long. Max 60 characters allowed.\n");
                clearBuffer();
                continue;
            }
            cityBuffer[strcspn(cityBuffer, "\n")] = '\0';
            length = strlen(cityBuffer);
            if (length > 60) {
                printf("City name too long. Max 60 characters allowed.\n");
                continue;
            }
            cityCheck = validateCity(cityBuffer);
            if (!cityCheck) {
                printf("Invalid city format. Please try again.\n");
            }
            else {
                break;
            }
        }

        //Province Entry code
        while (1) {
            printf("Province: \n");
            if (fgets(provinceBuffer, sizeof(provinceBuffer), stdin) == NULL) {
                continue;
            }
            if (strchr(provinceBuffer, '\n') == NULL) {
                printf("Input too long. Max 2 characters allowed.\n");
                clearBuffer();
                continue;
            }
            provinceBuffer[strcspn(provinceBuffer, "\n")] = '\0';
            length = strlen(provinceBuffer);
            if (length != 2) {
                printf("Province must be 2 characters.\n");
                continue;
            }
            provinceCheck = validateProvince(provinceBuffer);
            if (!provinceCheck) {
                printf("Invalid province format. Please try again.\n");
            }
            else {
                break;
            }
        }

        //Postal Code Entry code
        while (1) {
            printf("Postal Code (LNL NLN): \n");
            if (fgets(postalBuffer, sizeof(postalBuffer), stdin) == NULL) {
                continue;
            }
            if (strchr(postalBuffer, '\n') == NULL) {
                printf("Input too long. Max 7 characters allowed (e.g., A1A 1A1).\n");
                clearBuffer();
                continue;
            }
            postalBuffer[strcspn(postalBuffer, "\n")] = '\0';
            length = strlen(postalBuffer);
            if (length > 7) {
                printf("Postal code too long. Max 7 characters.\n");
                continue;
            }
            postalCheck = validatePostalCode(postalBuffer, length);
            if (!postalCheck) {
                printf("Invalid postal code format. Please try again.\n");
            }
            else {
                break;
            }
        }

        //Phone Number Entry
        while (1) {
            printf("Phone Number (###-###-####): \n");
            if (fgets(phoneBuffer, sizeof(phoneBuffer), stdin) == NULL) {
                continue;
            }
            if (strchr(phoneBuffer, '\n') == NULL) {
                printf("Input too long. Max 12 characters (###-###-####).\n");
                clearBuffer();
                continue;
            }
            phoneBuffer[strcspn(phoneBuffer, "\n")] = '\0';
            length = strlen(phoneBuffer);
            if (length != 12) {
                printf("Phone number must be 12 characters (###-###-####).\n");
                continue;
            }
            phoneCheck = validatePhone(phoneBuffer);
            if (!phoneCheck) {
                printf("Invalid phone number format. Please try again.\n");
            }
            else {
                break;
            }
        }

        //Confirm all validations pass
        validateUserEntries(nameCheck, addressCheck, cityCheck, provinceCheck, postalCheck, phoneCheck);

        //Add data to the list
        strcpy_s(EntryList[*entryCount].name, sizeof(EntryList[*entryCount].name), nameBuffer);
        strcpy_s(EntryList[*entryCount].address, sizeof(EntryList[*entryCount].address), addressBuffer);
        strcpy_s(EntryList[*entryCount].city, sizeof(EntryList[*entryCount].city), cityBuffer);
        strcpy_s(EntryList[*entryCount].province, sizeof(EntryList[*entryCount].province), provinceBuffer);
        strcpy_s(EntryList[*entryCount].postalCode, sizeof(EntryList[*entryCount].postalCode), postalBuffer);
        strcpy_s(EntryList[*entryCount].phone, sizeof(EntryList[*entryCount].phone), phoneBuffer);

        //Increment entry count
        (*entryCount)++;
    }
}

//
// FUNCTION   : enterCheck
// DESCRIPTION: Checks if the Enter key was pressed without any input.
// PARAMETERS : buffer - the input buffer
// RETURNS    : true if Enter was pressed without input, false otherwise.
bool enterCheck(char* buffer) {
	// Check if the name input is empty (only Enter key pressed)
	if (buffer[0] == '\n' || strlen(buffer) == 0) {
		printf("Enter was pressed without input. Returning to main menu...\n");
		clearBuffer();
		return true;
	}
	else {
		return false;
	}
}

//
// FUNCTION   : validateName
// DESCRIPTION: Validates the name input using regex.
// PARAMETERS : buffer - the name input buffer
// RETURNS    : true if valid, false otherwise.
bool validateName(char* buffer) {
	std::regex nameRegex("^[A-Za-z' -]{1,30}$");
	if (std::regex_match(buffer, nameRegex)) {
		return true;
	}
	else {
		return false;
	}
}
//
// FUNCTION   : validateAddress
// DESCRIPTION: Validates the address input using regex.
// PARAMETERS : address - the address input buffer
// RETURNS    : true if valid, false otherwise.
bool validateAddress(char* address) {
	std::regex addressRegex("^.{1,60}$");
	if (std::regex_match(address, addressRegex)) {
		return true;
	}
	else {
		return false;
	}
}

//
// FUNCTION   : validateCity
// DESCRIPTION: Validates the city input using regex.
// PARAMETERS : city - the city input buffer
// RETURNS    : true if valid, false otherwise.
bool validateCity(char* city) {
	std::regex cityRegex("^[A-Za-z]{1,60}$");
	if (std::regex_match(city, cityRegex)) {
		return true;
	}
	else {
		return false;
	}
}

//
// FUNCTION   : validateProvince
// DESCRIPTION: Validates the province input using regex.
// PARAMETERS : province - the province input buffer
// RETURNS    : true if valid, false otherwise.
bool validateProvince(char* province) {
	std::regex provRegex("^[A-Z]{2}$");
	if (std::regex_match(province, provRegex)) {
		return true;
	}
	else {
		return false;
	}
}

//
// FUNCTION   : validatePostalCode
// DESCRIPTION: Validates the postal code input using regex.
// PARAMETERS : postalCode - the postal code input buffer
//              length - the length of the postal code
// RETURNS    : true if valid, false otherwise.
bool validatePostalCode(char* postalCode ,int length) {
	std::regex postalRegex("^[A-Za-z][0-9][A-Za-z] [0-9][A-Za-z][0-9]$");
	if (length > 7 || length < 7) {
		return false;
	}

	if (std::regex_match(postalCode, postalRegex)) {
		return true;
	}
	else {
		return false;
	}
}

//
// FUNCTION   : validatePhone
// DESCRIPTION: Validates the phone number input using regex.
// PARAMETERS : phone - the phone number input buffer
// RETURNS    : true if valid, false otherwise.
bool validatePhone(char* phone) {
	std::regex phoneRegex("^\\d{3}-\\d{3}-\\d{4}$");
	if (std::regex_match(phone, phoneRegex)) {
		return true;
	}
	else {
		return false;
	}
}

//
// FUNCTION   : validateUserEntries
// DESCRIPTION: Validates all user entries and prints the results.
// PARAMETERS : nameCheck - result of name validation
//              addressCheck - result of address validation
//              cityCheck - result of city validation
//              provinceCheck - result of province validation
//              postalCheck - result of postal code validation
//              phoneCheck - result of phone number validation
// RETURNS    : none.
void validateUserEntries(bool nameCheck, bool addressCheck, bool cityCheck, bool provinceCheck, bool postalCheck, bool phoneCheck) {
	if (nameCheck && addressCheck && cityCheck && provinceCheck && postalCheck && phoneCheck) {
		printf("All entries are valid.\n");
	}
	else {
		printf("You failed on these checks: \n");
		printf("Name: %s\n", nameCheck ? "Valid" : "Invalid");
		printf("Address: %s\n", addressCheck ? "Valid" : "Invalid");
		printf("City: %s\n", cityCheck ? "Valid" : "Invalid");
		printf("Province: %s\n", provinceCheck ? "Valid" : "Invalid");
		printf("Postal Code: %s\n", postalCheck ? "Valid" : "Invalid");
		printf("Phone Number: %s\n", phoneCheck ? "Valid" : "Invalid");
	}
}

//
// FUNCTION   : mainMenu
// DESCRIPTION: Displays the main menu options to the user.
// PARAMETERS : none.
// RETURNS    : none.
void mainMenu(void) {
	clearConsole();
	printf("========== MAIN MENU ==========\n");
	printf("1. Add Entry\n");
	printf("2. Display Entries\n");
	printf("3. Exit the program\n");
	printf("===============================\n");
}

//
// FUNCTION   : displayEntries
// DESCRIPTION: Displays all entries in the entry list.
// PARAMETERS : EntryList - pointer to the list of entries
//              entryCount - the number of entries in the list
// RETURNS    : none.
void displayEntries(Entry* EntryList, int entryCount) {
	if (entryCount == 0) {
		printf("No entries to display.\n");
		return;
	}
	printf("========== ENTRY LIST ==========\n");
	for (int i = 0; i < entryCount; i++) {
		printf("Entry %d:\n", i + 1);
		printf("Name: %s\n", EntryList[i].name);
		printf("Address: %s\n", EntryList[i].address);
		printf("City: %s\n", EntryList[i].city);
		printf("Province: %s\n", EntryList[i].province);
		printf("Postal Code: %s\n", EntryList[i].postalCode);
		printf("Phone: %s\n", EntryList[i].phone);
		printf("===============================\n");
		printf("Press Enter to see the next entry...\n");
		getchar();
		}
	}

//
// FUNCTION   : InitializeEntryList
// DESCRIPTION: Initializes the entry list by setting all fields to empty strings.
// PARAMETERS : EntryList - pointer to the list of entries
// RETURNS    : none.
void InitializeEntryList(Entry* EntryList) {
	for (int i = 0; i < 10; i++) {
		strcpy_s(EntryList[i].name, sizeof(EntryList[i].name), "");
		strcpy_s(EntryList[i].address, sizeof(EntryList[i].address), "");
		strcpy_s(EntryList[i].city, sizeof(EntryList[i].city), "");
		strcpy_s(EntryList[i].province, sizeof(EntryList[i].province), "");
		strcpy_s(EntryList[i].postalCode, sizeof(EntryList[i].postalCode), "");
		strcpy_s(EntryList[i].phone, sizeof(EntryList[i].phone), "");
	}
}