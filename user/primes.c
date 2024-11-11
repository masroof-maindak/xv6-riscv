/* Sieve of Eratosthenes via child processes */

#include "kernel/types.h"
#include "user/user.h"

/**
 * @brief Read numbers from stdin and write them to stdout if they are not
 * divisible by 'base'
 */
void sieve(int base) {
	int n, i;

	for (;;) {
		n = read(0, &i, sizeof(i));
		if (n == 0) { /* END */
			break;
		} else if (n == -1) {
			fprintf(2, "read() in sieve()\n");
			exit(6);
		}

		if (i % base != 0) {
			if (write(1, &i, sizeof(i)) < 0) {
				fprintf(2, "write() in sieve()\n");
				exit(7);
			}
		}
	}

	return;
}

/**
 * @brief close fd 'x' and make stdin/stdout point to the read/write end of the
 * pipe
 */
void point_pipe(int x, int pd[]) {
	close(x);
	dup(pd[x]);
	close(pd[0]);
	close(pd[1]);
}

/**
 * @details \
 * 1. Read a prime number from stdin and print it to stdout.
 * 2. Create a child process.
 * 3. The parent process reads numbers from the child process and prints them to
 *    stdout if they are not divisible by the prime number.
 * 4. The child process reads numbers from stdin and writes them to the parent
 *    process.
 */
void primes() {
	int pd[2], n, p;

	n = read(0, &p, sizeof(p));
	if (n == -1) {
		fprintf(2, "read() in primes()\n");
		exit(3);
	} else if (n == 0) {
		/* END */
	} else {
		printf("prime %d\n", p);

		if (pipe(pd) == -1) {
			fprintf(2, "pipe() in primes()\n");
			exit(4);
		}

		int pid = fork();
		if (pid > 0) {
			/* Parent */
			point_pipe(0, pd); /* point pipe's read end to stdin */
			primes();
			exit(0);
		} else if (pid == 0) {
			/* Child */
			point_pipe(1, pd); /* point pipe's write end to stdout */
			sieve(p);
		} else {
			fprintf(2, "fork() in primes()\n");
			exit(5);
		}
	}
}

int main() {
	int p[2], pid;

	if (pipe(p) == -1) {
		fprintf(2, "pipe() in main()");
		exit(1);
	}

	pid = fork();
	if (pid > 0) {
		/* Parent */
		point_pipe(0, p);
		primes();
	} else if (pid == 0) {
		/* Child */
		point_pipe(1, p);
		for (int i = 2; i < 1000; i++)
			write(1, &i, sizeof(i));
	} else {
		fprintf(2, "fork() in main()");
		exit(2);
	}

	exit(0);
}
