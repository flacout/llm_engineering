import modal
from modal import App, Image

# Setup
# create the modal App
# describe infrastructure: use linux debian, pip install request
app = modal.App("hello")
image = Image.debian_slim().pip_install("requests")

# Hello!
@app.function(image=image)
def hello() -> str:
    import requests
    
    response = requests.get('https://ipinfo.io/json') # return the ip of the caller
    data = response.json()
    city, region, country = data['city'], data['region'], data['country']
    return f"Hello from {city}, {region}, {country}!!"
