# Task3.2CMQTT

Embedded Systems Development – Task 3.2C
MQTT-Based Smart Lighting System

Overview
In this project I implement an IoT-based smart lighting system using the MQTT publish/subscribe communication model. The system detects hand gestures either wave or pat using an ultrasonic sensor and controls two LEDs representing hallway and bathroom lights.
A wave gesture will turn the lights on and a pat gesture turns them off. The system communicates using a public MQTT broker.

How MQTT Works
MQTT (Message Queuing Telemetry Transport) is a lightweight communication protocol used in IoT systems. It is designed specifically for constrained devices and low-bandwidth, high-latency, or unreliable networks this makes it widely used in IoT systems. It operates on a publish - subscribe architecture where communication is coordinated through a central broker rather than direct device-to-device connections 

The following are the main parts of MQTT protocol.
1.	Client: Any device that connects to the broker (Arduino in this case)
2.	Broker: Central server managing communication (broker.emqx.io)
3.	Publisher: Device sending data (Arduino with ultrasonic sensor)
4.	Subscriber: Device receiving data (same Arduino system)


The workflow is a s follows:
1.	Arduino detects gesture (pat or wave)
2.	It then publishes message to topic
3.	The broker receives the message
4.	The subscriber receives message
5.	Then the LEDs respond accordingly

Hardware requirements
1.	Arduino Nano 33 IoT
2.	Ultrasonic Sensor (HC-SR04)
3.	2 × LEDs
4.	2 × Resistors (220Ω)
5.	Breadboard
6.	Jumper wires
The hardware will be setup as follows. Also refer to the diagram.json file in this repo:

![image alt](https://github.com/kuriajeremy/Task3.2CMQTT/blob/28329a7ea49cbfcf43720b3b36b83f8b73529992/ultrasonic.png)

Software Requirements
1.	Arduino Web IDE / Arduino IDE
2.	MQTT Client (MQTT Explorer recommended)
3.	Public MQTT Broker: broker.emqx.io

Pin connections on the setup
Component	Arduino Pin
TRIG	    D9
ECHO	    D10
LED1	    D5
LED2	    D6

System implementation steps
Step 1: Hardware setup is as shown above
1.	Connect ultrasonic sensor to Arduino
2.	Connect LEDs with resistors
3.	Ensure proper grounding

Step 2: Install the needed libraries
Install:
•	WiFiNINA
•	PubSubClient

Step 3: Configure WiFi
Change credentials in the code:
const char* ssid = "Wifi Name";
const char* password = "Wifi Password";

Step 4: Upload code
Using Arduino IDE, upload the code on mqtt_lights.ino  in this repository 

Step 5: MQTT setup
1.	Broker: broker.emqx.io
2.	Port: 1883
3.	Topics: ES/Wave and ES/Pat

Step 6: Testing
1.	Move hand near sensor
2.	Observe messages in MQTT Explorer
3.	Verify LEDs:
o	Wave → ON
o	Pat → OFF

System behaviour
1.	Detects the gestures using distance and time/duration
2.	Publishes MQTT messages
3.	Subscribes to MQTT topics
4.	Controls LEDs using the received messages
