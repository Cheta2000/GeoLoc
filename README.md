# GeoLoc

GeoLoc is a desktop application built using Qt6, C++, and SQLite. It allows users to input geolocation-related data, such as an IP address or a domain, and stores the information in an SQLite database. The app also integrates with an external API (IPStack) to fetch geolocation data based on the user input.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Setup](#setup)
- [Running the Application](#running-the-application)
- [Usage](#usage)

## Features

- **Main Window**: The UI contains a text field and three buttons.
- **Database Integration**: App stores geolocation data into an SQLite database.
- **Geolocation API**: Uses an external API (IPStack) to fetch geolocation data.

## Prerequisites

Make sure the following software is installed on your system before setting up and running GeoLoc:

- **Qt6** (version 6.0 or later)
- **CMake** (version 3.14 or later)
- **g++** (for C++ compilation)
- **SQLite** (for database management)

Install dependencies on a Debian-based system:

```bash
sudo apt-get install qt6-base-dev qt6-widgets-dev qt6-sql-dev sqlite3 libsqlite3-dev cmake g++
```

## Setup

### 1. Set API key

Create account on https://ipstack.com. Generate API key.

```bash
export GEO_API_KEY=your_api_key
```

### 2. Run the setup script

```bash
cd scripts
chmod +x setup_env.sh
./setup_env.sh
```

## Running the Application

### 1. Build the Project

Create a build directory and compile the application:

```bash
mkdir build
cd build
cmake ..
make
```

### 2. Run the Application

Once built, you can run GeoLoc with the following command:

```bash
./GeoApp
```

You can also use dedicated script:

```bash
cd scripts
chmod +x run.sh
./run.sh
```

To run tests:

```bash
ctests
```

## Usage

- The application displays a window with a text field and three buttons.
  - **ADD**: Get the geolocation (using the external API) of given URL or IP and save in the SQLite database.
  - **DELETE**: Delete the row with given URL or IP from the database.
  - **SEARCH**: Searche geolocation of given URL or IP in the database.

### Example Workflow

1. Enter an IP address or domain in the text field.
2. Click **ADD** to store its geolocation in the database.
3. Click **SEARCH** to retrieve and display geolocation data.
