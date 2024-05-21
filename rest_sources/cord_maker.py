import urllib.parse
import requests
import urllib

API_KEY = "Asy8n0risQlPzXgXmk-fiCHB6GTBFa2DqDVgAuemQp4_l3u8nG0_LLNQbdApIxhM"

file = open("city_wise_rests/zomato_chennai.txt")
lines = file.readlines()
file.close()

def get_name(url):
    return url.split(":")[0].strip()

def get_loc(url):
    return url.split(":")[-1]

def clean_loc(loc):
    loc = loc.split(',')[::-1]
    for place in range(len(loc)):
        loc[place] = loc[place].strip()
    return "/".join(loc)

def sanitize_url(url):
    nc = url.count('&')
    uc = url.count('?')
    return url.replace('&', 'and', nc-1).replace('?','', uc-1)


#test = "Peshawri - ITC Grand Chola : 4.4 : North Indian : ₹6,500 for two : 99, Vidya Theertha Nagar, St. Mary’s Road, Chennai, Tamil Nadu 600018 "


final_details = []
for line in lines:
    name = get_name(line)
    loc = get_loc(line)
    loc = clean_loc(loc)
    url = "http://dev.virtualearth.net/REST/v1/Locations/%s/%s?key=%s&maxResults=1"%(loc,name,API_KEY)
    url = sanitize_url(url)

    res = requests.get(url=url)
    if res.status_code != 200:
        print("ERROR: ", url)
        final_details.append(f"ADDRESS NOT FOUND: {lines.index(line)}")
    else:
        # final_details.append(line)
        data = res.json()
        lat,long = data['resourceSets'][0]['resources'][0]['point']['coordinates']
        final_details.append(line.rstrip() + f" : {lat} : {long}\n")

f = open("city_wise_rests/zomato_chennai", 'w')
f.writelines(final_details)
f.close()