from .brainpy import interpret_cli, interpret_file
from .parser import ParseError

import argparse

parser = argparse.ArgumentParser(description='Simple BrainF*ck interpreter')

parser.add_argument('file', nargs='*', help='file to interpret')

args = parser.parse_args()

if args.file:
    for f in args.file:
        try:
            interpret_file(f)
        except IOError:
            print('could not open {}'.format(f))
        except ParseError as pe:
            print(pe)
else:
    try:
        interpret_cli()
    except KeyboardInterrupt:
        pass
    except EOFError:
        pass
