#include<stdio.h>
#include<unistd.h>
#include<malloc.h>
#include<string.h>

void filter (char* command) {

	FILE *fd = popen(command, "r");
	if (fd == NULL) {
		perror(command);
		return;
	}
	
	char cur_c;
	
	char* buf = malloc(1);	
	
	int count = 0;
	
	if (buf == NULL) {
		perror(buf);
		pclose(fd);
		return;
	}
	
	cur_c = fgetc(fd);
	
	while (!feof(fd)) {
		buf[0] = cur_c;
		write(1, buf, 1);
		if (cur_c == '\n')
			count++;
			cur_c = fgetc(fd);
	}
	
	printf("Count = %d\n", count);
	
	pclose(fd);
}


int main(int argc, char* argv[]) {

	int i = 0, result_len = 0;

	if (argc < 2) {
		fprintf(stderr, "Too few arguments");
		return 1;
	}
	
	for (i = 1; i < argc; i++)
		result_len += strlen(argv[i]) + 1;
		
	char* arguments = malloc(result_len);
	
	for (i = 1; i < argc - 1; ++i) {	
		strcat(arguments, argv[i]);
		strcat(arguments, " ");
	}
	
	strcat(arguments, argv[i]);
	arguments[result_len - 1] = 0;
	
	filter(arguments);
	
	return 0;
}
