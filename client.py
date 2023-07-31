import requests

# URL of the Flask API on the server
#api_url = 'http://192.168.1.17:5000/classify'  # Replace with your server's IP
api_url = 'http://luisacavalcante.pythonanywhere.com/classify'  # Replace with your server's IP

try:
    # Sample data to send to the server
    data_to_send = [0.667560, -0.038610, 0.231416, -0.054367, -0.007712, 0.225257]

    # Send a POST request to the Flask API with the data as a JSON payload
   # response = requests.post(api_url, json={'data': data_to_send})
    response = requests.post(api_url)

    if response.status_code == 200:
        try:
            reshaped_data = response.json()['data_array']
            print('Reshaped Data:', reshaped_data)
        except ValueError:
            print('Error: Invalid JSON response')
    else:
        print('Error:', response.text)
except Exception as e:
    print('Error:', str(e))
