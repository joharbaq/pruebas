#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"

void led_verde()
{
    printf("\r\033[0;31m");
    printf("[ ]");
    printf("\033[0;32m");
    printf("[\u2586]");
    printf("\033[0m");
}

void led_rojo(bool toogle){
    printf("\r\033[0;31m");
    if(toogle){
    printf("[\u2586]");}
    else{printf("[]");}
    printf("\033[0;32m");
    printf("[ ]");
    printf("\033[0m");
}
void parpadea_verde(bool toggle)
{
  printf("\r\033[0;31m");
  printf("[ ]");
  printf("\033[0;32m");
  if(toggle){
    printf("[\u2586]");
    }else
    printf("[ ]");
  printf("\033[0m");
  fflush(stdout);
}

void init_buffer(circular_buffer_t *buffer)
{
    memset(buffer, 0, sizeof(circular_buffer_t));
}

void insert_buffer(circular_buffer_t *buffer, unsigned int datum)
{
    buffer->data[buffer->index] = datum;
    buffer->index = (buffer->index + 1)%BUFFER_SIZE;
}

float mean_buffer(circular_buffer_t *buffer)
{
    unsigned int acc = 0;
    for(int i=0;i<BUFFER_SIZE;i++)
        acc += buffer->data[i];

    return acc/BUFFER_SIZE;
}

