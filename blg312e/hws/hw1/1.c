#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int N;
	scanf("%d", &N);
	for	(int i = 0; i < N + 1; i++) {
		if (fork() == 0) {		// Left node creation for each process
			break;
		}
		if (i == N) {	// Do not extend further on the right if current process is the right end node
			break;
		}
		if (fork() > 0) {		// Right node creation
			break;
		}
	}
	printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
	while (wait(NULL) > 0);		// Wait and reap until all the child processes terminate
	return 0;
}
