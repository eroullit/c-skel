#!/bin/sh

# Wipeout template repo historym, keep sources untracked
rm -rf .git
# Init empty repo
git init

# Tweak config
git config color.ui auto
git config user.name "Emmanuel Roullit"
git config user.email emmanuel.roullit@gmail.com

# Add README as initial commit
git add README
git commit README -m "Initial commit"
# Add the rest of the repo
git add *
git commit -a -m "add build and test infrastructure"
