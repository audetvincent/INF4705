#!/usr/bin/env python

import os
dir = os.path.dirname('mean.py')
result_path = os.path.join(dir, '../result')
for filename in os.listdir(result_path):
    f = open(filename)
    content = f.readlines()
    for line in content:
        print line