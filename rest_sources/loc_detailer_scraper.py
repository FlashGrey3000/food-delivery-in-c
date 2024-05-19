from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.service import Service
import time

# Initialize WebDriver
driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))

# File handling using context managers
with open('city_wise_rests/zomato_chennai.txt', encoding='utf-8') as file:
    rests = file.readlines()

with open('Chennai_rest_addrss.txt', 'a', encoding='utf-8') as write_file:
    # Open Bing Maps
    driver.get('https://www.bing.com/maps')
    
    wait = WebDriverWait(driver, 10)
    line_count = 0
    for line in rests:
        line_count+=1
        if line_count<=452:
            continue
        found_add = False
        line = line.strip().split(' : ')
        
        # Wait for the search bar to be clickable
        search_bar = wait.until(EC.element_to_be_clickable((By.ID, 'maps_sb')))
        
        search_bar.clear()
        time.sleep(2)  # Use minimal sleep
        
        search_text = f"{line[0]}, {line[-1]}"
        search_bar.send_keys(search_text)
        search_bar.send_keys(Keys.RETURN)
        
        # Wait for results to load
        try:
            # Wait for the results to load by checking for some map-related element
            wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, '.bm_l2NavLeft.bm_whitebg.bm_phase2.bm_tcftitlea')))  # Update with a correct selector
            time.sleep(9)  # Additional wait to ensure data is fully loaded
            
            # Check for address element and get its texticonDataList
            addr_elements = driver.find_elements(By.CSS_SELECTOR, '.iconDataList')
            #address = addr_element.text.strip()

            for ad_ele in addr_elements:
                if len(ad_ele.text)>30:
                    if ('Chennai' not in ad_ele.text) and ('Tamil Nadu' not in ad_ele.text) and ('chennai' not in ad_ele.text):
                        continue
                    print(f"Address found: {ad_ele.text}")  # Debugging output
                    write_file.write(ad_ele.text[:-8] + '\n')
                    found_add = True

            if not found_add:
                print(f"ERROR FINDING ADDRESS FOR : {search_text} ON LINE: {line_count}")
                not_found_str = f"ADDRESS NOT FOUND FOR LINE: {line_count}, : SEARCH TEXT: {search_text}"+'\n'
                write_file.write(not_found_str)

        except Exception as e:
            print(f"Error finding address for {search_text}: {e}")
            continue

# Quit the driver
driver.quit()
