#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define OPEN	'o'
#define READ	'r'
#define WRITE	'w'
#define EXIT	'e'
#define ENTER   '\0'

#define BUFFER_SIZE 1024


openDevice(){
	open("/dev/simple_character_device", O_RDWR | O_APPEND);
	getInput();
}

readDevice(){
	printf("\nData read from the device:\n");
	system("cat /dev/simple_character_device");

	getInput();
}

writeDevice(){
	printf("\nEnter data you want to write to the device:\n");
	char data[BUFFER_SIZE];
	if (fgets(data, BUFFER_SIZE, stdin) != NULL){
		char cmd[BUFFER_SIZE+50];
		sprintf(cmd,"echo \"%s\" >> /dev/simple_character_device", data);
		system(cmd);
	}
	getInput();	
}

getInput(){
	char inputBuffer[3];
	printf("\nPlease enter a command (o,r,w,e): ");
	if (fgets(inputBuffer, 3, stdin) != NULL){
		// printf("\nYou entered this: %c \n", inputBuffer[0]);

		if (inputBuffer[0] == OPEN){
			openDevice();
		}
		else if (inputBuffer[0] == READ){
			readDevice();
		}
		else if (inputBuffer[0] == WRITE){
			writeDevice();
		}
		else if (inputBuffer[0] == EXIT){
		}
		else{
			printf("You have given incorrect input");
			getInput();
		}
	}
}

main(){
	getInput();
}