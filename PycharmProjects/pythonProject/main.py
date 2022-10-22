from Crypto.Cipher import AES
from base64 import b64encode
import requests
import json

url = f'https://music.163.com/weapi/comment/resource/comments/get?csrf_token=c07d7634ac8904fc3a79c0ff141e178f'

data = {
    'csrf_token': f'c07d7634ac8904fc3a79c0ff141e178f',
    'cursor': f'-1',
    'offset': f'0',
    'orderType': f'1',
    'pageNo': f'1',
    'pageSize': f'20',
    'rid': f'R_SO_4_1887276693',
    'threadId': f'R_SO_4_1887276693'
}

f = "00e0b509f6259df8642dbc35662901477df22677ec152b5ff68ace615bb7b725152b3ab17a876aea8a5aa76d2e417629ec4ee341f56135fccf695280104e0312ecbda92557c93870114af6c9d05c4f7f0c3685b7a46bee255932575cce10b424d813cfe4875d3e82047b97ddef52741d546b8e289dc6935b3ece0462db0a22b8e7 "
g = "0CoJUm6Qyw8W8jud"
e = "010001"
i = "d5bpgMn9byrHNtAh"

"""
    function a(a) {
        var d, e, b = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", c = "";
        for (d = 0; a > d; d += 1)
            e = Math.random() * b.length,
            e = Math.floor(e),
            c += b.charAt(e);
        return c
    }
    function b(a, b) {
        var c = CryptoJS.enc.Utf8.parse(b)
          , d = CryptoJS.enc.Utf8.parse("0102030405060708")
          , e = CryptoJS.enc.Utf8.parse(a)
          , f = CryptoJS.AES.encrypt(e, c, {
            iv: d,
            mode: CryptoJS.mode.CBC
        });
        return f.toString()
    }
    function c(a, b, c) {
        var d, e;
        return setMaxDigits(131),
        d = new RSAKeyPair(b,"",c),
        e = encryptedString(d, a)
    }
    function d(d, e, f, g) {
        var h = {}
          , i = a(16);
        return h.encText = b(d, g),
        h.encText = b(h.encText, i),
        h.encSecKey = c(i, e, f),
        h
    }
    function e(a, b, d, e) {
        var f = {};
        return f.encText = c(a + e, b, d),
        f
    }
    window.asrsea = d"""


def get_encSecKey():  # 由于i是固定的. 那么encSecText就是固定的.  c()函数的结果就是固定的
    return "1b5c4ad466aabcfb713940efed0c99a1030bce2456462c73d8383c60e751b069c24f82e60386186d4413e9d7f7a9c7cf89fb06e40e52f28b84b8786b476738a12b81ac60a3ff70e00b085c886a6600c012b61dbf418af84eb0be5b735988addafbd7221903c44d027b2696f1cd50c49917e515398bcc6080233c71142d226ebb"


# 把参数进行加密
def get_params(data):  # 默认这里接收到的是字符串
    first = enc_params(data, g)
    second = enc_params(first, i)
    return second  # 返回的就是params


# 转化成16的倍数, 为下方的加密算法服务
def to_16(data):
    pad = 16 - len(data) % 16
    data += chr(pad) * pad
    return data


# 加密过程
def enc_params(data, key):
    iv = "0102030405060708"
    data = to_16(data)
    aes = AES.new(key=key.encode("utf-8"), IV=iv.encode('utf-8'), mode=AES.MODE_CBC)  # 创建加密器
    bs = aes.encrypt(data.encode("utf-8"))  # 加密, 加密的内容的长度必须是16的倍数
    return str(b64encode(bs), "utf-8")  # 转化成字符串返回


# 发送请求. 得到评论结果
resp = requests.post(url, data={
    "params": get_params(json.dumps(data)),
    "encSecKey": get_encSecKey()
})

print(resp.text)
