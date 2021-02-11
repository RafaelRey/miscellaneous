#!/usr/bin/env python3

import yaml
import sys

with open(sys.argv[1], 'r') as stream:
    try:
        yml_data = yaml.safe_load(stream)
        for data in yml_data:
            try:
                yml_data[data]['ubuntu']['noetic'] = str(yml_data[data]['ubuntu']['bionic'])[2:-2].replace("melodic", "noetic")
            except Exception:
                continue
            
    except yaml.YAMLError as exc:
        print(exc)
    
    stream.close()

with open(sys.argv[1], 'w') as stream:
    yaml.dump(yml_data,stream)