from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from webdriver_manager.chrome import ChromeDriverManager
import time
from bs4 import BeautifulSoup
from fake_useragent import UserAgent


ua = UserAgent()
options = webdriver.ChromeOptions()
options.add_argument(f'user-agent={ua.random}')
driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)
wait = WebDriverWait(driver, 10)

try:
    with open('./rest_data.txt', 'a', encoding='utf-8') as f:
        for i in range(1, 178):
            url = f"https://www.tripadvisor.in/Restaurants-g304556-oa{30*i}-Chennai_Madras_Chennai_District_Tamil_Nadu.html"
            driver.get(url)

            wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, '.THBFE f e')))

            page_source = driver.page_source
            soup = BeautifulSoup(page_source, 'lxml')

            restaurant_names = soup.find_all('a', {'class': 'BMQDV _F Gv wSSLS SwZTJ FGwzt ukgoS'})
            rating_titles = soup.find_all('title', {'id': ':lithium-r3:'})

            for link, rating in zip(restaurant_names, rating_titles):
                f.write(f"{link.text} : {rating.text}\n")
            time.sleep(10)
finally:
    driver.quit()
