#include "coroutine.h"
#include <stdio.h>
#include <unistd.h>
struct args
{
	int n;
};

static void foo1(struct schedule *S, void *args)
{
	while (1)
	{
		sleep(1);
		printf("1\n");
		coroutine_yield(S);
	}
}
static void foo2(struct schedule *S, void *args)
{
	while (1)
	{
		sleep(2);
		printf("2\n");
		coroutine_yield(S);
	}
}


int main()
{
	struct schedule *S = coroutine_open();
	struct args arg1 = {1};
	struct args arg2 = {2};
	int co1 = coroutine_new(S, foo1, &arg1);
	int co2 = coroutine_new(S, foo2, &arg2);
	while (coroutine_status(S, co1) && coroutine_status(S, co2))
	{
		coroutine_resume(S, co1);
		coroutine_resume(S, co2);
	}
	coroutine_close(S);
	return 0;
}
