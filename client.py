import requests

# URL of the Flask API on the server
api_url = 'http://61c8-35-225-43-53.ngrok-free.app/get_data'  # Replace with your server's IP
#api_url = 'http://4cfe-35-225-43-53.ngrok-free.app/teste'  # Replace with your server's IP
try:
    # Sample data to send to the server


    data_to_send = [

        {
            "AccX": 0.09,
            "AccY": 0.34,
            "AccZ": 0.29,
            "GyroX": 0.00,
            "GyroY": 0.02,
            "GyroZ": -0.02
        },

    ]

    # Send a POST request to the Flask API with the data as a JSON payload
    #data_teste = {"Teste":"Oi"}
    response = requests.post(api_url,json=data_to_send)
    if response.status_code == 200:
        try:
            #predicted_class = response.json()['Predicted Class']
           # print('Predicted Class:', predicted_class)
            print(response.text)
        except ValueError:
            print('Error: Invalid JSON response')
    else:
        print('Error:', response.text)
except Exception as e:
    print('Error:', str(e))
