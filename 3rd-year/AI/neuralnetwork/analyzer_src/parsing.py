from sys import argv
from analyzer_src.analyzer_class import Analyzer

def parsing():
    argc = len(argv)
    if argc < 3 or argc > 7:
        exit(84)
    loadfile = argv[-2]
    dataset_file = argv[-1]
    analyzer = Analyzer(loadfile, dataset_file)
    if "--predict" in argv:
        analyzer.predict = True
    if "--train" in argv:
        analyzer.train = True
    if "--save" in argv:
        analyzer.save = argv[argv.index("--save") + 1]
    return analyzer
