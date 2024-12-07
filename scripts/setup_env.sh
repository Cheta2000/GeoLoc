#!/bin/bash

# This script automates the setup of the geolocation app

install_dependencies_debian() {
    echo "Installing dependencies for Debian-based system..."

    sudo apt update

    sudo apt-get install -y qtbase6-dev qt6-qmake qtbase6-dev-tools \
            cmake g++ libsqlite3-dev
}

install_dependencies_macos() {
    echo "Installing dependencies for macOS..."

    if ! command -v brew &> /dev/null; then
        echo "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi

    brew install qt sqlite cmake
}

if [ "$(uname)" == "Linux" ]; then
    if [ -f /etc/debian_version ]; then
        install_dependencies_debian
    else
        echo "Unsupported Linux distribution. Please install dependencies manually."
        exit 1
    fi
elif [ "$(uname)" == "Darwin" ]; then
    install_dependencies_macos
else
    echo "Unsupported OS. Please install dependencies manually."
    exit 1
fi

if [ -z "$GEO_API_KEY" ]; then
    echo "GEO_API_KEY environment variable is not set. Please set it before proceeding."
    exit 1
fi

echo "Setup completed successfully."