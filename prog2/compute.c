#include "header.h"

//Calculating computeStrengthFunction based on various factors passing them as parameters.
//We pass 9 input int values here which are HTO, HTD, HTS, HTH, HTC, VTO, VTD, VTS and VTR.
// Using these int values, we calculate five relative team strengths of both teams as doubles in the function below.
//HTO stands for home team offensive strength while HTD for home team defensive strength.
// HTS is special team strength for home team and HTH is home team home strength, HTC is home team advantage in crowd noise.
//VTO and VTD are visiting team offensive and defensive strength respectively
//VTS is  visiting team special strength and VTR is visiting team road advantage.
//We get these values ranging from 1(worst) to 10(best) .
void computeStrength(int HTO, int HTD, int HTS, int HTH, int HTC, int VTO, int VTD,
 int VTS ,int VTR, double* home_Scoring_Strength, double* visiting_Scoring_Strength, double* special_Teams_Impact, double* home_Field_Advantage, double* visiting_Road_Strength){
    // Calculate home scoring strength based on HTO and VTD
    *home_Scoring_Strength = HTO * OFFENSIVE_FACTOR - VTD;

    // Calculate visiting scoring strength based on HTD , VTO and OFFENSIVE_FACTORr
    *visiting_Scoring_Strength = HTD + 2 - VTO * OFFENSIVE_FACTOR;

    //Calculating specialteamimpact based on HTS, specialteamfactor and VTS
    *special_Teams_Impact = HTS * SPECIAL_TEAMS_FACTOR - VTS;

    //calculating home field advantage based on HTH, HTC, HOME_FIELD_ADVANTAGE and VTS
    *home_Field_Advantage = HTH + HTC * HOME_FIELD_ADVANTAGE - VTS;

    //Calculate visiting road strength based on HTO, HTD, HTH, VTO, VTD, VTR and OVERALLL_FACTOR
    *visiting_Road_Strength = (HTO * HTD * HTH * OVERALL_FACTOR )- (VTO * VTD * VTR);

//OFFENSIVE_FACTOR, SPECIAL_TEAMS_FACTOR, HOME_FIELD_ADVANTAGE and OVERALL_FACTOR are constant values defined in header file.

}

// Calculating score difference passing home_Scoring_Strength, visiting_Team_Strength, special_Teams_Impact, home_field_advantage and visiting_Road_Strength as parameters
int score_Difference(double home_Scoring_Strength, double visiting_Team_Strength, double special_Teams_Impact,
                     double home_field_advantage, double visiting_road_strength) {
    return (int)(home_Scoring_Strength * OFFENSIVE_WEIGHT + visiting_Team_Strength * DEFENSIVE_WEIGHT +
                        special_Teams_Impact * SPECIAL_WEIGHT + home_field_advantage * HOME_WEIGHT +
                        visiting_road_strength * OVERALL_WEIGHT);

//returning  score_difference as int value;

}



