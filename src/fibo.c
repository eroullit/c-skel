/**
 * \file fibo.c
 * \author written by Emmanuel Roullit emmanuel.roullit@gmail.com \copy 2013
 * \date 2013
 */

/*

=head1 NAME

fibo - Print Fibonacci sequence to stdout

=head1 SYNOPSIS

dabbad [--order <order>][--help]

=head1 DESCRIPTION

This tool prints the Fibonacci sequence from 0 to the requested order.
The output is formatted in YAML.

=head1 EXAMPLES

=over

=item fibo

Print the number of the Fibonacci sequence up to the order 10

=item fibo --order 20

Print the number of the Fibonacci sequence up to the order 20

=item fibo --help

Prints help content.

=back

=head1 AUTHOR

Written by Emmanuel Roullit <emmanuel.roullit@gmail.com>

=back

=head1 COPYRIGHT

=over

=item Copyright © 2013 Emmanuel Roullit.

=item License GPLv2+: GNU GPL version 2 or later <http://gnu.org/licenses/gpl.html>.

=item This is free software: you are free to change and redistribute it.

=item There is NO WARRANTY, to the extent permitted by law.

=back

=cut

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
	uint64_t a = 1, b = 0, c = 0, i = 0;

	do
	{
		print_fibo_result(c);
		c=a+b;
		a=b;
		b=c;
	} while(i++ < order);

	printf("\n");
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
