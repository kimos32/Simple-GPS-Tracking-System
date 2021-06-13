#include "coord.c"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int latDDI;                             //Integer part of the latitude
int lgDDI;                              //Integer part of the longitude
double latDDF;                          //Fraction part of the latitude
double latDD;                           //Final Latitude in DD form
double lgDDF;                           //Fraction part of the longitude
double lgDD;                            //Final Longitude in DD form
double lat2;                            //latitude as double 
double lg2;                             //longitude as double
double old_lat = 0;
double old_lg = 0;
double Distance_lat;
double Distance_lg;
int Distance = 0;
//int distlg;
//int distlat;
char *ptrt;
char *ptrg;
int travel;                             //distance counter
double a;                               //temp variable to convert to meters
double c;                               //temp variable to convert to meters


void convert(void){

if (quality == 'A'){                //checks if the data is valid; if it's not it calls gps() for new data

    lat2 = strtod(lat, &ptrt);          //converts latitude and longitude from char to double
    lg2 = strtod(lg, &ptrg);
       


      latDDI = (lat2)/100;                  //takes the integer part of the latitude (Degrees)
      latDDF = ((lat2) - latDDI*100)/60;  //takes the fractional part of the latitude (Decimal Minutes)
      latDD = latDDI + latDDF;        //adds both to get the lattitude in DD form

      lgDDI = (lg2)/100;                    //takes the integer part of the longitude (Degrees)
      lgDDF = ((lg2) - lgDDI*100)/60;     //takes the fractional part of the longitude (Decimal Minutes)
      lgDD = lgDDI + lgDDF;           //takes the fractional part of the longitude (Decimal Minutes)

      latDD = latDD*100;
      lgDD = lgDD*100;

      Distance_lat = latDD - old_lat;
      old_lat = latDD ;
      //distlat = (int)((Distance_lat / 0.000001)*111.132)/1000;

      Distance_lg = lgDD - old_lg;
      old_lg = lgDD;
      //distlg = (int)((Distance_lg / 0.000001)*111.132)/1000;
  
  a = pow(sin(Distance_lat/2),2) + cos(old_lat)*sin(latDD) * pow(sin(Distance_lg),2); //converts position from DD to meters
  c = 2* asin(sqrt(a));
   travel = 6371 * c;

      //travel = sqrt((distlat)^2 + (distlg)^2);
      if( travel > 3) {gps();}
      else{

      Distance = Distance + travel;             //main distance counter
      }

}
else{
gps(); 
}
}