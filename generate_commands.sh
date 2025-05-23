#!/usr/bin/env bash
make --always-make --dry-run \
 | grep -wE 'gcc|g\+\+' \
 | grep -w '\-c' \
 | sed 's/$/ -std=c++17 -Wno-c++17-extensions/' \
 | jq -nR --arg pwd "$PWD" '[inputs | {
     directory: $pwd,
     command: .,
     file: ($pwd + "/" + (match(" -c ([^ ]+)").captures[0].string))
 }]' \
 > compile_commands.json
