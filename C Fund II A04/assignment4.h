#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include <regex>

typedef struct {
	char name[32];
	char address[62];
	char city[62];
	char province[4];
	char postalCode[9];
	char phone[15];
} Entry;

void Run(void);
int GetValidIntegerInput(void);
void systemListen(void);
void clearBuffer(void);
void clearConsole(void);
void mainMenu(void);
void addEntry(Entry** EntryList, int* entryCount);
bool validateName(char* buffer);
bool validateAddress(char* address);
bool validateCity(char* city);
bool validateProvince(char* province);
bool validatePostalCode(char* postalCode, int length);
bool validatePhone(char* phone);
void validateUserEntries(bool nameCheck, bool addressCheck, bool cityCheck, bool provinceCheck, bool postalCheck, bool phoneCheck);
bool enterCheck(char* buffer);
void displayEntries(Entry* EntryList, int entryCount);
void InitializeEntryList(Entry* EntryList);


