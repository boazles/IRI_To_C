#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> 
#include <math.h>
#define PI 3.142857
extern void iri_sub_(int[] , int *, float *, float *, int *, int * , float *, float *, float *, float *, float[][20], float[]);
extern void iri_web_(int[] , int *, float *, float *, int *, int * , float *,float *, int * , int * ,int *, float *, float *, float *, float[][20], float[]);

int main(int c, char* argv[])
{
    int index = 0;
    if (c==2)
        index = atoi(argv[1]);
    else
    {
       printf("error: missing arguement or too many command line arguments , usage: ./run 1 or ./run 2 \n");
        return -1;
    }
    int line_count = 0;
    
    int jf[50]={true,true,true,false,false,
                false,true,true,true,true, 
                true,true,true,true,true,
                true,true,true, true,true,
                false,true, false,true,true,
                false, true,false,false,false, 
                true,true,false,true, false,
                true,true,true, false,true,
                true,true,true, true,true,
                true,false, true,true, true};
   
    int jmag;
    float alati;
    float along;
    int iyyy;
    int mmdd;
    float dhour;
    float begin;
    float end;
    float step;
    float oarr[100];
    float out[1000][20];
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    float height =100; // height in km to intialize iri_web
    int h_tec_max  =0; //no TEC otherwise upper boundary for integral
    int  iut=1;// for UT       =0 for LT
    int ivar =1; 
    char file_name[10] ;
    sprintf(file_name, "%s%d", "params", index);
    fp = fopen(file_name, "r");
    if (fp != NULL)
    {

        while ((read = getline(&line, &len, fp)) != -1) 
        {
                printf("Retrieved line of length %zu:\n", read);
                //printf("%s\n", line);
                if (line_count==0) // works only for iri_sub_ can be easily adjusted for iri_web_
                {
                    jmag== atoi(line); //=0/1,geog/geom  coordinates could use bool
                    printf("jmag is %d\n", jmag);
                }
                else if (line_count==1)
                {
                    alati= atof(line); // latitude
                }
                else if (line_count==2)
                {
                    along = atof(line);  // longitude
                }
                else if (line_count==3)
                {
                    iyyy = atoi(line);  //year in yyyy format
                }
                else if (line_count==4)
                {
                    mmdd = atoi(line);  // Month and  days could use day of year (Julian date)
                }
                else if (line_count==5) 
                {
                    dhour =atof(line);  // Hour at UTC
                }
                else if (line_count==6)
                {
                    begin =atof(line); // start latitude KM
                }
                else if (line_count==7)
                {
                    end =atof(line);  // End latitude KM
                }
                else if (line_count==8)
                {
                    step =atof(line); // Sampling step number of steps cannot exceed 1000
                }
                line_count++;
            }
            fclose(fp);
            int month = floor(mmdd/100); // formatting graph
            int day = mmdd%100;
            char date[100];
            int minutes = floor(fmodf(dhour, floor(dhour))*60);
            char min[3];
            if (minutes >=10)
                sprintf(min,"%d",  minutes);
            else
                sprintf(min, "%d%d", 0, minutes);
            char mon[20];
            if ((int)month== 1)
                sprintf(mon , "January");
            if ((int)month== 2)
                sprintf(mon , "February");
            if ((int)month== 3)
                sprintf(mon , "March");
            if ((int)month== 4)
                sprintf(mon , "April");
            if ((int)month== 5)
                sprintf(mon , "May");
            if ((int)month== 6)
                sprintf(mon , "June");
            if ((int)month== 7)
                sprintf(mon , "July");
            if ((int)month== 8)
                sprintf(mon , "August");
            if ((int)month== 9)
                sprintf(mon , "September");
            if ((int)month== 10)
                sprintf(mon , "October");
            if ((int)month== 11)
                sprintf(mon , "November");
            if ((int)month== 12)
                sprintf(mon , "December");
            sprintf(date, "%s %d %d %d:%s", mon, day ,iyyy, (int)dhour, min );
            printf("%s\n", date);
            printf("%i, %f, %f,%i, %i, %f, %f, %f, %f\n", jmag, alati, along, iyyy,mmdd,dhour, begin, end, step);
            //iri_web_(jf, &jmag, &alati, &along, &iyyy, &mmdd , &dhour,&height , &h_tec_max,&iut, &ivar, &begin , &end, &step,  out, oarr);
            iri_sub_(jf, &jmag, &alati, &along, &iyyy, &mmdd , &dhour, &begin , &end, &step,  out, oarr);
            printf("computed iri model\n");
            FILE * dPtr;
            char rawdata[20];
            sprintf(rawdata, "%s", "output.dat");
            dPtr = fopen(rawdata, "w");
            for (int i = 0 ; i<1000 ;i++)
            {
                    if (out[i][0]!=-1.0)
                    {
                        fprintf(dPtr,"%f ",out[i][0]);
                        fprintf(dPtr,"%f",begin+i*step);
                        fprintf(dPtr,"\n");
                    }
            }
            /* File pointer to hold reference to our file */
            FILE * fPtr;
            /* 
            * Open file in w (write) mode. 
            */
            char outfile[20];
            sprintf(outfile, "%s%d%s", "output", index , ".dat");
            fPtr = fopen(outfile, "w");
            printf("saving the iri model to %s\n", outfile);

            /* fopen() return NULL if last operation was unsuccessful */
            if(fPtr == NULL)
            {
                /* File not created hence exit */
                printf("Unable to create file.\n");
                exit(EXIT_FAILURE);
            }

            float sun_spot = oarr[32]; // 12-month running mean of sunspot number from model

            float fact = 1.6*10E-19/sqrt(8.85*10E-12*9.1*10E-31); // change from density to frequency using the oscilator formula wp = sqrt(n*e^2/(eo*me)) using permittivity of free space
            for (int i = 0 ; i<1000 ;i++)
            {
            
                for (int j =0 ; j<1 ; j++)
                {
                    if (out[i][j]!=-1.0)
                    {
                        fprintf(fPtr,"%f ",fact*sqrt(out[i][j])/(2*PI*1000000));
                        fprintf(fPtr,"%f",begin+i*step);
                        fprintf(fPtr,"\n");
                    }
                }
            }
            

            /* Close file to save file data */
            fclose(fPtr);


            /* Success message */
            printf("File created and saved successfully. :) \n");
            //plot via GnuPlot
            int NUM_COMMANDS = 4;
            char title[400];
            char st[20]= " EDP for";
            char beg[20] = "set title \"";
            char utc[10] = "\'";
            char end[50] = "UTC with sun spot number ";
            sprintf (title , "%s%s %s %s %d ",beg, st, date, end, (int)sun_spot);
            //printf( "%s\n", title);
            char fl[50];
            char pl[20] = "plot \'";
            sprintf (fl , "%s%s%s"  , pl, outfile, utc);
            //printf("%s\n", title);
            //printf("%s\n", fl);
            char * commandsForGnuplot[] = {title, "set xlabel \"Plasma Frequency (MHz)\"", "set ylabel \"Altitude (Km)\"",fl};
            FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
            for (int i=0; i < NUM_COMMANDS; i++)
            {
                fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
            }
       }
   return 0;
}