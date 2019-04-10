#!/usr/bin/env python3

# Author: Jan Demel (xdemel01@fit.vutbr.cz)
# This script was made as a part of IPK course
# Don't copy this please...

# My API key: 419db25b1d35c32d9f83525f3bc9931c

import socket
import json
import sys

# Error codes

ERROR_ARGS = -1
ERROR_SOCKET_CONNECTION = -2
ERROR_FORMAT_OUTPUT_DATA = -3
ERROR_API_CALL = -4

# ============== Variables definitions =================

if len(sys.argv) != 3:
	print("Forbidden use of arguments.\n", file=sys.stderr)
	sys.exit(ERROR_ARGS)

if sys.argv[2] == "":
	print("Please enter city name correctly\n", file=sys.stderr)
	sys.exit(ERROR_ARGS)

api_key = sys.argv[1]
city = sys.argv[2]
host_name = "api.openweathermap.org"
port = 80
request = "GET /data/2.5/weather?q=" + city + "&APPID=" + api_key + "&units=metric HTTP/1.1\r\nHost: " + host_name + "\r\n\r\n"

# ============== Socket connection and response parsing =================

connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
	connection.connect((host_name, port))
	connection.send(request.encode())
except:
	print("Caught exception socket.error", file=sys.stderr)
	sys.exit(ERROR_SOCKET_CONNECTION)

(response_headers, response_json) = connection.recv(4096).decode().split("\r\n\r\n")
response_json = json.loads(response_json)

# ============== Handeling errors =================

if int(response_json["cod"]) != 200:
	print(response_json["message"])
	sys.exit(ERROR_API_CALL)

# ============== Printing response =================

try:
	print(response_json["name"])
	print(response_json["weather"][0]["description"])
	print("temp:" + str(response_json["main"]["temp"]) + "°C")
	print("humidity:" + str(response_json["main"]["humidity"]) + "%")
	print("pressure:" + str(response_json["main"]["pressure"]) + " hPa")
	print("wind-speed:" + str(response_json["wind"]["speed"]) + " km/h")
	print("wind-deg:" + (str(response_json["wind"]["deg"]) if ("deg" in response_json["wind"]) else "-"))
except:
	print("Error with formating output data...", file=sys.stderr)
	sys.exit(ERROR_FORMAT_OUTPUT_DATA)