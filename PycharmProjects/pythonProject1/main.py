import json
import os
import re

####
from xml import etree

import requests
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By

options = Options()
options.add_argument('--no-sandbox')  # 解决DevToolsActivePort文件不存在的报错
options.add_argument('window-size=1920x3000')  # 指定浏览器分辨率
options.add_argument('--disable-gpu')  # 谷歌文档提到需要加上这个属性来规避bug
options.add_argument('--hide-scrollbars')  # 隐藏滚动条, 应对一些特殊页面
# options.add_argument('--headless')#linux一定要用   隐藏浏览器
wd = webdriver.Chrome(service=Service(r"D:\chromedriver_win32_101.0.4951.41\\chromedriver.exe"), options=options)
# https://search.bilibili.com/video?keyword='苹果'&from_source=webtop_search&spm_id_from=333.1007&page=1&o=30


with open('save_len2_50_in_rank_all2_web+ofa_words_times_n_30000.json','r',encoding='utf-8')as f:
    keyword_list = list(json.load(f).keys())
for keyword in keyword_list:
    nums_page = 30
    save_folder = 'bilibili_' + keyword  # 保存很多个save_json_per_page

    if not os.path.exists(save_folder):
        os.mkdir(save_folder)
    else:
        continue


    for i in range(1, nums_page + 1):
        save_json_per_page = 'bilibili_{}_page{}.json'.format(keyword, i)  # 每一页保存为一个json  {url1:title1,...}
        url = "https://search.bilibili.com/video?keyword={}&from_source=webtop_search&spm_id_from=333.1007&page={}&o={}".format(
            keyword, i, i * 30)  # 1-30  2-60
        # 对视频主页发送请求，获取响应
        wd.get(url)  # 1-30  2-60)

        # 设置最大等待时长为 10秒
        wd.implicitly_wait(10)  ###千万要加上，不然后面elements加载延迟，就无法打印

        url_title_dic = {}
        elements = wd.find_elements(By.CSS_SELECTOR,
                                    'a[href^="//www"][target=_blank][data-idx=all][data-ext=click]')  # a[href^="//www"]  以什么开头
        for element in elements:
            ele = (element.get_attribute('outerHTML'))  # class 'str'
            try:
                url_title = re.findall('<a href="//(.*?)" target="_blank" data-v-62341667="" data-mod="search-card" data-idx="all" data-ext="click"><h3 class="bili-video-card__info--tit" title="(.*?)" data-v-62341667="">',ele)
                # [(url,title)]
                if (len(url_title) == 1):
                    url_title_dic['https://'+url_title[0][0]] = url_title[0][1]
                    ###################根据url下载视频#############
                    url_ = 'https://'+url_title[0][0]
                    # #手动构造请求头的参数
                    headers = {
                        'User-Agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.41 Safari/537.36",
                        'Cookie': "_uuid=5153E88A-59D5-781D-382E-8722D512D26609183infoc; buvid4=3079BA34-505B-A455-7138-105AFF9641D796730-022020421-5tvc85fCeqioMaiBYlCXsw==; buvid3=A5F6E3E0-4F12-0EAB-FA6A-BA1FDD2E5BAC10673infoc; b_nut=1647424609; i-wanna-go-back=-1; nostalgia_conf=-1; CURRENT_BLACKGAP=0; rpdid=|(umkmJ~|uJ)0J'uYR~Rk)uRk; fingerprint=630aac0ea364ba115c3f563f8232e885; buvid_fp_plain=undefined; buvid_fp=630aac0ea364ba115c3f563f8232e885; DedeUserID=357527535; DedeUserID__ckMd5=c4c968312dfb7fc0; SESSDATA=6cb1c121,1667119652,5e3e4*51; bili_jct=237a9a39b192e826bde83bceae51fa8f; b_ut=5; blackside_state=0; CURRENT_QUALITY=64; sid=iq4xiym2; bp_video_offset_357527535=656217762427830300; bsource=search_baidu; innersign=1; PVID=4; CURRENT_FNVAL=4048; b_lsid=92764539_1808E9D6599",
                        'Referer': url_
                    }
                    # # 对视频主页发送请求，获取响应
                    response_ = requests.get(url_, headers=headers)
                    html_ = response_.text
                    # print(html_)
                    '''
                    tree = etree.HTML(html_)
                    error:module 'xml.etree' has no attribute 'HTML'
                    '''

                    from lxml import html
                    tree = html.etree.HTML(html_)



                    play_info = re.findall('<script>window.__playinfo__=(.*?)</script>', html_)[0]
                    import json

                    play_info_dic = json.loads(play_info)

                    # pprint.pprint(play_info_dic)
                    audio_url = play_info_dic['data']['dash']['audio'][0]['base_url']
                    video_url = play_info_dic['data']['dash']['video'][0]['base_url']

                    # print(audio_url)

                    audio_content = requests.get(url=audio_url, headers=headers).content
                    video_content = requests.get(url=video_url, headers=headers).content
                    with open(save_folder + '/' + '{}.mp3'.format(url_.replace('/', '_')), mode='wb') as f:
                        f.write(audio_content)
                    with open(save_folder + '/' + '{}.mp4'.format(url_.replace('/', '_')), mode='wb') as f:
                        f.write(video_content)
                    print('{} is successfully downloaded!'.format(url_))

                    ######################################
            except Exception as ex:
                print("出现如下异常%s" % ex)

        save_json_path = os.path.join(save_folder, save_json_per_page)
        with open(save_json_path, 'w', encoding='utf-8') as f:
            f.write(json.dumps(url_title_dic))
            print(save_json_path)

# time.sleep(10000)

# print(url_)


##
#
# def bilbili_keyword_spider(keyword,nums_page):#根据关键词爬取视频
#     save_folder = 'bilibili_'+keyword    #保存很多个save_json_per_page
#
#     if not os.path.exists(save_folder):
#         os.mkdir(save_folder)
#     else:
#         return
#     # #手动构造请求头的参数
#
#     proxies = {
#         'http': 'http://123.182.58.14:8080'
#     }
#     headers = {
#         'User-Agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.41 Safari/537.36",
#         'Cookie': "_uuid=5153E88A-59D5-781D-382E-8722D512D26609183infoc; buvid4=3079BA34-505B-A455-7138-105AFF9641D796730-022020421-5tvc85fCeqioMaiBYlCXsw==; buvid3=A5F6E3E0-4F12-0EAB-FA6A-BA1FDD2E5BAC10673infoc; b_nut=1647424609; i-wanna-go-back=-1; nostalgia_conf=-1; CURRENT_BLACKGAP=0; rpdid=|(umkmJ~|uJ)0J'uYR~Rk)uRk; fingerprint=630aac0ea364ba115c3f563f8232e885; buvid_fp_plain=undefined; buvid_fp=630aac0ea364ba115c3f563f8232e885; DedeUserID=357527535; DedeUserID__ckMd5=c4c968312dfb7fc0; SESSDATA=6cb1c121,1667119652,5e3e4*51; bili_jct=237a9a39b192e826bde83bceae51fa8f; b_ut=5; blackside_state=0; CURRENT_QUALITY=64; sid=iq4xiym2; bp_video_offset_357527535=656217762427830300; bsource=search_baidu; innersign=1; PVID=4; CURRENT_FNVAL=4048; b_lsid=92764539_1808E9D6599",
#         'Referer': 'https://search.bilibili.com'
#     }
#
#     for i in range(1,nums_page+1):
#         time.sleep(random.uniform(0,0.3))
#         save_json_per_page = 'bilibili_{}_page{}.json'.format(keyword,i)  # 每一页保存为一个json  {url1:title1,...}
#         url_ = "https://search.bilibili.com/video?keyword={}&from_source=webtop_search&spm_id_from=333.1007&page={}&o={}".format(keyword,i,i*30)  # 1-30  2-60
#         # # 对视频主页发送请求，获取响应
#         response_ = requests.get(url_,proxies=proxies)  # ,headers=headers
#         response_.encoding = 'utf-8'
#         html_ = response_.text
#         # tree = etree.HTML(html_)
#
#         play_info2 = re.findall(
#             '<li class="video-item matrix"><a href="//(.*?)" title=(.*?)target="_blank" class="img-anchor">', html_)
#
#         save_json_path = os.path.join(save_folder,save_json_per_page)
#         with open(save_json_path,'w',encoding='utf-8')as f:
#             dic_per_page = {}
#             for part_url in play_info2:               #('www.bilibili.com/video/BV1wA4y1S78p?from=search', '"【穆祉丞/张峻豪】重庆八中《青苹果乐园》" ')
#                 url = 'https://'+part_url[0]          #https://www.bilibili.com/video/BV1yr4y1876N?from=search
#                 title = part_url[1]
#                 dic_per_page[url] = title
#             print(dic_per_page)
#             f.write(json.dumps(dic_per_page))
#
#
# if __name__ == "__main__":
#     with open('save_len2_50_in_rank_all2_web+ofa_words_times_n_30000.json','r',encoding='utf-8')as f:
#         keyword_list = list(json.load(f).keys())
#     nums = len(keyword_list)
#
#     for j in range(nums//2):
#         key_list=[]
#         key_list.append(keyword_list[j])
#         key_list.append(keyword_list[nums-1-j])
#
#     # key_list = ['苹果','香蕉']
#
#     ############多进程#####################
#         process_list = []
#         from multiprocessing import Process
#         for i in range(2):
#             p = Process(target=bilbili_keyword_spider, args=((key_list[i],30)))
#             p.start()
#             process_list.append(p)
#
#         for i in process_list:
#             p.join()
#         print('结束')
#
#     # bilbili_keyword_spider('苹果',10)
