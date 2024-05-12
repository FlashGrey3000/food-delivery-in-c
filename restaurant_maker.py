import requests
from bs4 import BeautifulSoup

# url = r"view-source:https://www.tripadvisor.in/Restaurants-g304556-oa60-Chennai_Madras_Chennai_District_Tamil_Nadu.html"

# r = requests.get(url=url)

# print(r.text)

fn = "page_source.html"

f = open(fn, 'r')

content = f.read()

soup =BeautifulSoup(content, 'lxml')

print(content.find('biGQs _P fiohW alXOW NwcxK GzNcM ytVPx UTQMg RnEEZ ngXxk'))
print(content[77415:77700])

ass = soup.find_all('a', {'class': 'BMQDV _F Gv wSSLS SwZTJ FGwzt ukgoS'})

for aaa in ass:
    print(aaa.text)