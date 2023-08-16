import requests

# URL of the Flask API on the server
api_url = 'http://b737-35-221-141-21.ngrok-free.app/get_data'  # Replace with your server's IP
#api_url = 'http://68e6-35-221-141-21.ngrok-free.app/teste'  # Replace with your server's IP
try:
    # Sample data to send to the server


    data_to_send = [

        {
            "AccX": -0.66274977,
            "AccY": -0.46277535,
            "AccZ": -0.09979725,
            "GyroX": 0.00870483,
            "GyroY": -0.009773844,
            "GyroZ": 0.046960264
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
