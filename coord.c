#include "tm4c123gh6pm.h"


unsigned char Uart0GetCh (void);
unsigned char NMEA_DATA;                // for incoming serial data
int pos_cnt = 0;               //position counter
int lat_cnt = 0;               //latitude data counter
int lg_cnt = 0;                //longitude data counter
int com_cnt = 0;               //comma counter
char lat[20];                  //latitude array
char lg[20];                   //longitude array
int end  = 0;                  //indicate end of message
int check = 0;                 //GPS flag
char quality;                  //GPS fix

  void convert();



unsigned char Uart0GetCh (void)		// Read character from Serial Port   
{            
  while((UART1_FR_R & 0x10) != 0); 				// wait if the receive FIFO is empty
return (UART1_DR_R & 0xFF);
}

void gps()
{
    while(end == 0){
     
	    NMEA_DATA = Uart0GetCh();
        check = 1;
       if(NMEA_DATA =='$' && pos_cnt == 0)   // finding GPRMC header
         pos_cnt=1;
        if(NMEA_DATA =='G' && pos_cnt == 1)
            pos_cnt=2;
          if(NMEA_DATA =='P' && pos_cnt == 2)
              pos_cnt=3;
            if(NMEA_DATA =='R' && pos_cnt == 3)
                pos_cnt=4;
              if(NMEA_DATA =='M' && pos_cnt == 4)
                  pos_cnt=5;
                if(NMEA_DATA =='C' && pos_cnt == 5)
                    pos_cnt=6;
                  if(NMEA_DATA == ',' && pos_cnt == 6){   // count commas in message
                      com_cnt++;
                      check = 0;
       }
 
        if(com_cnt==2 && check == 1){
        quality =  NMEA_DATA;                //Detects if data is valid or not 
        check = 0;
       }

       if(com_cnt==3 && check == 1){
        lat[lat_cnt++] =  NMEA_DATA;         // Latitude
        check = 0;
       }
 
       if(com_cnt==5 && check == 1){
         lg[lg_cnt++] =  NMEA_DATA;         // Longitude
         check = 0;
       }


       
       if(NMEA_DATA == '*' && com_cnt >= 5 && check == 1){
         lat[lat_cnt] ='\0';             // end of GPRMC message
         lg[lg_cnt]  = '\0';
				 com_cnt = 0;                      // end of GPRMC message
         lat_cnt = 0;
         lg_cnt = 0;
         check     = 0;
         end  = 1;
 
      }

    }
 
   end = 0;
   pos_cnt = 0;

convert();
}

//$GPRMC,001225,A,2832.1834,N,08101.0536,W,12,25,251211,1.2,E,A*03
