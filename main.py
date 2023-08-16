#https://www.youtube.com/watch?v=vieoHqt7pxo
#servidor

import numpy as np
import pandas as pd
import tensorflow as tf
from flask import Flask, jsonify, request
from flask_ngrok import run_with_ngrok
import joblib

app = Flask(__name__)
run_with_ngrok(app)

def get_data(json_data):
    # Sample JSON data with 10 objects

    # Convert JSON data to a DataFrame
    motion_data_test = pd.DataFrame(json_data, columns=['AccX', 'AccY', 'AccZ', 'GyroX', 'GyroY', 'GyroZ'])
    print(json_data)
    # Convert the DataFrame to a numpy array
    motion_data_array = motion_data_test.to_numpy()


    reshaped_motion_data = motion_data_array.reshape(1, -1)

    # Load the LSTM model
    model = joblib.load('/content/drive/My Drive/tcc/model_svm')
    # Make prediction
    predicted_values = model.predict(reshaped_motion_data)

    # Define the threshold for classification
    threshold = 0.5

    # Convert the predicted values to binary classification (NORMAL or AGGRESSIVE)
    predicted_values = model.predict(reshaped_motion_data)

    return predicted_values.tolist()

@app.route('/get_data', methods=['POST'])
def predict_data():
    json_data = request.get_json()
    predicted_class = get_data(json_data)
    return jsonify({"Predicted Class": predicted_class})
@app.route('/')
def hello():
    return 'Hello, World!'

@app.route('/teste', methods=['POST'])
def teste():
    json_data = request.get_json()
    print(json_data)
    return json_data
if __name__ == '__main__':
    app.run()