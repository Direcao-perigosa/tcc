from flask import Flask, jsonify, request
import tensorflow as tf
import numpy as np
import pandas as pd

app = Flask(__name__)

# Load your trained model
model = tf.keras.models.load_model(r"C:\Users\danin\Desktop\LSTM_MODEL")

# Define a function to reshape the data
def reshape(data):
    # Assuming you already have the motion_data_test DataFrame and the LSTM model defined

    # Sample data and new_data
    # data = [0.667560, -0.038610, 0.231416, -0.054367, -0.007712, 0.225257]

    print("entrei no reshape")
    new_data = pd.DataFrame([data],
                            columns=['AccX', 'AccY', 'AccZ', 'GyroX', 'GyroY', 'GyroZ'])

    # Create a sequence with a minimum length of 20
    min_seq_length = 20
    duplicated_data = [data] * min_seq_length

    # Convert the duplicated data to a DataFrame
    motion_data_test = pd.DataFrame(duplicated_data, columns=['AccX', 'AccY', 'AccZ', 'GyroX', 'GyroY', 'GyroZ'])

    # Convert the DataFrame to a numpy array
    motion_data_array = motion_data_test.to_numpy()

    # Reshape the array to match the LSTM input shape (None, 20, 6)
    reshaped_motion_data = np.reshape(motion_data_array, (1, min_seq_length, 6))
    return reshaped_motion_data

def predict(reshaped_motion_data):
    model = tf.keras.models.load_model(r"C:\Users\danin\Desktop\LSTM_MODEL")

    predicted_values = model.predict(reshaped_motion_data)

    # Define the threshold for classification
    threshold = 0.5

    # Convert the predicted values to binary classification (NORMAL or AGGRESSIVE)
    predicted_class = np.where(predicted_values > threshold, "AGGRESSIVE", "NORMAL")

    print("Predicted Class:", predicted_class)
    return predicted_class.tolist()

@app.route('/classify', methods=['POST'])
def get_data():
    try:
        # Get the data from the request
        data = request.json['data']
        # Reshape the data using the reshape function
        reshaped_data = reshape(data)
        reshaped_data_list = reshaped_data.tolist()
        predicted = predict(reshaped_data_list)
        print(predicted)
        json_reshape = jsonify({'data_array': predicted})
        # Return the reshaped data as a response
        return json_reshape
    except Exception as e:
        return jsonify({'error': str(e)})

# The predict() function and '/connect' endpoint remain unchanged.

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
