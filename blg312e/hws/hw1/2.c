#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	
	pid_t current_head;
	for (int i = 0; i < N + 1; i++) {
		current_head = getpid();
		for (int j = 0; j < M; j++) {
			if (fork() > 0) {	// Left tree expansion - If called from the parent process, break and delegate the rest to the child process
				break;
			}
		}
		if (current_head != getpid() || i == N) {	// Checks if the calling process should expand to the right (if it is not a head node or it is a right end node)
			break;
		}
		if (fork() > 0) {	// Right tree expansion - Similar to the comment above
			break;
		}
	}
	printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
	while (wait(NULL) > 0);		// Wait and reap until all the child processes terminate
	return 0;
}
