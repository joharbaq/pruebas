#ifndef COMMON_H
#define COMMON_H

#define BUFFER_SIZE 10

typedef struct
{
    unsigned int data[BUFFER_SIZE];
    unsigned short index;
}circular_buffer_t;

/**
 * Imprime led verde.
 */
void led_verde();

/**
 * Imprime led rojo.
 */
void led_rojo();

/**
 * Inicializa el buffer circular con ceros.
 *
 * @param buffer puntero al buffer.
 */
void init_buffer(circular_buffer_t *buffer);

/**
 * Inserta un dato en el buffer.
 *
 * @param buffer puntero al buffer.
 * 
 * @param datum dato a insertar.
 */
void insert_buffer(circular_buffer_t *buffer, unsigned int datum);

/**
 * Calcula el promedio, en punto flotante, del buffer circular.
 *
 * @param buffer puntero al buffer.
 *
 * @return el promedio de todos los elementos del buffer.
 */
float mean_buffer(circular_buffer_t *buffer);

#endif /* COMMON_H */