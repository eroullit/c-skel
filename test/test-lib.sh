#!/bin/sh
#
# Copyright (C) 2013    Emmanuel Roullit <emmanuel.roullit@gmail.com>
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

. ./paths.sh
. ./sharness.sh

PATH="$PATH:$PATH_TO_EXEC"
PYTHON_PATH="$(command -v python)"
test -n "$PYTHON_PATH" && test_set_prereq PYTHON
"$PYTHON_PATH" -c "import yaml" > /dev/null 2>&1 && test_set_prereq PYTHON_YAML

pyfibo() {
    "$PYTHON_PATH" "$SHARNESS_TEST_DIRECTORY/fibo.py" $@
}

# vim: ft=sh:tabstop=4:et
