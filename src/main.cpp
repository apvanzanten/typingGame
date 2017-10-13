#include <iostream>
#include <random>

#include <unistd.h>
#include <termios.h>

const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789;:\\|[{]},<.>/?!@#$%&*()_+";

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

float percentage(int a, int b){
	if(a == 0 || b == 0) return 0;
	return ((float)a / (float)b) * 100.0;
}

int main(void){
	
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,chars.size()-1);

	int correct = 0;
	int incorrect = 0;
	int total = 0;

	char desiredChar = chars[distribution(generator)];
	std::cout << "1:\t" << desiredChar << "\t" << percentage(correct, total) << std::endl;	

	for(int i = 2; i <= 1000; i++){
		total++;
		if(desiredChar == getch()){
			correct++;
			desiredChar = chars[distribution(generator)];
			std::cout << i << ":\t" <<  desiredChar << "\t" << percentage(correct, total) << std::endl;
		} else {
			incorrect++;
		}
	}

	return 0;
}