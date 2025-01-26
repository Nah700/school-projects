import sys
import numpy as np
from analyzer_src.math import sigmoid, sigmoid_derivative

class NeuralNetwork:
    def __init__(self, conf):
        self.epochs = conf["epochs"]
        self.input_size = conf["input_size"]
        self.hidden_size = conf["hidden_size"]
        self.output_size = conf["output_size"]
        self.learning_rate = conf["learning_rate"]

        self.weights_input_hidden = np.array(conf["weights_input_hidden"])
        self.weights_hidden_output = np.array(conf["weights_hidden_output"])
        self.bias_hidden = np.array(conf["bias_hidden"])
        self.bias_output = np.array(conf["bias_output"])

    def predict(self, inputs):
        hidden_layer_input = np.dot(inputs, self.weights_input_hidden) + self.bias_hidden
        hidden_layer_output = sigmoid(hidden_layer_input)

        output_layer_input = np.dot(hidden_layer_output, self.weights_hidden_output) + self.bias_output
        output_layer_output = sigmoid(output_layer_input)

        return output_layer_output

    def train(self, training_data, epochs, print_progress_bar=True):
        for epoch in range(epochs):
            for inputs, expected in training_data:
                hidden_layer_input = np.dot(inputs, self.weights_input_hidden) + self.bias_hidden
                hidden_layer_output = sigmoid(hidden_layer_input)

                output_layer_input = np.dot(hidden_layer_output, self.weights_hidden_output) + self.bias_output
                output_layer_output = sigmoid(output_layer_input)

                output_error = expected - output_layer_output
                output_delta = output_error * sigmoid_derivative(output_layer_output)

                hidden_error = output_delta.dot(self.weights_hidden_output.T)
                hidden_delta = hidden_error * sigmoid_derivative(hidden_layer_output)

                self.weights_hidden_output += np.outer(hidden_layer_output, output_delta) * self.learning_rate
                self.bias_output += output_delta * self.learning_rate

                self.weights_input_hidden += np.outer(inputs, hidden_delta) * self.learning_rate
                self.bias_hidden += hidden_delta * self.learning_rate

            if print_progress_bar:
                print_progress(epoch + 1, epochs)

def print_progress(epoch, total_epochs):
    bar_length = 40
    progress = epoch / total_epochs
    block = int(bar_length * progress)
    bar = "#" * block + "-" * (bar_length - block)
    sys.stdout.write(f"\rEpoch {epoch}/{total_epochs} [{bar}] {progress * 100:.2f}%")
    sys.stdout.flush()
    if epoch == total_epochs:
        print()

def load_training_data(filename):
    training_data = []
    results = ["Nothing", "White", "Black", "CheckmateWhite", "CheckmateBlack", "Stalemate"]
    # TODO: remove difference between colors in result list
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split(' ')
            fen = ' '.join(parts[:6])
            if len(parts) < 7:
                continue
            label = parts[6]
            if label == "Check":
                label = parts[7]
            elif label == "Checkmate":
                label = "Checkmate" + parts[7]
            #if label in results:
            #    output = [0] * 7
            #    output[results.index(label)] = 1
            #    output = np.array(output)
            if label == "Nothing":
                output = np.array([1, 0, 0, 0, 0, 0])
            elif label == "White":
                output = np.array([0, 1, 0, 0, 0, 0])
            elif label == "Black":
                output = np.array([0, 0, 1, 0, 0, 0])
            elif label == "CheckmateWhite":
                output = np.array([0, 0, 0, 1, 0, 0])
            elif label == "CheckmateBlack":
                output = np.array([0, 0, 0, 0, 1, 0])
            elif label == "Stalemate":
                output = np.array([0, 0, 0, 0, 0, 1])
            training_data.append((fen, output))
    return training_data
