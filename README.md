# Explainable-AI-for-Solar-Energy-Prediction

This project explores the application of Explainable AI (XAI) techniques for predicting energy output and detecting anomalies in solar energy systems. By integrating XAI methods with advanced machine learning algorithms—including neural networks, decision trees, and ensemble methods—we aim to create a comprehensive framework that optimizes solar energy generation and enhances system reliability.

By analyzing historical energy data, weather patterns, and environmental factors, this approach identifies key patterns, trends, and anomalies affecting solar energy output. This enables proactive maintenance, fault detection, and performance optimization, ultimately contributing to more efficient and reliable solar energy systems.

# Hardware Configuration

Microcontroller: ESP32 Wi-Fi Module
Sensors:
DHT11: Measures temperature and humidity.
Voltage Sensor: Monitors voltage output from the solar panel.
LDR (Light Dependent Resistor): Measures light intensity.
Solar Panel: Captures solar energy.

# Data Acquisition System
Sensor data and solar panel readings were gathered using the ESP32 microcontroller, which wirelessly connected to the internet via Wi-Fi. This microcontroller transmitted the data to ThingSpeak, an IoT platform, where it was stored for analysis. After logging, the data was exported for further examination and utilized in the research for solar energy prediction and anomaly detection.

# Illustration of Circuit Configuration

![Circuit Setup](https://github.com/user-attachments/assets/8ed445d9-38be-4a9a-a5c1-14c5af91e84f)



