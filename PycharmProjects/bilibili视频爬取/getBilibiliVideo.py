import requests
import re
import json

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                  'Chrome/83.0.4103.61 Safari/537.36',
}


def main(url):
    with open('SESSDATA.txt', 'r') as f:
        SESSDATA = f.read()
    if SESSDATA == '':
        print('检测到您未设置SESSDATA,最高只能下载480p画质哦！')

    # 获取BV号
    if '?' in url:
        url = url.split('?')[0]
        print(url)
    bvid = re.search(r'BV.*', url).group()
    print('BV号：' + bvid)
    # 获取cid
    cid_json = requests.get('https://api.bilibili.com/x/player/pagelist?bvid={}&jsonp=jsonp'.format(bvid)).text
    cid = re.search(r'{"cid":(\d+)', cid_json).group()[7:]
    print('CID:' + cid)

    # 获取视频的av号
    rsp = requests.get(url, headers=headers)
    aid = re.search(r'"aid":(.*?),"', rsp.text).group()[6:-2]
    print('AV号：' + aid)

    # 抓取视频真实地址,清晰度
    qn = 16  # 先设置一个默认低清晰度
    headers['Referer'] = url
    api_url = 'https://api.bilibili.com/x/player/playurl?cid={}&avid={}&qn={}&otype=json&requestFrom=bilibili-helper'.format(
        cid, aid, qn)
    qn_dict = {}  # 用来存放清晰度选择参数
    rsp = requests.get(api_url, headers=headers).content
    rsp = json.loads(rsp)
    qn_accept_description = rsp.get('data').get('accept_description')
    qn_accept_quality = rsp.get('data').get('accept_quality')
    # print('下载视频清晰度选择')
    for i, j, xuhao in zip(qn_accept_description, qn_accept_quality, range(len(qn_accept_quality))):
        # print(str(xuhao + 1) + '：' + i)
        qn_dict[str(xuhao + 1)] = j
    # xuhao = input('请选择(输入清晰度前的标号)：')
    xuhao = "1"
    qn = qn_dict[xuhao]
    print('清晰度参数qn：' + str(qn))
    api_url = 'https://api.bilibili.com/x/player/playurl?cid={}&avid={}&qn={}&otype=json&requestFrom=bilibili-helper'.format(
        cid, aid, qn)
    print('api_url=' + api_url)
    cookies = {'SESSDATA': SESSDATA}
    rsp = requests.get(api_url, headers=headers, cookies=cookies).content  # 这里代cookies才能得到会员或者登录后才能下载的视频的链接
    rsp = json.loads(rsp)
    real_url = rsp.get('data').get('durl')[0].get('url')
    print('成功获取视频直链！')
    print(real_url)

    return real_url
