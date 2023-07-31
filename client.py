import requests

def call_flask_app():
    url = 'http://127.0.0.1:5000/get_data'

    # Sample JSON data with 20 objects
    json_data = [
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        {
            'AccX': 0.667560,
            'AccY': -0.038610,
            'AccZ': 0.231416,
            'GyroX': -0.054367,
            'GyroY': -0.007712,
            'GyroZ': 0.225257
        },
        # Add 19 more JSON objects here...
    ]
    try:
        response = requests.post(url, json=json_data)  # Send a POST request with JSON data
        if response.status_code == 200:
            data = response.json()
            predicted_class = data.get('Predicted Class')
            print("Predicted Class:", predicted_class)
        else:
            print("Failed to get data from the server. Status code:", response.status_code)
    except requests.exceptions.RequestException as e:
        print("An error occurred while making the request:", e)


if __name__ == '__main__':
    call_flask_app()
