#!/bin/bash

# executar com watch -d -n 0.5 ./video-08-desafio.c
# ps -x --forest | grep "a.out" | grep -v 'grep' |
#   sed -E "s/^(\s+?[0-9]+)(.*\s+\|)(.*)/(\1) \3/"
ps -x --forest | grep "a.out" | grep -v 'grep' |
  sed -E "s/^(\s+?)([0-9]+)(.*\s+\|)(.*)/(\2) \4/"
