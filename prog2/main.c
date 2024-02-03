/*
Name: Suman Bhandari
CSC 362 Programming Assignment 2
Date: Oct 6, 2023

In this program,we predict the outcome of football game based on input data from a file.
The program calculates teams' strength using various factors and predict which team will win by how many points.
It also keeps track of stats like average difference in score and  percentage of team win.
The program is divided into three different parts for reading data, making calculation, getting input and displaying output and a header.h file to
declare constant, data types, library declaration.
 1:Reading Data: We gather data for upcoming football games from an input file, including team details and performance metrics.
 2: Calculations: Using this data, the program computes strengths and advantages of the teams, like their scoring abilities, and home-field advantage, following predefined formulas.
 3:Outcome Prediction: Based on these calculations, the program forecasts the winning team and the point difference. It also tracks statistics,
      like the average scoring difference and the percentage of home team wins.
      For this it is separated into different files which are main.c, compute.c, header.c and io.c.
-main.c : It contains the main function, which helps the program by reading data, making calculations, and displaying predictions and summaries.
-compute.c: This file contains the  computational functions responsible for calculating team strengths and predicting outcomes.
-io.c: This file handles input, output, and summary functions. It reads input data from the file, displays the results of game predictions, and calculates summary statistics.
-header.h: Header file that declares constants, data types, library inclusions, and function prototypes used across the program.
 The program utilizes parameter passing and show effective data sharing between functions.
It correctly predicts football game results by effectively passing parameters between its parts and functions, following a well-organized method.


 */
#include "header.h"   //include header file which contains function prototypes, constants

int main() {
    //Declaring variable for input file , total no. of games, team wins and total score difference and score difference.
    char filename1[100];   //limiting maximum no. of character to 100
    int total_games = 0;
    int home_team_wins = 0;
    int total_score_difference = 0;
    int scoreDifference;

    double home_Scoring_Strength, visiting_Scoring_Strength, special_Teams_Impact, home_Field_Advantage, visiting_Road_Strength;
    FILE* input_file;          //File pointer for input file

    //Asking user to input the filename
    printf("Enter the input filename: ");
    scanf("%s", filename1);

    //Opening the input file
    input_file = fopen(filename1, "r");

    //Testing if file is opened properly
    if (input_file == NULL) {
        printf("Error: File not found.\n");
        return 1;      //Exiting program with an error code
    }

    char home_team_name[20];        // limiting home team name to just 20 characters
    int HTO, HTD, HTS, HTH, HTC, VTO, VTD, VTS, VTR;
    char visiting_team_name[20];     //limiting away team name to just 20 characters

    //Reading data from the input file until the end of the file using while loop. Int value is retured by fscanf from io file to determine the continuity of loop.
    while (getInput(input_file, home_team_name, &HTO, &HTD, &HTS, &HTH,
                    &HTC, visiting_team_name, &VTO, &VTD, &VTS, &VTR) != EOF) {

        //Computing various team strengths and score_differences

        computeStrength(HTO, HTD, HTS, HTH, HTC, VTO, VTD, VTS, VTR, &home_Scoring_Strength, &visiting_Scoring_Strength, &special_Teams_Impact, &home_Field_Advantage, &visiting_Road_Strength);

        scoreDifference = score_Difference(home_Scoring_Strength, visiting_Scoring_Strength, special_Teams_Impact,
                                           home_Field_Advantage, visiting_Road_Strength);

        //Output result of the file
        outputResult(home_team_name, visiting_team_name, scoreDifference);

        // Updating teh statistics for calculate summary
        updateTotals(&total_games, &home_team_wins, &total_score_difference, scoreDifference);
    }
    fclose(input_file);    //closing the input file
     //Showing the calculation summary of results.
    calculate_Summary(total_games, home_team_wins, total_score_difference);
    return 0;   //Exiting the program returning 0
}

/*
 * Output for testcase 2
 *
/Users/sumanbhandari/Desktop/workspace/prog2/cmake-build-debug/prog2
Enter the input filename: football2.txt
Clemson beats Wake_Forest by 2
Florida_St beats Virginia_Tech by 11
Nebraska beats Illinois by 3
Iowa_St beats TCU by 1
Georgia beats Kentucky by 19
Notre_Dame beats Louisville by 4
Michigan beats Minnesota by 8
LSU beats Missouri by 4
Ohio_State beats Maryland by 21
Oklahoma_St beats Kansas_St by 6
Texas beats Oklahoma by 3
USC beats Arizona by 8
Wisconsin beats Rutgers by 4

Percentage of home team wins is predicted as 69.23%
Average difference in scores is predicted as 4.23

Process finished with exit code 0


 */
