/**
 * \file fibo.c
 * \author written by Emmanuel Roullit emmanuel.roullit@gmail.com \copy 2013
 * \date 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <assert.h>
#include <inttypes.h>

/** \brief Order use by default */
#ifndef DEFAULT_FIBO_ORDER
#define DEFAULT_FIBO_ORDER 10
#endif /* DEFAULT_FIBO_ORDER */

/**
 * \brief Print process usage on stdout
 * \param[in]           pname	        Process name
 * \param[in]           opt		Pointer to process option structure
 */

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

/**
 * \brief Print YAML header with the requested order on stdout
 * \param[in]           order	        Requested Fibonacci sequence order
 * \return similar return values as \c printf(3)
 */

int print_header(void)
{
	/* YAML header */
	return printf("---\n");
}

/**
 * \brief Print result as a YAML formatted list on stdout
 * \param[in]           num		Number to print
 * \return similar return values as \c printf(3)
 */

int print_fibo_result(const uint64_t num)
{
	/* YAML formatted list */
	return printf("- %"PRIu64"\n", num);
}

/**
 * \brief Calculate the Fibonnaci sequence
 * \param[in]           order		Requested Fibonacci sequence order
 * \return Always return 0
 */

int fibo(const uint64_t order)
{
	/* a = F_0, b = F_1 */
	uint64_t a = 0, b = 1, c = a, i = 0;

	do
	{
		print_fibo_result(c);
		c=a+b;
		a=b;
		b=c;
	}while(i++ < order);

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

	print_header();
	return fibo(order);
}
