void extract_lat_lon(char *gprmc_sentence, float *latitude, float *longitude);
float ToDegree(double val);
float convert_to_Rad(double degree);
double GPS_calc_distance(double current_Lat,double current_Long,double previous_Lat,double previous_Long);
