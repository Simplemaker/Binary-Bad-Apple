
// Binary Video Viewer
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

extern unsigned char out_data[];
extern unsigned long out_end;
extern void decompress(void);

#define WIDTH 40
#define HEIGHT 24
#define INCREMENT 960

// 16 color grayscale
char* colorScale = " .:-~=+ozO0Z#8%@";

// ESC [ 1 J 
char* clear = "\x1b[1J";

// ESC [ pl ; pc H
char* home = "\x1b[0;0H";

// ESC [ 2 K
char* clearline = "\x1b[2K";

float timedifference_msec(struct timeval* t0, struct timeval* t1)
{
    return (t1->tv_sec - t0->tv_sec) * 1000.0f + (t1->tv_usec - t0->tv_usec) / 1000.0f;
}

void displayFrame(unsigned long position){
    printf("%sDisplaying frame %ld\n",clearline , position / INCREMENT);
    for(int h = 0; h < HEIGHT; ++h){
        for(int w = 0; w < WIDTH; ++w){
            unsigned char colors = out_data[position++];
            printf("%c%c", colorScale[0x0f & colors], colorScale[colors / 0x10]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    unsigned long position = 0;
    struct timeval start, current;
    struct timespec ts;

    decompress();
    ts.tv_sec = 0;
    gettimeofday(&start, 0);
    gettimeofday(&current, 0);
    while(position < out_end / INCREMENT){
        displayFrame(position * INCREMENT);
        ++position;
        gettimeofday(&current, 0);
        unsigned wait_time_ms = position * 1000.0 / 30.0 - timedifference_msec(&start, &current);
        ts.tv_nsec = 1000000 * wait_time_ms;
        nanosleep(&ts, &ts);
        printf("%s", home);
        
    }
}