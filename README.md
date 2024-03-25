The purpose of this code is for a lab assignment to become more accustomed to the technologies used in consuming APIs using embedded electronics as a web client.

The embedded client is able to make requests to endpoints: GET /api/light and PUT /api/temp. This will be done by functions getLightand patchTemp. 

getLight
This function takes the status of the light switch from the website and changes the status of the LED connected to the circuit appropriately.

patchTemp
This function takes the temperature value detected by the temperature sensor and patches the existing temperature, rewriting the value every time.
