#!/usr/bin/env python

import os, sys

key = sys.argv[1]
print key
dir_l = [x for x in os.listdir(".") if os.path.isdir(x) and x.find(key) > 0]

print dir_l

for x in dir_l:
  os.system("./rivetHadd "+x)
