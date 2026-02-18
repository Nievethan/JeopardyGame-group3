/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Copyright (C) 2026, <GROUP NUMBER 3>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"
#include <ctype.h>

#define BUFFER_LEN 256
#define NUM_PLAYERS 4


static void trim_newline(char *s)
{
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

void tokenize(char *input, char **tokens){ // Extracts the actual answer after "what is?" or "Who is"
  tokens[0] = NULL;
  if(!input) return;

  while(*input && isspace((unsigned char)*input))//Removing leading spaces
    input++;

  char temp[BUFFER_LEN];
  strncpy(temp, input, BUFFER_LEN-1);
  temp[BUFFER_LEN - 1] = '\0';


  for(int i= 0; temp[i]; i++)
    temp[i] = (char)tolower((unsigned char)temp[i]);

  if (strncmp(temp, "what is", 7) == 0)
        input += 7;

  else if (strncmp(temp, "who is", 6) == 0)
    input += 6;
  else
    return;

  while (*input && isspace((unsigned char)*input))
    input++;

  tokens[0] = input;
}

static int unanswered_count(void)
{
    int count = 0;

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (!questions[i].answered)
            count++;
    }

    return count;
}






// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players){
  player sorted[NUM_PLAYERS];

    for (int i = 0; i < num_players; i++)
        sorted[i] = players[i];

    // bubble sort descending
    for (int i = 0; i < num_players - 1; i++){
        for (int j = 0; j < num_players - 1 - i; j++){
            if (sorted[j].score < sorted[j + 1].score){
                player temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
  }
  printf("\n=== FINAL RESULTS ===\n");
    for (int i = 0; i < num_players; i++)
        printf("%d) %s - %d\n", i + 1, sorted[i].name, sorted[i].score);
}

static int question_exists(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 &&
            questions[i].value == value)
        {
            return 1;  // found
        }
    }
    return 0;  // not found
}

int main(void){
   player players[NUM_PLAYERS];

    // Input buffer
    char buffer[BUFFER_LEN] = {0};

    // Initialize questions
    initialize_game();

    // Gets players names
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        printf("Enter player %d name: ", i + 1);
        fgets(buffer, BUFFER_LEN, stdin);

        // remove newline
        buffer[strcspn(buffer, "\n")] = '\0';

        strncpy(players[i].name, buffer, MAX_LEN - 1);
        players[i].name[MAX_LEN - 1] = '\0';
        players[i].score = 0;
    }

    // Main loop
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        //Checks if game is over
        int remaining = 0;
        for (int i = 0; i < NUM_QUESTIONS; i++)
        {
            if (!questions[i].answered)
                remaining++;
        }

        if (remaining == 0)
        {
            printf("\nAll questions have been answered!\n");
            break;
        }

        char picker[BUFFER_LEN];
        char category[BUFFER_LEN];
        char value_str[BUFFER_LEN];
        int value;

        display_categories();

        printf("\nPicker name: ");
        fgets(picker, BUFFER_LEN, stdin);
        picker[strcspn(picker, "\n")] = '\0';

        if (!player_exists(players, NUM_PLAYERS, picker))
        {
            printf("Invalid player name.\n");
            continue;
        }
        printf("Category: ");
        fgets(category, BUFFER_LEN, stdin);
        category[strcspn(category, "\n")] = '\0';

        printf("Value : ");
        fgets(value_str, BUFFER_LEN, stdin);
        value_str[strcspn(value_str, "\n")] = '\0';

        value = atoi(value_str);


        if (!question_exists(category, value)){
          printf("Invalid category or value.\n");
          continue;
        }

        if (already_answered(category, value))
        {
            printf("That question has already been answered.\n");
            continue;
        }

        display_question(category, value);

        // Gets Answer
        printf("Answer (start with 'what is' or 'who is'): ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        char *tokens[2] = {0};
        tokenize(buffer, tokens);

        if (!tokens[0])
        {
            printf("Invalid answer format.\n");
            continue;
        }

        // Checks Answer
        if (valid_answer(category, value, tokens[0]))
        {
            printf("Correct! +%d\n", value);
            update_score(players, NUM_PLAYERS, picker, value);
        }
        else
        {
            printf("Incorrect.\n");
        }
    }

    //Final rankings
    show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}
