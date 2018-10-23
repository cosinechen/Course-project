#include <stdio.h>
#include <stddef.h>
#include <time.h>
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
	//define file handles for gpio67 (P8, pin 8)
	FILE *ifp_export_67, *ofp_export, *ifp_gpio67_value, *ofp_gpio66_value, *ifp_gpio67_direction,*ofp_gpio66_direction;

	//define pin variables for gpio67
	int pin_number = 66, pin_number_67 = 67 ,logic_status_67, logic_on = 1, logic_off = 0;
	
	char* pin_direction_67 = input;
	char* pin_direction = output;
	
	//create direction and value file for gpio67
	ifp_export_67 = fopen("/sys/class/gpio/export", "w");
	if(ifp_export_67 == NULL) {printf("Unable to open export.\n");}
	fseek(ifp_export_67, 0, SEEK_SET);
	fprintf(ifp_export_67, "%d", pin_number_67);
	fflush(ifp_export_67);
	fclose(ifp_export_67);
	
	ofp_export = fopen("/sys/class/gpio/export", "w");
	if(ofp_export == NULL) {printf("Unable to open export.\n");}
	fseek(ofp_export, 0, SEEK_SET);
	fprintf(ofp_export, "%d", pin_number);
	fflush(ofp_export);
	fclose(ofp_export);	
	
	//configure gpio67 direction
	ifp_gpio67_direction = fopen("/sys/class/gpio/gpio67/direction", "w");
	if(ifp_gpio67_direction == NULL) {printf("Unable to open gpio67_direction.\n");}
	fseek(ifp_gpio67_direction, 0, SEEK_SET);
	fprintf(ifp_gpio67_direction, "%s",  pin_direction_67);
	fflush(ifp_gpio67_direction);
	fclose(ifp_gpio67_direction);
	
	//configure gpio66 for writing
	ofp_gpio66_direction = fopen("/sys/class/gpio/gpio66/direction", "w");
	if(ofp_gpio66_direction == NULL) {printf("Unable to open gpio66_direction.\n");}
	fseek(ofp_gpio66_direction, 0, SEEK_SET);
	fprintf(ofp_gpio66_direction, "%s",  pin_direction);
	fflush(ofp_gpio66_direction);
	fclose(ofp_gpio66_direction);
	
	while(1) {
  		//read the gpio67 pin
  		ifp_gpio67_value = fopen("/sys/class/gpio/gpio67/value", "r");
  		if(ifp_gpio67_value == NULL) {printf("Unable to open gpio67_value.\n");}
  		fseek(ifp_gpio67_value, 0, SEEK_SET);
  		fscanf(ifp_gpio67_value, "%d", &logic_status_67);
  		fflush(ifp_gpio67_value);
		fclose(ifp_gpio67_value);
		
  		if(logic_status_67 == 1){
			ofp_gpio66_value = fopen("/sys/class/gpio/gpio66/value", "w");
			if(ofp_gpio66_value == NULL) {printf("Unable to open gpio66_value.\n");}
			fseek(ofp_gpio66_value, 0, SEEK_SET);
			fprintf(ofp_gpio66_value, "%d", logic_off);
			fflush(ofp_gpio66_value);
			fclose(ofp_gpio66_value);
			printf("High\n");
		} 
  		else{		
			ofp_gpio66_value = fopen("/sys/class/gpio/gpio66/value", "w");
			if(ofp_gpio66_value == NULL) {printf("Unable to open gpio66_value.\n");}
			fseek(ofp_gpio66_value, 0, SEEK_SET);
			fprintf(ofp_gpio66_value, "%d", logic_on);
			fflush(ofp_gpio66_value);
			fclose(ofp_gpio66_value);
			printf("Low\n");
		}
		delay(1000);
	}
	
	return 0;
}
