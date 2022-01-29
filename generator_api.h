#ifndef GENERATOR_API_H
#define GENERATOR_API_H

typedef union {
    float analog;
    unsigned int digital;
} data_t;

typedef void (data_event_handler_t) (data_t);

/**
 * Register sensor for data generation.
 *
 * @param sensor_description_file sensor description file in JSON format.
 * 
 * @param handler callback function for data ready event.
 *
 * @return 0 if registered, -1 if file error, -2 if parsing error.
 */
int register_sensor(char *sensor_description_file, data_event_handler_t handler);

/**
 * Deregister sensor. Stops sampling if sensor is in sampling state.
 */
void deregister_sensor();

/**
 * Starts sampling thread, sensor is now in sampling state.
 */
void start();

/**
 * Stops sampling thread, sensor is now in idle state.
 */
void stop();

#endif /* GENERATOR_API_H */