//*******************************************************************
// file name: ADC.c
// function: let potentiometer be the input of ain0, read the value of ain0,
//           if read the voltage exceeds 0.9V, then set gpio 66 output 1(light), 
//           else set gpio 66 output 0(unlight)
//*******************************************************************
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>
#define  output "out"
#define  input  "in"
#define  logic_on  1
#define  logic_off  0

void delay(int milliseconds) {
    long pause;
    clock_t now,then;
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int  main (void) {
	
	//export gpio and enable capes with slots/
	//define file variables
	char* export_file_path = "/sys/class/gpio/export";
	char* enable_adc_path = "/sys/devices/platform/bone_capemgr/slots";
	FILE *p_export_file, *p_enable_capes_slots_file;
	//define pin variables for gpio66, adc device
	int pin_number_66 = 66;
	//	char* ADC_device = "BB-ADC"
	
	//export for gpio66
	p_export_file = fopen(export_file_path, "w");
	if(p_export_file == NULL) {printf("Unable to open export file.\n");}
	fseek(p_export_file, 0, SEEK_SET);
	fprintf(p_export_file, "%d", pin_number_66);
	fflush(p_export_file);
	fclose(p_export_file);
	
	/*enable capes with slots
	p_enable_capes_slots_file = fopen(enable_adc_path, "w");
	if(p_enable_capes_slots_file == NULL) {printf("Unable to open slots file.\n");}
	fseek(p_enable_capes_slots_file, 0, SEEK_SET);
	fprintf(p_enable_capes_slots_file, "%s", ADC_device);
	fflush(p_enable_capes_slots_file);
	fclose(p_enable_capes_slots_file);*/
	
	
	//direction setting/
	//define file variables
	char* gpio66_direction_file_path = "/sys/class/gpio/gpio66/direction";
	FILE *p_gpio_direction_file;
		
		
	p_gpio_direction_file = fopen(gpio66_direction_file_path, "w");
	if(p_gpio_direction_file == NULL) {printf("Unable to open direction file.\n");}
	fseek(p_gpio_direction_file, 0, SEEK_SET);
	fprintf(p_gpio_direction_file, "%s",  output);
	fflush(p_gpio_direction_file);
	fclose(p_gpio_direction_file);	
	
	while(1){
		
		/*Loop for detecting adc ain0 status(value)*/
		//define file handles
		FILE *p_adc_ain0_value_file, *p_gpio_value_file;
		char* ain0_value_path = "/sys/bus/iio/devices/iio:device0/in_voltage0_raw";
		char* gpio66_value_file_path = "/sys/class/gpio/gpio66/value";
		float ain0_value;
		
		p_adc_ain0_value_file = fopen(ain0_value_path, "r");
		if (p_adc_ain0_value_file == NULL) {printf("Unable to ain0.\n");}
		fseek(p_adc_ain0_value_file, 0, SEEK_SET);
		fscanf(p_adc_ain0_value_file, "%f", &ain0_value);
		printf("%f\n", ain0_value); 
		if(ain0_value<2047){
			//write a logic 1 to gpio66 to illuminate the LED
			p_gpio_value_file = fopen(gpio66_value_file_path, "w");
			if(p_gpio_value_file == NULL) {printf("Unable to open gpio66_value.\n");}
			fseek(p_gpio_value_file, 0, SEEK_SET);
			fprintf(p_gpio_value_file, "%d", logic_on);
			fflush(p_gpio_value_file);
			fclose(p_gpio_value_file);
			printf("read 67 High > 66 light\n");
		}
		else if(ain0_value>=2047){
			//else turn off the led via send low value to gpio66
  			//write a logic 0 to gpio66 to unilluminate the LED
			p_gpio_value_file = fopen(gpio66_value_file_path, "w");
			if(p_gpio_value_file == NULL) {printf("Unable to open gpio66_value.\n");}
			fseek(p_gpio_value_file, 0, SEEK_SET);
			fprintf(p_gpio_value_file, "%d", logic_off);
			fflush(p_gpio_value_file);
			fclose(p_gpio_value_file);
			printf("read 67 Low > 66 unlight\n");
		}
		delay(1000);
		fclose(p_adc_ain0_value_file);
		
	}
	printf("remember close the adc device for saving power.\n");
	printf("command: cat /sys/devices/platform/bone_capemgr/slots\n");
	printf("echo '-device no.' > /sys/devices/platform/bone_capemgr/slots\n");
	
	
	return 0;
}