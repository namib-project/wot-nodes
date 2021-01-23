#ifndef SENSOR_H_
#define SENSOR_H_

typedef enum units {C, K, F} Unit;
bool validUnit(unsigned int i);//needs to get modified if the number of supported units change

int dht_sensor_init(void);
int dht_cmd(int argc, char **argv);
int sensor_get_temperature(void);
int sensor_get_humidity(void);
Unit sensor_get_temperature_unit(void);
int* sensor_get_temperature_range(void);
int sensor_get_temperature_step(void);
int sensor_get_temperature_precision(void);
void sensor_set_temperature_unit(Unit u);

char* sensor_get_humidity_unit(void);
int sensor_get_humidity_min_range(void);
int sensor_get_humidity_max_range(void);
int sensor_get_humidity_precision(void);
int sensor_get_humidity_step(void);
int sensor_get_humidity_max(void);
int sensor_get_humidity_min(void);
void sensor_humidity_reset_extreme(void);

#endif // SENSOR_H_