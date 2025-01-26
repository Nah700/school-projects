import json

def save(learning_rate, weights_input_hidden, weights_hidden_output, bias_hidden, bias_output, filename_in, filename_out):
    with open(filename_in, 'r') as f:
        json_data = json.load(f)
        state = {
            'weights_input_hidden': weights_input_hidden,
            'weights_hidden_output': weights_hidden_output,
            'bias_hidden': bias_hidden,
            'bias_output': bias_output,
            'learning_rate': learning_rate,
            "input_size": json_data["input_size"],
            "hidden_size": json_data["hidden_size"],
            "output_size": json_data["output_size"],
            "epochs": json_data["epochs"]
        }

    with open(filename_out, 'w') as f:
        json.dump(state, f, indent=4)
