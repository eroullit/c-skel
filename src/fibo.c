#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <assert.h>
#include <inttypes.h>

#ifndef DEFAULT_FIBO_ORDER
#define DEFAULT_FIBO_ORDER 10
#endif /* DEFAULT_FIBO_ORDER */

void show_usage(const char *pname, const struct option *opt)
{
	assert(pname);

	printf("%s\n", pname);

	while (opt && opt->name) {
		printf("  --%s", opt->name);
		if (opt->has_arg == required_argument)
			printf(" <arg>\n");
		else if (opt->has_arg == optional_argument)
			printf(" [arg]\n");
		else
			printf("\n");
		opt++;
	}
}

int print_header(const uint64_t order)
{
	/* YAML header */
	return printf("--- #Fibonacci sequence order %"PRIu64"\n", order);
}
int print_fibo_result(const uint64_t num)
{
	/* YAML formatted list */
	return printf("- %"PRIu64"\n", num);
}

int fibo(const uint64_t order)
{
	/* a = F_0, b = F_1 */
	uint64_t a = 0, b = 1, c, i;

	if (order == 0)
		print_fibo_result(a);

	for (i = 0; i < order; i++)
	{
		c=a+b;
		a=b;
		b=c;
		print_fibo_result(c);
	}

	return 0;
}

int main(int argc, char ** argv)
{
	enum opts {
		OPT_FIBO_ORDER,
		OPT_HELP
	};

	static const struct option fibo_opts[] = {
		{"order", required_argument, NULL, OPT_FIBO_ORDER},
		{"help", no_argument, NULL, OPT_HELP},
		{NULL, 0, NULL, 0}
	};

	uint64_t order = DEFAULT_FIBO_ORDER;
	int ret;

	while((ret = getopt_long_only(argc, argv, "", fibo_opts, NULL)) != EOF)
	{
		switch(ret)
		{
			case OPT_FIBO_ORDER:
				order = strtoull(optarg, NULL, 10);
				break;
			case OPT_HELP:
			default:
				show_usage(argv[0], fibo_opts);
				return EXIT_SUCCESS;
		}
	}

	print_header(order);
	return fibo(order);
}
