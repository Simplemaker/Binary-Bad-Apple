
// Binary Video Viewer
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

extern unsigned char Bad_Apple_bin[12618240];

#define WIDTH 80
#define HEIGHT 24
#define INCREMENT 1920

char* colorScale = " .\'`^\",:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
unsigned colorScaleSize = 69;

// *  ESC [ 1 J 
char* clear = "\x1b[1J";

// *  ESC [ pl ; pc H
char* home = "\x1b[0;0H";


char* clearline = "\x1b[2K";

float timedifference_msec(struct timeval* t0, struct timeval* t1)
{
    return (t1->tv_sec - t0->tv_sec) * 1000.0f + (t1->tv_usec - t0->tv_usec) / 1000.0f;
}

void displayFrame(unsigned long position){
    printf("%sDisplaying frame %ld\n",clearline , position / INCREMENT);
    for(int h = 0; h < HEIGHT; ++h){
        for(int w = 0; w < WIDTH; ++w){
            int color = Bad_Apple_bin[position++];
            int color2 = color * colorScaleSize / 256;
            printf("%c", colorScale[color2]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    unsigned long position = 0;
    struct timeval start, current;
    struct timespec ts;
    ts.tv_sec = 0;
    gettimeofday(&start, 0);
    gettimeofday(&current, 0);
    while(position < sizeof(Bad_Apple_bin) / INCREMENT){
        displayFrame(position * INCREMENT);
        ++position;
        gettimeofday(&current, 0);
        unsigned wait_time_ms = position * 1000.0 / 30.0 - timedifference_msec(&start, &current);
        ts.tv_nsec = 1000000 * wait_time_ms;
        nanosleep(&ts, &ts);
        printf("%s", home);
        
    }
}