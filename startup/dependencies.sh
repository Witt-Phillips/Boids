#!/bin/bash

# Check if Homebrew is installed
if ! command -v brew &> /dev/null
then
    echo "Homebrew not installed. Please install Homebrew first."
    exit 1
fi

# Install dependencies
brew install glfw
brew install glew
brew install glm