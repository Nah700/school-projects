from sys import argv

def parsing():
    argc = len(argv)
    data = []
    if argc == 1 or argc % 2 == 0:
        exit(84)
    for i in range(1, argc, 2):
        try:
            argv[i + 1] = int(argv[i + 1])
            data.append((argv[i], argv[i + 1]))
        except:
            print(f"Error: Couldn't parse number for {argv[i]}")
    return data
