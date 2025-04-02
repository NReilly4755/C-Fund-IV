#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include <regex.h>

typedef struct {
	char name[30];
	char address[60];
	char city[60];
	char province[2];
	char postalCode[7];
	char phone[12];
} Entry;

void Run(void);
int GetValidIntegerInput(void);
void systemListen(void);
void clearBuffer(void);
void clearConsole(void);


