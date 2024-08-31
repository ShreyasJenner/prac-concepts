#include <ao/ao.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc ,char **argv) {
    int default_driver;
    ao_device *device;
    ao_sample_format format;
    char *buffer;
    unsigned long count;
    FILE *fp;

    ao_initialize();

    default_driver = ao_default_driver_id();

    if(default_driver == -1) {
        printf("Getting default driver failed\n");
        exit(1);
    }
    memset(&format, 0, sizeof(format));

    format.bits = 16;
    format.channels = 2;
    format.rate = 44100;
    format.byte_format = AO_FMT_BIG;

    device = ao_open_live(default_driver, &format, NULL);

    if(device == NULL) {
        printf("Error opening sound device\n");
        exit(1);
    }

    fp = fopen(argv[1], "rb");
    if(fp == NULL) {
        printf("Failed to open file\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    count = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    fread(buffer, sizeof(uint8_t), count, fp);

    ao_play(device, buffer, count);
    ao_close(device);
    ao_shutdown();
}
