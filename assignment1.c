/* Maths quiz game 
 * Generates random questions for a user to answer
 * and records the score of each round.
 * User can set number of questions per round,
 * start a round, or display score of previous round.
 * 
 * OS: Linux Mint 17.2 Rafaela
 * Compiled using GCC version 4.84
 * Author: Pádraig Redmond C15755659
 * Last updated: 10/11/15
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUESTIONS 5
#define DIFFICULTY 10

void flush_buffer();
int generate_question();

int main()
{
	int option, right, wrong, user_answer, answer, questions_remaining;
	int num_questions =  0, start_quiz = 0, quiz_played = 0;
	
	// seed the random number generator using current time
	srand(time(NULL));
	
	do
	{
		// Have to reset option at the start of the loop,
		// otherwise the program will reuse the previous input
		// if incorrect input is given
		//
		option = 0;
		
		printf("-------------------------------------------\n");
		printf("1. Enter number of questions for this round\n");
		printf("2. Start quiz\n");
		printf("3. Display score from last round\n");
		printf("4. Exit Program\n");
		scanf("%d",&option);
		flush_buffer();
		
		// 1-4 is only accepted input
		//
		while(option < 1 || option > 4)
		{
			printf("ERROR: Invalid input, try again\n");
			scanf("%d",&option);
			flush_buffer();
		}
		
		switch(option)
		{
			// Set number of questions,
			// must be between 1 and 5
			//
			case 1:
			{
				printf("Number of questions (1-5): ");
				scanf("%d",&num_questions);
				flush_buffer();
				while(num_questions < 1 || num_questions > MAX_QUESTIONS)
				{
					printf("ERROR: Choose between 1-%d questions:",MAX_QUESTIONS);
					scanf("%d",&num_questions);
					flush_buffer();
				}
				break;
			}
			
			// Start the quiz.
			// Resets the answer totals, and sets the start_quiz
			// flag to 1. Won't let you start if you haven't set
			// the number of questions
			//
			case 2:
			{
				if(num_questions != 0)
				{
					right = 0;
					wrong = 0;
					start_quiz = 1;
				}
				else
				{
					printf("ERROR: You must specify the number of questions before starting the quiz\n");
				}
				break;
			}
			
			// Print score from last round.
			// Only works if you've played at least 1 quiz
			//
			case 3:
			{
				if(quiz_played)
				{
					printf("You got %d right and %d wrong\n",right,wrong);
				}
				else
				{
					printf("ERROR: You haven't played the quiz yet!\n");
				}
				break;
			}
			
			default:
				break;
		}//end switch
		
		// Enter here if the user has requested the quiz to start
		//
		if(start_quiz == 1)
		{
			// This lets the game know it can display scores
			//
			quiz_played = 1;
			
			// Using questions_remaining variable to store the number of questions
			// so that num_questions can be reused for the next quiz if needs be
			//
			questions_remaining = num_questions;
			
			printf("\n--------------\n");
			printf("| Maths Quiz |");
			printf("\n--------------\n");
			
			while(questions_remaining != 0)
			{
				// Ask a randomly generated question, check user's answer 
				// against the valid answer and update score
				//
				answer = generate_question();
				scanf("%d",&user_answer);
				flush_buffer();
				printf("You entered: %d - ",user_answer);
				
				if(user_answer == answer)
				{
					printf("Correct!\n");
					right++;
				}
				else
				{
					printf("Wrong !! The correct answer: %d\n",answer);
					wrong++;
				}
				
				questions_remaining--;
			}
			
			// reset the quiz flag after quiz ends
			start_quiz = 0;
		}//end if
		
		
		printf("\n");
	}
	while(option != 4);
	
	return 0;
}

// Function to clear the input buffer.
// Prevents '\n' being read as input
//
void flush_buffer()
{
	char c;
	while((c = getchar()) != '\n')
	{
		// discarding input
	}
}

// randomly generates and prints a question
// based on DIFFICULTY, and returns the answer
//
int generate_question()
{
	int num1, num2, operator;
	char operators[3] = {'+','-','*'};
	
	num1 = rand()%(DIFFICULTY-1) + 1;
	num2 = rand()%(DIFFICULTY-1) + 1;
	operator = rand()%3;
	
	printf("%d %c %d = ",num1, operators[operator], num2);
	
	switch(operator)
	{
		case 0:
			return num1+num2;
		case 1:
			return num1-num2;
		case 2:
			return num1*num2;
	}
}

