#https://www.youtube.com/watch?v=vieoHqt7pxo
import numpy as np
import pandas as pd
import tensorflow as tf
from flask import Flask, jsonify, request

app = Flask(__name__)

def get_data(json_data):
    # Sample JSON data with 20 objects

    # Convert JSON data to a DataFrame
    motion_data_test = pd.DataFrame(json_data, columns=['AccX', 'AccY', 'AccZ', 'GyroX', 'GyroY', 'GyroZ'])

    # Convert the DataFrame to a numpy array
    motion_data_array = motion_data_test.to_numpy()

    # Reshape the array to match the LSTM input shape (None, 20, 6)
    reshaped_motion_data = np.reshape(motion_data_array, (1, len(json_data), 6))

    # Load the LSTM model
    model = tf.keras.models.load_model("./MODELO_LSTM_TCC.h5")

    # Make prediction
    predicted_values = model.predict(reshaped_motion_data)

    # Define the threshold for classification
    threshold = 0.5

    # Convert the predicted values to binary classification (NORMAL or AGGRESSIVE)
    predicted_class = np.where(predicted_values > threshold, "AGGRESSIVE", "NORMAL")
    predicted_class = predicted_class.tolist()  # Convert the NumPy array to a Python list

    return predicted_class

@app.route('/get_data', methods=['POST'])
def predict_data():
    json_data = request.get_json()
    predicted_class = get_data(json_data)
    return jsonify({"Predicted Class": predicted_class})
@app.route('/')
def hello():
    return 'Hello, World!'
if __name__ == '__main__':
    app.run(debug=True)
