from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import requests
import time
import os
import re
import platform
from lxml import etree
from datetime import datetime







url = 'http://piyao.sina.cn/'
header = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36'}



if platform.system()=='Windows':
    chrome_driver_path = "chromedriver.exe"
elif platform.system()=='Linux'or platform.system()=='Darwin':
    chrome_driver_path="./chromedriver"
else:
    print('Unknow System Type. quit...')



    
chrome_options = Options()
#chrome_options.add_argument('--headless')
chrome_options.add_argument('--disable-gpu')
driver = webdriver.Chrome(chrome_options=chrome_options, 
    executable_path= chrome_driver_path)


driver.get(url)
time.sleep(3)
allitem = []

#逐渐滚动浏览器窗口，令ajax逐渐加载
for i in range(0,100):
    driver.execute_script('window.scrollTo(0, document.body.scrollHeight)')
    i += 1
    time.sleep(4)


for l in range(1,90):
    title = []
    number = []
    dates = driver.find_elements_by_xpath('//div[@class="zy_day" and position()='+str(l)+']/div[@class="day_date"]')
    titles = driver.find_elements_by_xpath('//div[@class="zy_day" and position()='+str(l)+']/div[@class="day_date"]/following-sibling::ul//div[@class="left_title"]')
    numbers = driver.find_elements_by_xpath('//div[@class="zy_day" and position()='+str(l)+']/div[@class="day_date"]/following-sibling::ul//div[@class="like_text"]')
    for i in numbers:
        number.append(i.text)
    for n in titles:
        title.append(n.text)
    for m in dates:
        date = m.text
    titles_numbers = zip(title,number)
    for m,n in titles_numbers:
        dic={}
        dic['title'] = m

        dic['number'] = int(n)
        dic['date'] = date
        allitem.append(dic)

driver.quit()
high_number = sorted(allitem, key=lambda x : x['number'],reverse = True)

for x in high_number:
    print('number:', x['number'], '\t','date:', x['date'],'\t','title:', x['title'])


