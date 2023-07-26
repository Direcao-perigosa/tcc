import requests

# URL of the Flask API on the server
api_url = 'http://192.168.1.17:5000/classify'  # Replace with your server's IP

try:
    # Sample data to send to the server
    data_to_send = [0.667560, -0.038610, 0.231416, -0.054367, -0.007712, 0.225257]

    # Send a POST request to the Flask API with the data as a JSON payload
    response = requests.post(api_url, json={'data': data_to_send})

    # Check if the request was successful (status code 200)
    if response.status_code == 200:
        # The server will return the reshaped data as a response
        reshaped_data = response.json()['data_array']  # Use 'data_array' here, not 'reshape'
        print('Reshaped Data:', reshaped_data)
    else:
        print('Error:', response.json())
except Exception as e:
    print('Error:', str(e))
