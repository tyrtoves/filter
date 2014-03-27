#include<stdio.h>
#include<unistd.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

void filter (char** argv) {

	int filedes[2];

	if (pipe(filedes) < 0) {
	    printf("PIPE");
	    return;
	}
	
	int PID = fork();
	
	if (PID < 0) { 
		perror("FORK");
		return;	
	}
	if (PID == 0){
	
		close(filedes[0]);
		dup2(filedes[1], 1);
		
		if (execvp(argv[1], argv + 1) == -1) {
			perror("EXEC");
			return;
		}
		
		close (filedes[1]);
		return;
	}
	
    else { 
    
        close(filedes[1]);
        int count = 0, pos = 0;
        char buf[500];
		
		while ( ( pos = read(filedes[0], buf, 500) ) != 0) {
			write(1, buf, pos);
			int i;
			for (i = 0; i < pos; ++i)
				if (buf[i] == '\n')
					++count;
		}
		
		printf("%d\n", count);
    }
}


int main(int argc, char* argv[]) {
	
	filter(argv);
	
	return 0;
}
