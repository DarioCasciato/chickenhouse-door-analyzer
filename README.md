# Automatic Chicken Door Analyzer

## Description

An ESP8266-based analytics tool designed to monitor and log the behavior of an automatic chicken door operated by a light sensor. This project captures door states and correlates them with sunrise and sunset times to provide data-driven insights.

## Installation

1. Clone this repository.
2. Install the required libraries.
3. Flash the firmware onto your ESP8266.

## How it Works

### State Management

The firmware uses a state machine to manage different functionalities. The two main states are:

1. **Idle State (`st_idle`)** : In this state, the system listens for changes in the reed sensor to detect if the chicken door is opening or closing. When a change is detected, the current time and either the sunrise or sunset time are logged into flash memory.
2. **Flash Reading State (`st_flashReading`)** : This state is responsible for reading the logged events from flash memory and displaying them for analysis.

#### Idle State

* **Reed Sensor Positive Edge** : When the reed sensor detects a door closing, the current Unix timestamp and the sunset time are captured and logged into flash memory.
* **Reed Sensor Negative Edge** : When the reed sensor detects a door opening, the current Unix timestamp and the sunrise time are captured and logged into flash memory.

#### Flash Reading State

In this state, the system reads all the logged open and close events from flash memory and logs them for analysis.


## Contributing

Contributions to improve this template repository are always welcome. If you find any issues or have suggestions for enhancements, please open an issue or submit a pull request.

## License

This template repository is licensed under the [MIT License](LICENSE). Feel free to use it as a starting point for your own firmware projects.
