# Use a suitable base image
FROM python:3.11-slim

# Set the working directory for your app within the container
WORKDIR /app

# Copy your dependencies file
COPY requirements.txt requirements.txt

# Install the required dependencies
RUN pip install -r requirements.txt

# Copy your application code into the image
COPY . .

EXPOSE 8822

# Specify the command to execute when the container starts
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8822"]
