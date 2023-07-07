import socket
import urllib.parse
#server to run machine learning code
#ajustar depois para o que for necessário 


#Host do meu computador
host = "192.168.1.17"  # Replace with your server's IP address
port = 80  # Make sure it matches the port used in the Arduino code

# Create a TCP/IP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the host and port
server_socket.bind((host, port))

# Listen for incoming connections
server_socket.listen(1)
print(f"Server listening on {host}:{port}")

while True:
    # Wait for a client to connect
    client_socket, client_address = server_socket.accept()
    print(f"Client connected: {client_address[0]}:{client_address[1]}")

    # Receive and print the client's request
    request = client_socket.recv(1024).decode('utf-8')
    print("Received data from client:")
    print(request)

    # Extract the value from the received data
    query_params = urllib.parse.parse_qs(request.split('\n')[-1])
    value = query_params.get('teste', [''])[0]

    print(f"Value of 'teste': {value}")

    # Send a response back to the client
    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello, Client!"
    client_socket.sendall(response.encode('utf-8'))

    # Close the connection with the client
    client_socket.close()
