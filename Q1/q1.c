#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
	// We use two pipes
	// First pipe to send input string from parent
	// Second pipe to send concatenated string from child

	int fd1[2];
	int fd2[2];

	char fixed_str[] = " The sum of even digits in the input number:";
	char input_str[100];
	pid_t p;

	if ((pipe(fd1)==-1) || (pipe(fd2)==-1))
	{
		fprintf(stderr, "Pipe Failed" );
		return 1;
  }

  printf("enter a number\t");
	scanf("%s", input_str);
	p = fork();

	if (p < 0)
	{
		fprintf(stderr, "fork Failed" );
		return 1;
	}
  // Parent process
	else if (p > 0)
	{
		char concat_str[100];

		close(fd1[0]);
		write(fd1[1], input_str, strlen(input_str)+1);
		close(fd1[1]);

		wait(NULL);

		close(fd2[1]);
		read(fd2[0], concat_str, 100);
		close(fd2[0]);

    printf("%s\n", concat_str);
	}
	// child process
	else
	{
    char concat_str[150];
    char input_num[100];

		close(fd1[1]);
		read(fd1[0], input_num, 100);
    close(fd1[0]);

    //calculate sum of even numbers:
    int sum = 0;

    for (int i=0, j=0; i<strlen(input_num); i++) {
      j = input_num[i] - '0';
      if(j % 2 == 0)
        sum += j;
    }

		// Concatenate a fixed string with it
		int k = strlen(input_num);
		for (int i=0; i<strlen(fixed_str); i++)
			input_num[k++] = fixed_str[i];

    sprintf(concat_str, "%s %d\n", input_num, sum);


		close(fd2[0]);
		write(fd2[1], concat_str, strlen(concat_str)+1);
		close(fd2[1]);

		exit(0);
	}
}
