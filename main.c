
// Binary Video Viewer
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <zip.h>
#include <stdlib.h>

extern unsigned char BadApple_zip[];
extern unsigned int BadApple_zip_len;

unsigned char* Bad_Apple_bin;

#define WIDTH 80
#define HEIGHT 24
#define INCREMENT 1920
#define FRAMES 6572

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
            unsigned char colors = Bad_Apple_bin[position++];
            printf("%c",colorScale[colors& 0x0f]);
        }
        printf("\n");
    }
}

// Loads the attached zip file into Bad_Apple_bin, and returns the number of bytes read.
unsigned load_zip(){
    zip_error_t er;
    struct zip_stat zs;
    
    zip_source_t* source = zip_source_buffer_create(BadApple_zip, BadApple_zip_len, 0, &er);

    zip_t* z = zip_open_from_source(source, 0, &er);
    printf("Z: %p\n", z);
    zip_stat(z, "Bad Apple.bin", ZIP_FL_ENC_UTF_8, &zs);
    int size = zs.size;
    printf("Found file of size: %d\n", size);
    Bad_Apple_bin = malloc(zs.size);
    zip_file_t* file = zip_fopen(z, "Bad Apple.bin", ZIP_FL_ENC_UTF_8);

    int bytesread = zip_fread(file, Bad_Apple_bin, zs.size);
    printf("Read %d bytes\n", bytesread);
    return zs.size;
}

int main(int argc, char *argv[]) {
    unsigned long position = 0;
    struct timeval start, current;
    struct timespec ts;

    unsigned size = load_zip();

    ts.tv_sec = 0;
    gettimeofday(&start, 0);
    gettimeofday(&current, 0);
    while(position < size / INCREMENT){
        displayFrame(position * INCREMENT);
        ++position;
        gettimeofday(&current, 0);
        unsigned wait_time_ms = position * 1000.0 / 30.0 - timedifference_msec(&start, &current);
        ts.tv_nsec = 1000000 * wait_time_ms;
        nanosleep(&ts, &ts);
        printf("%s", home);
    }
}