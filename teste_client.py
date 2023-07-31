import requests

def call_flask_app():
    url = 'http://127.0.0.1:5000/get_data'

    try:
        response = requests.get(url)
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
