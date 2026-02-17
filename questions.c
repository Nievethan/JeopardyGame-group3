/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Copyright (C) 2026, <GROUP 3>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void) {
	// Programming questions
	questions[0] = (question){
		"programming",
		"The standard library header file required to use the printf function.",
		"stdio.h",
		200,
		false
	};

	questions[1] = (question){
		"programming",
		"A variable that stores the memory address of another variable.",
		"pointer",
		400,
		false
	};

	        questions[2] = (question){
                "programming",
                "A user-defined data type in C that groups related variables of different types.",
                "struct",
                600,
                false
        };

        questions[3] = (question){
                "programming",
                "This keyword is used to return a value from a function."
,
                "return",
                800,
                false
        };

	// Algorithm questions
	 questions[4] = (question){
                "algorithms",
                "A simple sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.",
		"bubble sort",
		200,
                false
        };

        questions[5] = (question){
                "algorithms",
                "A search algorithm that finds the position of a target value within a sorted array by reapeatedly dividing the search interval in half",
                "binary search",
                400,
                false
        };
	
	questions[6] = (question){
                "algorithms",
                "A linear data structure that follows the Last In, First Out(LIFO) principle",
		"stack",
                600,
                false
        };

        questions[7] = (question){
                "algorithms",
                "A problem-solving method where the solution depends on solutions to smaller instances of the same problem (often calls itself).",
                "recursion",
                800,
                false
        };

	// Database questions
        questions[8] = (question){
                "databases",
                "The standard language used to communicate with and manipulate relational databases.",
		"SQL",
                200,
                false
        };

        questions[9] = (question){
                "databases",
                "A column or group of columns that uniquely identifies every row in a table.",
		"primary key",
                400,
                false
        };
	
	questions[10] = (question){
                "databases",
                "The SQL command used to retrieve specific data from a database.",
                "SELECT",
                600,
                false
        };

        questions[11] = (question){
                "databases",
                "The acronym for the four properties that guarantee database transactions are processed reliably: Atomicity, Consistency, Isolation, Durability"
,
                "ACID",
                800,
                false
        };
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {

    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
