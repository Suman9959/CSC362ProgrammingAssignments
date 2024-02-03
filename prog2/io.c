#include "header.h"
#include <stdio.h>    // provides function like printf and scanf
#include <stdlib.h>    //includes abs function(for getting absolute value)

// Reading input data for a single game from the file and return the number of items read
int getInput(FILE* input_file, char* home_team_name, int* HTO, int* HTD, int* HTS, int* HTH, int* HTC,
             char* visiting_team_name, int* VTO, int* VTD, int* VTS, int* VTR) {
    return fscanf(input_file, "%s %d %d %d %d %d %s %d %d %d %d",
                  home_team_name, HTO, HTD, HTS, HTH, HTC,
                  visiting_team_name, VTO, VTD, VTS, VTR);
}
// Outputing the game prediction results, considering score differences
void outputResult(const char* home_team_name, const char* visiting_team_name, int score_difference) {
    if (score_difference > 0) {
        printf("%s beats %s by %d\n", home_team_name, visiting_team_name, score_difference);
    } else if (score_difference < 0) {
        printf("%s beats %s by %d\n", visiting_team_name, home_team_name, abs(score_difference));
    } else {
        // If the point differential is 0, the home team wins by 1 point
        printf("%s beats %s by 1\n", home_team_name, visiting_team_name);
    }
}


// Update running totals based on game predictions
void updateTotals(int* total_games, int* home_team_wins, int* total_score_difference, int score_difference) {
    (*total_games)++;              //incrementing total_games

    // If the score difference is non-negative, it indicates a home team win.
    // Incrementing the total number of home team wins accordingly.
    if (score_difference >= 0) {
        (*home_team_wins)++;
    }
    // Update the total computed score differences
    *total_score_difference += score_difference;
}
// Calculating and displaying  summary of all predictions
void calculate_Summary(int total_games, int home_team_wins, int total_score_difference) {
    double percentage = ((double)home_team_wins / total_games) * 100;
    double average_score_difference = (double)total_score_difference / total_games;     //average score difference calculation


    //Output of summary results
    printf("\n");
    printf("Percentage of home team wins is predicted as %.2f%%\n", percentage);
    printf("Average difference in scores is predicted as %.2f\n", average_score_difference);
}
