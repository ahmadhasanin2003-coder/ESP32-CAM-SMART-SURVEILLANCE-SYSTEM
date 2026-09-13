# ESP32-CAM-SMART-SURVEILLANCE-SYSTEM
ESP32-CAM based smart surveillance system with real-time motion detection, Wi-Fi video streaming, SD card image capture, and web-controlled pan-tilt camera operation.

Features

- Real-time Wi-Fi video streaming
- Motion detection with bounding box highlighting
- Browser-based control interface
- SD card image capture and storage
- Servo motor camera control
- Remote monitoring from any device on the network

Hardware Used

- ESP32-CAM
- MicroSD Card
- SG90 Servo Motor
- FTDI Programmer
- Power Supply

System Architecture

Camera
   |
   v
ESP32-CAM <------> Web Interface (Browser)
   |                     |
   |                     |
   v                     v
SD Card             OpenCV Processing
   |
   v
Servo Motor Control


Working Principle

1. ESP32-CAM captures video frames.
2. The motion detection algorithm compares consecutive frames.
3. Moving objects are highlighted with a green bounding box.
4. The video stream is served through a web interface over Wi-Fi.
5. Users can capture snapshots and save them to the SD card.
6. Servo motors can be controlled remotely through the browser.
