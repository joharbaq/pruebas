#include <stdio.h>
#include <stdbool.h>

#include "generator_api.h"
#include "planificador.h"
#include "common.h"
#define PeriodoParpadeo 1000
#define PeriodoPrendio 2000
#define TIMEOUT 2000 //Timeout en milisegundos
#define TICK 10
float THRESHOLD;
bool parpadear= true;
bool prendido=true;


/* Estados de la FSM */
typedef enum {EXIT = 0, START, SAMPLING, ALERT} STATE;

STATE estado;

volatile bool is_new_data = false;

volatile unsigned int data_adc;

/* Función callback, es llamada cuando
hay un dato nuevo en el ADC simulado */
void callback_datos(data_t data)
{
    data_adc = data.digital;
    is_new_data = true;
}

void parpadeoVerde(void *args){
    parpadea_verde(parpadear);
    if(parpadear==true){
        parpadear= false;
    }else{
        parpadear=true;
    }

}
void encendido (void *args){
led_rojo(prendido);

}
int main(int argc, char **argv)
{
    //Registra el sensor en la simulación...
    int r = register_sensor("sensor_adc.json", callback_datos);

    if(r < 0){
        fprintf(stderr, "Error al registrar el sensor.\n");
        return 1;
    }


    printf("Ingrese umbral de alerta [40-400]: ");
    scanf("%f", &THRESHOLD);
    printf("Recibiendo datos, umbral de alerta es %f.\n", THRESHOLD);
    printf(" grados");

    tTime TiempoInicio= TimeNow_ms(); 
    struct Task *parpadear= TaskNew(TiempoInicio,0,PeriodoParpadeo,parpadeoVerde);
    SchedulerAddTask(parpadear);
    struct Task *prendido= TaskNew(TiempoInicio,0,PeriodoPrendio,encendido);
    SchedulerAddTask(prendido);
    tTime inicioTimer;
    estado = START;
    circular_buffer_t buff;
    init_buffer(&buff);
    while(estado) {
        switch(estado)
        {
            case START:
                start(); //Inicia la generación de datos simulados
                estado = SAMPLING;
                break;
            case SAMPLING:
                if(is_new_data){
                    insert_buffer(&buff, data_adc);
                    float mean = mean_buffer(&buff);
                    float conversion = mean*(360.0/16383.0)+40.0;
                    TaskDisable(parpadear);
                    TaskEnable(parpadear);
                    printf("\t%.0f", conversion);
                    
                    if(conversion > THRESHOLD){
                        estado = ALERT;
                        inicioTimer = TimeNow_ms();
                        TaskDisable(parpadear):

                    }
                    is_new_data = false;
                }
                break;
            case ALERT:
                if(is_new_data){
                    TaskEnable(prendido);
                    printf("\t%u", data_adc);
                    fflush(stdout);

                    is_new_data = false;
                }

                if (TimePassed_ms(inicioTimer) > TIMEOUT)
                    estado = SAMPLING;
                break;
            default:
                estado = EXIT;
        }
        if(TimePassed(TiempoInicio) > TICK){
        SchedulerRun();
        TiempoInicio = TimeNow();
    }

    printf("Terminando proceso...\n");

    return 0;
}