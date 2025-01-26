import time
import numpy as np
from analyzer_src.MLP import NeuralNetwork, load_training_data
from analyzer_src.math import fen_to_matrix
from random import shuffle

def map_prediction_to_label(prediction):
    labels = ["Nothing", "Check White", "Check Black", "Checkmate White", "Checkmate Black", "Stalemate"]
    return labels[np.argmax(prediction)]

def predict(nn: NeuralNetwork, input_filepath: str):
    with open(input_filepath, 'r') as f:
        for line in f:
            line = line.replace("\n", "")
            prediction = nn.predict((np.array(fen_to_matrix(line)).flatten()))
            label = map_prediction_to_label(prediction)
            print(label)
    return prediction

def convert_seconds_to_hms(seconds):
    hours = seconds // 3600
    minutes = (seconds % 3600) // 60
    secs = seconds % 60
    return f"{hours:02d}:{minutes:02d}:{secs:02d}"

def train(nn: NeuralNetwork, dataset_file: str):
    training_data = load_training_data(dataset_file)
    shuffle(training_data)
    training_data = [(np.array(fen_to_matrix(fen)).flatten(), expected) for fen, expected in training_data]

    print(f"Starting training for {nn.epochs} epochs...")

    start_time = time.time()
    nn.train(training_data, 10, False)
    elapsed_time = time.time() - start_time
    estimated_total_time = int((elapsed_time / 10) * nn.epochs)
    print(f"Estimated total training time: {convert_seconds_to_hms(estimated_total_time)} seconds")

    nn.train(training_data, nn.epochs)

    for inputs, _ in training_data:
        print(f"Input: {inputs}, Predicted: {nn.predict(inputs)}")
    return nn
