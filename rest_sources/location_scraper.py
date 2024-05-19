from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
import time
from bs4 import BeautifulSoup

driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))

url = "https://www.zomato.com/india"
driver.get(url)

# Wait for JavaScript to load
time.sleep(30)

soup = BeautifulSoup(driver.page_source, 'lxml')

loc_urls = soup.find_all('a')

with open('locations.txt', 'w', encoding='utf-8') as file:
    for loc in loc_urls:
        # Check if 'href' attribute exists before trying to access it
        if 'href' in loc.attrs and loc['href'].startswith('https://www.zomato.com/'):
            file.write(f"{loc['href']}\n")

print("successful")

# Clean up
driver.quit()
