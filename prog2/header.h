
#ifndef PROG2_HEADER_H
#define PROG2_HEADER_H

#endif //PROG2_HEADER_H



// Constants used for calculations
#define OFFENSIVE_FACTOR 1.15
#define SPECIAL_TEAMS_FACTOR 1.22
#define HOME_FIELD_ADVANTAGE 1.2
#define OVERALL_FACTOR 1.15
#define OFFENSIVE_WEIGHT 0.30
#define DEFENSIVE_WEIGHT 0.24
#define SPECIAL_WEIGHT 0.17
#define HOME_WEIGHT 0.11
#define OVERALL_WEIGHT 0.13

#include <stdio.h>
#include <math.h>

//Function to read input data from a file
int getInput(FILE* input_file, char* home_team_name, int* HTO, int* HTD, int* HTS, int* HTH, int* HTC,
             char* visiting_team_name, int* VTO, int* VTD, int* VTS, int* VTR);

//Function to compute five different team strengths and advantages based on nne int input values
void computeStrength(int HTO, int HTD, int HTS, int HTH, int HTC, int VTO, int VTD, int VTS, int VTR,
                    double* home_Scoring_Strength, double* visiting_Scoring_Strength, double* special_Teams_Impact, double* home_Field_Advantage, double* visiting_Road_Strength);


//Computing score difference using function
int score_Difference(double home_strength, double visiting_strength, double special_teams_impact,
                             double home_field_advantage, double visiting_road_strength);

// Function to show output of game results
void outputResult(const char* home_team_name,const  char* visiting_team_name, int score_difference);

//Updating total statistics through function
void updateTotals(int* total_games, int* home_team_wins, int* total_score_difference, int score_difference);

//Function to calculate summary statistics
void calculate_Summary(int total_games, int home_team_wins, int total);

