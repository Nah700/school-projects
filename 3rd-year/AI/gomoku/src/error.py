import sys

def prout(str): # print out
    print("\033[31m[\033[0m\033[32mDEBUG\033[0m\033[31m]\033[0m " + "\033[34m" + str + "\033[0m", file=sys.stderr)