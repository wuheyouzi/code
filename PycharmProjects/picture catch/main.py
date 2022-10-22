import asyncio
import aiohttp
import aiofiles
import os

global path
path = "E:/img/"


# https://www.mihuashi.com

url = "https://www.mihuashi.com/api/v1/artworks/search"  # new / hot

headers = {
    "cookie": "aliyungf_tc=b61a8cf4221b9b59f135b5591e41997feaf1adc68d5cc8cfc2a2b40e527de2cb",
    "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) "
                  "Chrome/103.0.0.0 Mobile Safari/537.36 "
}


async def downloads(urls, param):
    name = urls.split("/")[-1]
    if os.path.exists(path + name):
        return
    async with aiohttp.ClientSession() as session:  # requests
        async with session.get(urls, params=param, headers=headers) as resp:  # resp = requests.get()
            async with aiofiles.open(path + name, mode="wb") as t:
                await t.write(await resp.content.read())  # 把下载到的内容写入到文件中


async def do_main(param):
    async with aiohttp.ClientSession() as session:  # requests
        async with session.get(url, params=param, headers=headers) as resp:  # resp = requests.get()
            json_pict = await resp.json()
            pict_list = json_pict['artworks']
            for lis in pict_list:
                ur = lis['url']
                while True:
                    try:
                        await downloads(ur, param)
                        break
                    except Exception as e:
                        print(e)

                print(f'picture over: {ur}')


async def main():
    itm = 0
    while itm + 1:
        itm += 1

        # new
        new_param = {
            'page': f'{itm}',
            'type': 'recent'
        }
        try:
            await do_main(new_param)
        except:
            await do_main(new_param)
        print("new over!", end="\n")

        # hot
        hot_param = {
            'page': f'{itm}',
            'type': 'hot',
            'duration': '7'
        }
        try:
            await do_main(new_param)
        except:
            await do_main(new_param)
        print("hot over!", end="\n")
        print(f'page {itm} over!', end='\n')


def mkdir():
    print("正在创建文件夹img")
    global path
    if path == "":
        path = "./img/"
    if not os.path.exists(path):
        os.mkdir(path)
        print("创建成功")
    else:
        print("路径已存在")
    if path[len(path) - 1] != '/':
        path += '/'


if __name__ == '__main__':
    mkdir()

    print("start!", end="\n")
    # 运行异步main函数
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main())
