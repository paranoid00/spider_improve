from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import requests
import time
import urllib.request
import os
import re
import platform
from lxml import etree
from datetime import datetime

def save_img(img,file_name):

    file_path ='xianxian'
    file_suffix = os.path.splitext(img)[1]
    filename = '{}{}{}{}'.format(file_path,os.sep,file_name,file_suffix)
    # f=open(file_path+'/'+str(file_name)+file_suffix,"wb")
    # f.write(img_url.text)

    urllib.request.urlretrieve(img,filename = filename)

url = 'https://s.weibo.com/weibo?q=x%E7%8E%96%E5%B0%91%E5%B9%B4%E5%9B%A2%E8%82%96%E6%88%98&wvr=6&b=1#_loginLayer_1563352028136&Refer=SWeibo_box'
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36'}

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

picture = driver.find_elements_by_xpath('//li/img')
m=1
for i in picture:
    img = i.get_attribute("src")
    save_img(img,m)
    m+=1
    print(img)
    
    














