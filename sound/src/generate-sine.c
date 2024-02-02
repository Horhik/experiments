#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint16_t sample_t;

#define BIT_DEPTH 16
#define SR 44100 // Sample rate
#define N_DURATION 80
#define CHANNELS 1
#define N_SAMPLES (CHANNELS * N_DURATION * SR)

#define SAMPLE_MAX 32767 // because of using LPCM will use int values for bit depth

float garmonic_series(int n){
  float res = 0;
  for (int i = 0; i < n; i++){
    res += 1/i;
  }
  return res;
}

int main(){

typedef int8_t fourcc;

struct riff_header{
    fourcc id; // 4 bytes, id = "RIFF"
    uint32_t size; // 4 bytes
    fourcc type; // 4 bytes, = WAVE
  };

struct fmt_chunk{
  fourcc id; // 4 bytes length id = "fmt "
  uint32_t size; // 4 bytes length length of the rest of fmt chunk
    // ...

uint16_t fmt_tag; // 2 bytes

uint16_t channels; // 2 bytes

uint32_t samples_sec; //4 bytes

uint32_t bytes_sec; // 4 bytes

uint16_t block_align; // 2 bytes

uint16_t bits_sample; // 2 bytes
};

struct data_header{
  fourcc id; // 4 bytes, id = "data"
  uint32_t size; // 4 bytes, size of data
};

struct wav_hdr{
  struct riff_header riff_header;
  struct fmt_chunk fmt_ck;
  struct data_header data_header;
};

struct wav_hdr header = {0};
FILE *fp = fopen("./sine.wav", "wb"); // write binary

memcpy(&header.riff_header.id, "RIFF", 4);
header.riff_header.size = 36 + N_SAMPLES*sizeof(sample_t); 
memcpy(&header.riff_header.type, "WAVE", 4);

memcpy(&header.fmt_ck.id, "fmt ", 4);
header.fmt_ck.size = 16;
header.fmt_ck.fmt_tag = 1;
header.fmt_ck.channels = CHANNELS;
header.fmt_ck.samples_sec = SR;
header.fmt_ck.bytes_sec = CHANNELS * SR * sizeof(sample_t); // using sizeof instead of BIT_DEPTH
header.fmt_ck.block_align = CHANNELS * sizeof(sample_t);
header.fmt_ck.bits_sample = 8*sizeof(sample_t); // converting bytes to bits

memcpy(&header.data_header.id, "data", 4);

header.data_header.size = N_SAMPLES*sizeof(sample_t);

fwrite(&header, sizeof(struct wav_hdr), 1, fp);

sample_t samples[N_SAMPLES];
 float gs = 0;
 int C = 880;
for (size_t i = 0; i < N_SAMPLES; i++){

  //samples[i] = lrint(SAMPLE_MAX*sin(i) + cos(i) );
  //samples[i] = lrint(SAMPLE_MAX*log(sin(2*M_PI*  C * i/SR) ));
  samples[i]= lrint(SAMPLE_MAX*log(2*M_PI*C*i*i/SR + sin(2*M_PI*  C* i/SR) ));
  samples[i] *= lrint(SAMPLE_MAX*sin(2*M_PI* C* i/SR)/(i%3000));
  samples[i] += lrint(SAMPLE_MAX*cos(4*M_PI* C* i/SR)/((i + N_SAMPLES/100)%3000));
  //samples[i]+= lrint(SAMPLE_MAX*log(sin(2*M_PI)* C * i/SR ));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  (441 + (i/10000)) * i/SR ));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  (430 + (i/10000)) * i/SR ));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  50 * i/SR * gs)/((1.0/i)*M_PI*i/(SR%1000)));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  10 * i/SR * gs)/((1.0/i)*M_PI*i/(SR%2000)));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  1000 * i/SR * gs)/((90.0)*M_PI/(SR%200)));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  1002 * i/SR * gs)/((90.0/i)*M_PI*i/(SR%200)));
  //samples[i] += lrint(SAMPLE_MAX*sqrt(cos(i%17)*log(sin(10*M_PI*  500 * i/SR * gs)/((90.0/i)*M_PI*i/(SR%200)))));
  //samples[i] = lrint(0.2*samples[i]);
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  120 * i/SR));
  //  samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI* exp(cos(i%5*10))*0.0001 * 20 * i/SR ));
  gs += cos(i%(int)(exp(i + 1)*10))/(i + 100) ;
}


 C = 440;
for (size_t i = 0; i < N_SAMPLES; i++){

  //samples[i] = lrint(SAMPLE_MAX*sin(i) + cos(i) );
  //samples[i] = lrint(SAMPLE_MAX*log(sin(2*M_PI*  C * i/SR) ));
  samples[i]+= lrint(SAMPLE_MAX*exp(8*M_PI*C*i*i/SR + sin(2*M_PI*  C* i/SR) ));
  samples[i] += lrint(SAMPLE_MAX*sin(8*M_PI* C* i/SR)/(5000*i%90000));
  //samples[i]+= lrint(SAMPLE_MAX*log(sin(2*M_PI)* C * i/SR ));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  (441 + (i/10000)) * i/SR ));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  (430 + (i/10000)) * i/SR ));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  50 * i/SR * gs)/((1.0/i)*M_PI*i/(SR%1000)));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  10 * i/SR * gs)/((1.0/i)*M_PI*i/(SR%2000)));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  1000 * i/SR * gs)/((90.0)*M_PI/(SR%200)));
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  1002 * i/SR * gs)/((90.0/i)*M_PI*i/(SR%200)));
  //samples[i] += lrint(SAMPLE_MAX*sqrt(cos(i%17)*log(sin(10*M_PI*  500 * i/SR * gs)/((90.0/i)*M_PI*i/(SR%200)))));
  //samples[i] = lrint(0.2*samples[i]);
  //samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI*  120 * i/SR));
  //  samples[i] += lrint(SAMPLE_MAX*sin(2*M_PI* exp(cos(i%5*10))*0.0001 * 20 * i/SR ));
  gs += cos(i%(int)(exp(i + 1)*10))/(i + 100) ;
}

fwrite(&samples, sizeof(samples), 1, fp);

/* 1 byte padding if samples size is odd */
if (sizeof(samples) % 2 == 1){
  char nil = 0;
  fwrite(&nil, 1, 1, fp);
}
fclose(fp);

return 0;
}
