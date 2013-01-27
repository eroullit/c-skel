#!/bin/sh
#
# Copyright (C) 2013	Emmanuel Roullit <emmanuel.roullit@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or (at
# your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
#

test_description="Test Fibonacci sequence calculator"

. ./test-lib.sh

order_max=100

test_expect_success "Check executable presence" "
	test -x fibo
"

cat expect <<EOF
---
- 0
- 1
- 1
- 2
- 3
- 5
- 8
- 13
- 21
- 34
EOF

test_expect_success "Print fibonacci sequence without order input" "
    fibo > result &&
    test_cmp expect result
"

for i in $(seq $order_max)
do
    test_expect_success PYTHON_YAML "Print fibonacci sequence up to order $i" "
        python -c 'import yaml fibo; print yaml.dump(map(fibo.fib, range($i)), default_flow_style=False, explicit_start=True)' > expect &&
        fibo --order $i > result &&
        test_cmp expect result
    "
done

test_done

# vim: ft=sh:tabstop=4:et
