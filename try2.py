import requests

url = f"https://www.tripadvisor.in/Restaurants-g304556-oa60-Chennai_Madras_Chennai_District_Tamil_Nadu.html"

headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3'}

response = requests.get(url, headers=headers)

print(response.text)