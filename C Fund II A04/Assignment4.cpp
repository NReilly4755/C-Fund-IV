#include "assignment4.h"

int main(void) {
	Run();
	return 0;
}

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
			addEntry(&EntryList, &entryCount);
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

void clearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void clearConsole() {
	system("cls");
}

void systemListen() {
	int key;
	printf("Enter 0 to go back to the main menu...");
	scanf_s("%d", &key);
	return;
}

void addEntry(Entry** EntryList, int* entryCount) {
	bool nameCheck, addressCheck, cityCheck, provinceCheck, postalCheck, phoneCheck, enterStatus;
	char nameBuffer[31];
	char addressBuffer[61];
	char cityBuffer[61];
	char provinceBuffer[4];
	char postalBuffer[8];
	char phoneBuffer[13];
	int length;
	clearConsole();
	while (1) {
		if (*entryCount >= 10) {
			printf("Entry list is full. Cannot add more entries.\n");
			return;
		}

		Entry* newEntry = (Entry*)malloc(sizeof(Entry));
		if (newEntry == NULL) {
			printf("Memory allocation failed!\n");
			return;
		}

		// Name Entry
		while (1) {
			printf("Name: \n");
			fgets(nameBuffer, 40, stdin);
			nameBuffer[strcspn(nameBuffer, "\n")] = 0;
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

		// Street Address Entry
		while (1) {
			printf("Street Address: \n");
			fgets(addressBuffer, 70, stdin);
			addressBuffer[strcspn(addressBuffer, "\n")] = 0;
			addressCheck = validateAddress(addressBuffer);
			if (!addressCheck) {
				printf("Invalid address format. Please try again.\n");
			}
			else {
				break;
			}
		}

		// City Entry
		while (1) {
			printf("City: \n");
			fgets(cityBuffer, 70, stdin);
			cityBuffer[strcspn(cityBuffer, "\n")] = 0;
			cityCheck = validateCity(cityBuffer);
			if (!cityCheck) {
				printf("Invalid city format. Please try again.\n");
			}
			else {
				break;
			}
		}

		// Province Entry
		while (1) {
			printf("Province: \n");
			fgets(provinceBuffer, 6, stdin);
			provinceBuffer[strcspn(provinceBuffer, "\n")] = 0;
			provinceCheck = validateProvince(provinceBuffer);
			if (!provinceCheck){
				printf("Invalid province format. Please try again.\n");
				clearBuffer();
			}
			else {
				break;
			}
		}
		
		// Postal Code Entry
		while (1) {
			printf("Postal Code: \n");
			fgets(postalBuffer, 10, stdin);
			length = strnlen_s(postalBuffer, 100);
			postalBuffer[strcspn(postalBuffer, "\n")] = 0;
			postalCheck = validatePostalCode(postalBuffer, length);
			if (!postalCheck) {
				printf("Invalid postal code format. Please try again.\n");
			}
			else {
				break;
			}
		}


		// Phone Number Entry
		while (1) {
			printf("Phone Number (###-###-####): \n");
			fgets(phoneBuffer, 13, stdin);
			clearBuffer();
			phoneBuffer[strcspn(phoneBuffer, "\n")] = 0;
			phoneCheck = validatePhone(phoneBuffer);
			if (!phoneCheck) {
				printf("Invalid phone number format. Please try again.\n");
			}
			else {
				break;
			}
		}

		// Confirm all validations pass
		validateUserEntries(nameCheck, addressCheck, cityCheck, provinceCheck, postalCheck, phoneCheck);

		// Copy data into new entry
		strcpy_s(newEntry->name, sizeof(newEntry->name), nameBuffer);
		strcpy_s(newEntry->address, sizeof(newEntry->address), addressBuffer);
		strcpy_s(newEntry->city, sizeof(newEntry->city), cityBuffer);
		strcpy_s(newEntry->province, sizeof(newEntry->province), provinceBuffer);
		strcpy_s(newEntry->postalCode, sizeof(newEntry->postalCode), postalBuffer);
		strcpy_s(newEntry->phone, sizeof(newEntry->phone), phoneBuffer);

		// Add entry to the list
		EntryList[*entryCount] = newEntry;
		(*entryCount)++;  

		// Testing output
		printf("Entry Added:\n");
		printf("Name: %s\n", newEntry->name);
		printf("Address: %s\n", newEntry->address);
		printf("City: %s\n", newEntry->city);
		printf("Province: %s\n", newEntry->province);
		printf("Postal Code: %s\n", newEntry->postalCode);
		printf("Phone: %s\n", newEntry->phone);

		printf("Entry count is now: %d\n", *entryCount);
	}
	}
	

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

bool validateName(char* buffer) {
	std::regex nameRegex("^[A-Za-z' -]{1,30}$");
	if (std::regex_match(buffer, nameRegex)) {
		return true;
	}
	else {
		return false;
	}
}

bool validateAddress(char* address) {
	std::regex addressRegex("^.{1,60}$");
	if (std::regex_match(address, addressRegex)) {
		return true;
	}
	else {
		return false;
	}
}

bool validateCity(char* city) {
	std::regex cityRegex("^[A-Za-z]{1,60}$");
	if (std::regex_match(city, cityRegex)) {
		return true;
	}
	else {
		return false;
	}
}

bool validateProvince(char* province) {
	std::regex provRegex("^[A-Z]{2}$");
	if (std::regex_match(province, provRegex)) {
		return true;
	}
	else {
		return false;
	}
}

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

bool validatePhone(char* phone) {
	std::regex phoneRegex("^\\d{3}-\\d{3}-\\d{4}$");
	if (std::regex_match(phone, phoneRegex)) {
		return true;
	}
	else {
		return false;
	}
}

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

void mainMenu(void) {
	printf("========== MAIN MENU ==========\n");
	printf("1. Add Entry\n");
	printf("2. Display Entries\n");
	printf("3. Exit the program\n");
	printf("===============================\n");
}

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
		systemListen();
		clearBuffer();
		}
	}

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