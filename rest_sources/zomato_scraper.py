from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
import time, random
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains
from bs4 import BeautifulSoup

# Setup Selenium with Chrome
driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))

loc_file = open('rest_sources\locations.txt', 'r')

urls = loc_file.readlines()

loc_file.close()

actions = ActionChains(driver)

for url in urls:
    if url.startswith('#'):
        continue
    driver.get(url.rstrip())

    # Wait for JavaScript to load
    time.sleep(30)

    actions.scroll_by_amount(0,250).perform()
    time.sleep(random.randint(15,30))
    actions.scroll_by_amount(0,250).perform()
    time.sleep(random.randint(10,20))
    actions.scroll_by_amount(0,250).perform()

    # Save the page source
    page_source = driver.page_source
    soup =BeautifulSoup(page_source, 'lxml')

    rest_block = soup.find_all('h4', {'class': 'sc-1hp8d8a-0 sc-ertOQY hArupt'})
    rating = soup.find_all('div', {'class': 'sc-1q7bklc-1 cILgox'})
    categories = soup.find_all('p', {'class': 'sc-1hez2tp-0 sc-iEPtyo bHxcOC'})
    avg_cost = soup.find_all('p', {'class': 'sc-1hez2tp-0 sc-iEPtyo dJHUYi'})
    addrs = soup.find_all('p', {'class': 'sc-1hez2tp-0 sc-gUlUPW icrStE'})
    with open(f'zomato_{url[23:].rstrip()}', 'w', encoding='utf-8') as file:
        for name,rat,cats,cost,addr in zip(rest_block,rating,categories,avg_cost,addrs):
            file.write(f"{name.text} : {rat.text} : {cats.text} : {cost.text} : {addr.text}\n")
    

# Clean up
driver.quit()
