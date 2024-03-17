#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//typedef int16_t sample_t;
typedef int8_t sample_t;
typedef int8_t fourcc[4];

#define SAMPLE_MAX 32767
#define DURATION 50 // In seconds
//#define SR 44100
#define SR 8000
#define NCHANNELS 1
#define NSAMPLES (NCHANNELS*DURATION*SR)
#define FILE_NAME "output.wav"
#define WRITE_MODE "wb"


struct riff_hdr {
    fourcc id;
    uint32_t size;
    fourcc type;
};

struct fmt_ck {
    fourcc id;
    uint32_t size;
    uint16_t fmt_tag;
    uint16_t channels;
    uint32_t samples_per_sec;
    uint32_t bytes_per_sec;
    uint16_t block_align;
    uint16_t bits_per_sample;

};

struct data_hdr {
  fourcc   id;
  uint32_t size;
};

struct wav_hdr {
  struct riff_hdr riff;
  struct fmt_ck   fmt;
  struct data_hdr data;
};

int main(){
    // Initializing WAV header
    struct wav_hdr hdr = {0};

    // Opening file
    FILE *fp  = fopen(FILE_NAME, "wb");

    // Initializing RIFF header
    memcpy(&hdr.riff.id, "RIFF", 4);
    hdr.riff.size = 36 + NSAMPLES*sizeof(sample_t);
    memcpy(&hdr.riff.type, "WAVE", 4);

    // Initializing FMT chunk
    memcpy(&hdr.fmt.id, "fmt ", 4);
    hdr.fmt.size = 16;
    hdr.fmt.fmt_tag = 1;  /* linear PCM */
    hdr.fmt.channels = NCHANNELS;
    hdr.fmt.samples_per_sec = SR;
    hdr.fmt.bytes_per_sec = NCHANNELS*SR*sizeof(sample_t);
    hdr.fmt.block_align = NCHANNELS*sizeof(sample_t);
    hdr.fmt.bits_per_sample = 8*sizeof(sample_t);

    // Initializing data chunk
    memcpy(&hdr.data.id, "data", 4);
    hdr.data.size = NSAMPLES*sizeof(sample_t);

    fwrite(&hdr, sizeof(struct wav_hdr), 1, fp);


    /* WRITING AUDIO CHUNKS! */
    static sample_t buf[NSAMPLES];

    for (size_t i = 0; i < NSAMPLES; ++i)
        buf[i] = lrint(SAMPLE_MAX*(sin(2*M_PI * 440 * i/SR) + sin(2*M_PI * 220 * i/SR))/2);
    for (size_t t = 0; t < NSAMPLES; ++t)
        buf[t] =  ( t *9&t >>4| t *5&t >>7| t *3&t >>10)-1;



    fwrite(buf, sizeof(buf), 1, fp);


    /* 1 byte padding if buf size is odd */
    if (sizeof(buf) % 2 == 1){
        char nil = 0;
        fwrite(&nil, 1, 1, fp);
    }

    fclose(fp);
    return 0;

}
