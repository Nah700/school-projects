from sys import argv

def parsing():
    argc = len(argv)

    if argc < 4 or argc > 5:
        exit(84)

    crypto_system = argv[1]
    mode = argv[2]
    if argv[3] == "-b":
        return [crypto_system, mode, argv[3], argv[4]]
    if argc == 4:
        return [crypto_system, mode, None, argv[3]]
    return [crypto_system, mode, argv[3], argv[4]]
