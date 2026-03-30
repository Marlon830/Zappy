#!/usr/bin/env python3

from ai import AI
from State.Homer import Homer
import argparse

import sys

def main():
    parser = argparse.ArgumentParser(add_help=False)
    
    parser.add_argument("-p", "--port", required=True, help="Server Port")
    parser.add_argument("-n", "--name", required=True, help="Team Name")
    parser.add_argument("-h", "--host", default="localhost", help="Server Host")
    parser.add_argument("-help", action="help", help="Show this help message and exit")
    
    args = parser.parse_args()

    try:
        ia = AI(args.host, args.port, args.name, Homer)
    except ConnectionRefusedError:
        print("Connection refused, cannot start.", file=sys.stderr)
        return 84

    ia.run()
    return 0

if __name__ == "__main__":
    sys.exit(main())
