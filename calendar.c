// Simple calendar
// Make a C script that returns a personal calendar
// 6/22/2022

#include <stdio.h>
#include <string.h>
#include <time.h>

// Note: year/month/date are 1-indexed, while wday is 0-indexed.
// This is because y/m/d are meant for humans to read.

// Print help
int help() {
  printf(
    "This is a simple program that prints a command-line calendar of the current month.\n"
    "Usage:\n"
    "date: enters a specific date and show that month.\n"
    "help: prints this help message.\n"
  );
}


// Print calendar framework
int printcalendar(int year, int month, int day, int wday) {

  // Get which weekday the first day of the month is, 0-indexed
  int startday = ((day - wday + 5) % 7);

  // Get how many totay days are there in month
  int monthlen = 30;
  int list_of_mo[] = {0, 2, 4, 6, 7, 9, 11};
  for (int i = 0; i < 7; i++) {
    if (list_of_mo[i] == month) {
      monthlen = 31;
      break;
    }
  }

  // Calendar, fixed header
  printf("\n"
  "       Y%d M%d\n"
  "-----------------------------\n"
  "| S | M | T | W | Th| F | Sa|\n"
  "-----------------------------\n"
  "|", 
  year, month);

  // Second part of calendar, print dates
  for (int pc = 0; pc < (monthlen + startday - 1); pc++) {
    // Print empty strings until the start of the month begins
    if (pc < (startday)) {
      printf("   |");
    }
    // Print date
    else {
      // Print an asterisk if it's today
      if (pc-startday+1 == day) {
        printf("*");
      }
      else {
        printf(" ");
      }
      // Print the actual date
      if (pc-startday < 9) {
        printf("%d |", pc-startday+1);
      }
      else {
        printf("%d|", pc-startday+1);
      }
    }
    // Break every 7 days
    if (pc % 7 == 6) {
      printf("\n-----------------------------\n|");
    }
  }
  // Wrap up the calendar
  printf(
    "\n-----------------------------\n",
    "\n\n"
  );
}


// Find current date and print
int currentdatecal() {
  // Capture the current time
  int day, wday, month, year;
  time_t now;
  time(&now);
  // Converts time_t value to calendar time
  // Note: everything except for wday is 1-indexed
  struct tm *local = localtime(&now);
  day = local->tm_mday;
  wday = local->tm_wday;
  month = local->tm_mon+1;
  year = local->tm_year + 1900;

  printf("The queried values are %d, %d, %d, and %d\n", year, month, day, wday);

  // Print calendar
  printcalendar(year, month, day, wday);
}


// Manually enter a date, find weekday, and print
int enterdatecal() {
  // Ask for current time
  int year, month, day, wday;
  printf("Enter current year: \n");
  scanf("%d", &year);
  printf("Enter current month: \n");
  scanf("%d", &month);
  printf("Enter current date: \n");
  scanf("%d", &day);
  // Find weekday info using math, 1-indexed
  int daycopy = day;
  wday = (day += month < 3 ? year-- : year - 2, 23*month/9 + day + 4 + year/4- year/100 + year/400)%7; 

  printf("Entered values are: %d, %d, %d, %d\n", year, month, daycopy, wday);
  // Print calendar
  printcalendar(year, month, daycopy, wday);
}


// Main 
int main(int argc, char *argv[]) {

  //printf("The number of arguments entered is %d\n", argc);
  //printf("The first argument is: %s\n", argv[1]);

  // Check if any arguments are entered; if not, modify
  if (argc == 1) {
    argc = 2;
    argv[1] = "none";
    //printf("Now there are %d arguments\n", argc);
  }
  // Check the arguments
  if ( ! strcmp(argv[1], "help")) {
    // Print the help statement
    help();
  }
  else if ( ! strcmp(argv[1], "date")) {
    // Query for date
    enterdatecal();
  }
  else {
    // Call the currentdatecal function
    currentdatecal();
  }
  return 0;
}
