/*
* FILE			: assignment4.h
* PROJECT		: SENG 1050 Assignment 4
* PROGRAMMER	: NICHOLAS REILLY
* FIRST VERSION	: 2025-04-02
* DESCRIPTION	: A program that allows the user to enter and validate personal information such as name, address, city, province, postal code, and phone number. The program also provides a menu for adding entries and displaying them.
* REFERENCING   : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc.
*/

#pragma once

//Libraries used
#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include <regex>

//Struct declaration for Entry
typedef struct {
	char name[32];
	char address[62];
	char city[62];
	char province[4];
	char postalCode[9];
	char phone[14];
} Entry;

//Function prototypes
void Run(void);
int GetValidIntegerInput(void);
void systemListen(void);
void clearBuffer(void);
void clearConsole(void);
void mainMenu(void);
void addEntry(Entry* EntryList, int* entryCount);
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


