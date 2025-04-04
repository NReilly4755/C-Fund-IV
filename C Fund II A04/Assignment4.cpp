
#include "assignment4.h"

int main(void) {
	Run();
	return 0;
}

void Run(void) {
	int* entryCount;
	int choice;
	Entry* EntryList = (Entry*)malloc(10 * sizeof(Entry));
	while (1) {
		mainMenu();
		printf("Enter your choice: \n");
		choice = GetValidIntegerInput();
		switch (choice) {
		case 1:
			addEntry(&EntryList, entryCount);
			break;
		case 2:
			//DisplayEntries(EntryList, entryCount);
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

void addEntry(Entry** EntryList, int* entryCount) {
	bool nameCheck, addressCheck, cityCheck, provinceCheck, postalCheck, phoneCheck, int entryStatus;
	char buffer[6][60];
	Entry* newEntry = (Entry*)malloc(sizeof(Entry));
	printf("Name: \n");
	fgets(buffer[1], 30, stdin);
	nameCheck = validateName(buffer[1]);
	enterCheck(buffer[1]);

	printf("Street Address: \n");
	fgets(buffer[2], 60, stdin);
	addressCheck = validateAddress(buffer[2]);
	

	printf("City: \n");
	fgets(buffer[3], 60, stdin);
	cityCheck = validateCity(buffer[3]);

	printf("Province: \n");
	fgets(buffer[4], 2, stdin);
	provinceCheck = validateProvince(buffer[4]);	

	printf("Postal Code: \n");
	fgets(buffer[5], 7, stdin);
	postalCheck = validatePostalCode(buffer[5]);


	printf("Phone Number: \n");
	fgets(buffer[6], 12, stdin);
	phoneCheck = validatePhone(buffer[6]);

	//Call a function that takes in all the info and displays and gets a confirmation from the user
	entryStatus = validateUserEntries(nameCheck, addressCheck, cityCheck, provinceCheck, postalCheck, phoneCheck);

	//Confirm that none of the validation checks returned 1. If so, throw error and begin again.
	if (entryStatus == 1) {
		printf("One or more of the entries was invalid. Please try again.\n");
		return;
	}

	//Append it to the new entry
	strcpy(newEntry->name, buffer[1]);
	strcpy(newEntry->address, buffer[2]);
	strcpy(newEntry->city, buffer[3]);
	strcpy(newEntry->province, buffer[4]);
	strcpy(newEntry->postalCode, buffer[5]);
	strcpy(newEntry->phone, buffer[6]);;

	//Add it to the array
	EntryList[*entryCount] = newEntry;	

	//Increament the counter. 
	*entryCount++;

	//Testing here after regex library convo
	printf("Name: %s\n", newEntry->name);	
}

bool validateName(char* buffer) {
	std::regex nameRegex ("^[A-Za-z' -]{1,30}$");
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
	std::regex provRegex("^[A-Z{2}$");
	if (std::regex_match(province, provRegex)) {
		return true;
	}
	else {
		return false;
	}
}

bool validatePostalCode(char* postalCode) {
	std::regex postalRegex("^[A-Z]\\d[A-Z] \\d[A-Z]\\d$");
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

bool validateUserEntries(bool nameCheck, bool addressCheck, bool cityCheck, bool provinceCheck, bool postalCheck, bool phoneCheck) {
	if (nameCheck == true && addressCheck == true && cityCheck == true && provinceCheck == true && postalCheck == true && phoneCheck == true) {
		return 0;
	}
	else {
		return 1;
	}
}

void enterCheck(char* buffer) {
	if (buffer[1] == '\n') {
		printf("Enter was pressed. Returning back to main menu....");
		return;
	}
}

void mainMenu(void) {
	printf("========== MAIN MENU ==========\n");
	printf("1. Add Entry\n");
	printf("2. Display Entries\n");
	printf("3. Exit the program\n");
	printf("===============================\n");
}