#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>
#define  output "out"
#define  input  "in"

void delay(int milliseconds) {
    long pause;
    clock_t now,then;
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int  main (void) {

	char* export_file_path = "/sys/class/gpio/export";
	FILE *p_export_file;
	int pin_number_66 = 66;
	int logic_on = 1,logic_off = 0;
	
	//export for gpio66
	p_export_file = fopen(export_file_path, "w");
	if(p_export_file == NULL) {printf("Unable to open export file.\n");}
	fseek(p_export_file, 0, SEEK_SET);
	fprintf(p_export_file, "%d", pin_number_66);
	fflush(p_export_file);
	fclose(p_export_file);
	
	char* gpio66_direction_path = "/sys/class/gpio/gpio66/direction";
	FILE *p_gpio_direction;
		
	p_gpio_direction = fopen(gpio66_direction_path, "w");
	if(p_gpio_direction == NULL) {printf("Unable to open direction file.\n");}
	fseek(p_gpio_direction, 0, SEEK_SET);
	fprintf(p_gpio_direction, "%s",  output);
	fflush(p_gpio_direction);
	fclose(p_gpio_direction);	
	
	while(1){

		FILE *ifp_ain0, *p_gpio_value;
		char* ain0_value_path = "/sys/bus/iio/devices/iio:device0/in_voltage0_raw";
		char* gpio66_value_path = "/sys/class/gpio/gpio66/value";
		float ain0_value;
		
		ifp_ain0 = fopen(ain0_value_path, "r");
		if (ifp_ain0 == NULL) {printf("Unable to ain0.\n");}
		fseek(ifp_ain0, 0, SEEK_SET);
		fscanf(ifp_ain0, "%f", &ain0_value);
		printf("%f\n", ain0_value);
		
		if(ain0_value < 2047){
			//write a logic 1 to gpio66 to illuminate the LED
			p_gpio_value = fopen(gpio66_value_path, "w");
			if(p_gpio_value == NULL) {printf("Unable to open gpio66_value.\n");}
			fseek(p_gpio_value, 0, SEEK_SET);
			fprintf(p_gpio_value, "%d", logic_on);
			fflush(p_gpio_value);
			fclose(p_gpio_value);
		}
		else if(ain0_value >= 2047){
			//else turn off the led via send low value to gpio66
  			//write a logic 0 to gpio66 to unilluminate the LED
			p_gpio_value = fopen(gpio66_value_path, "w");
			if(p_gpio_value == NULL) {printf("Unable to open gpio66_value.\n");}
			fseek(p_gpio_value, 0, SEEK_SET);
			fprintf(p_gpio_value, "%d", logic_off);
			fflush(p_gpio_value);
			fclose(p_gpio_value);
		}
		delay(1000);
		fclose(ifp_ain0);
	}
	return 0;
}