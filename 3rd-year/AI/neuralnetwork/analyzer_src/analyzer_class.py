class Analyzer:
    def __init__(self, loadfile: str, dataset_file: str):
        self.predict: bool = False
        self.train: bool = False
        self.save: str | None = None
        self.loadfile: str = loadfile
        self.dataset_file: str = dataset_file
