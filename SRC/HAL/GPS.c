#include "../../SERVICES/tm4c123.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../HEADERS/HAL/GPS.h"
#define pi 3.14159265358979323846
const double Earth_radius =6371000;



void extract_lat_lon(char *gprmc_sentence, float *latitude, float *longitude) {
    // Check if the sentence starts with "$GPRMC" and has at least 8 parts
    char *comma1 = strchr(gprmc_sentence, ',');
    char *comma2 = strchr(comma1 + 1, ',');
    char *comma3 = strchr(comma2 + 1, ',');
    char *comma4 = strchr(comma3 + 1, ',');
    char *comma5 = strchr(comma4 + 1, ',');
    char *comma6 = strchr(comma5 + 1, ',');
    char lat_dir;
    char lon_dir;

    if (comma1 && comma2 && comma3 && comma4 && comma5 && comma6) {
        // Extract latitude and longitude
        char lat_deg_str[10];
        char lon_deg_str[10];

        // Copy the substrings into null-terminated buffers
        strncpy(lat_deg_str, comma3 + 1, comma4 - comma3 );
        lat_deg_str[comma4 - comma3 - 1] = '\0';  // Null-terminate the string
        strncpy(lon_deg_str, comma5 + 1, comma6 - comma5 );
        lon_deg_str[comma6 - comma5 - 1] = '\0';  // Null-terminate the string

        // Convert to floating-point values
        *latitude = atof(lat_deg_str);
        *longitude = atof(lon_deg_str);

        // Adjust for South or West direction if needed
        if (lat_dir == 'S' || lat_dir == 's') {
            *latitude *= -1;
        }
        if (lon_dir == 'W' || lon_dir == 'w') {
            *longitude *= -1;
        }
    } else {
        // Invalid GPRMC sentence
        *latitude = 0.0f;
        *longitude = 0.0f;
    }
}




//*function to convert GPS values to degree*//
float ToDegree(double val) {
    double result=0;
    int degree = (int)val / 100;
    double minutes = val-(double)degree*100;
    result = degree+ (minutes/60);
    return result;
}
//*function to Convert Degree to Rad*//
float convert_to_Rad(double degree) {
    return degree * (pi / 180.0);
}
//*function to calculate distance between two locations using longitude and latitude in Radians*//
//  Haversine formula: a = sin (?f/2) + cos f1   cos f2   sin (??/2)
//  c = 2 * atan2(sqrt(a), sqrt(1 - a))
// distance = Earth radius *c
double GPS_calc_distance(double current_Lat,double current_Long,double previous_Lat,double previous_Long){
    double prev_lat_rad = convert_to_Rad(ToDegree(previous_Lat));
    double prev_long_rad = convert_to_Rad(ToDegree(previous_Long));
    double current_lat_rad = convert_to_Rad(ToDegree(current_Lat));
    double current_long_rad = convert_to_Rad(ToDegree(current_Long));
    double lat_diff = current_lat_rad - prev_lat_rad;
    double long_diff = current_long_rad - prev_long_rad;

    double a= sin(lat_diff/2)*sin(lat_diff/2)+ cos(prev_lat_rad)*cos(current_lat_rad)*sin(long_diff/2)*sin(long_diff/2); // Haversine formula: a = sin (?f/2) + cos f1   cos f2   sin (??/2)
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return (Earth_radius*c);   //distance in meters
}
