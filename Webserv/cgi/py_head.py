#!/usr/bin/env python3

import requests
import sys

if len(sys.argv) != 2:
    print("Usage: py_delete.py <url>")
    sys.exit(1)

try:
	response = requests.head(sys.argv[1])
except:
	print("Error: Could not connect to server")
	sys.exit(1)

print("Status code received: ", response.status_code)