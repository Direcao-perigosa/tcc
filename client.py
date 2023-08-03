import requests

# URL of the Flask API on the server
api_url = 'http://127.0.0.1:5000/get_data'  # Replace with your server's IP

try:
    # Sample data to send to the server
    data_to_send = [
        {
            "AccX": 0.667560,
            "AccY": -0.038610,
            "AccZ": 0.231416,
            "GyroX": -0.054367,
            "GyroY": -0.007712,
            "GyroZ": 0.225257
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        {
            "AccX": 0.123456,
            "AccY": -0.789012,
            "AccZ": 0.345678,
            "GyroX": -0.901234,
            "GyroY": -0.567890,
            "GyroZ": 0.123456
        },
        # Add more dictionaries for the remaining 18 data samples
        # ...
    ]

    # Send a POST request to the Flask API with the data as a JSON payload
    response = requests.post(api_url, json=data_to_send)

    if response.status_code == 200:
        try:
            predicted_class = response.json()['Predicted Class']
            print('Predicted Class:', predicted_class)
        except ValueError:
            print('Error: Invalid JSON response')
    else:
        print('Error:', response.text)
except Exception as e:
    print('Error:', str(e))
