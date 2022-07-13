from http.cookiejar import Cookie
from lib2to3.pgen2 import token
import requests

# 定制请求头
headers={
    'user-agent':'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.0.0 Mobile Safari/537.36',
    'mweibo-pwa':'1',
    'x-requested-with': 'XMLHttpRequest',
    'cookie':'_T_WM=93695650748; WEIBOCN_FROM=1110005030; SUB=_2A25PyhaRDeRhGeBL7FUQ8S7Pwj2IHXVtNLrZrDV6PUJbktCOLWrCkW1NRsxyVUO8FVopeRv2h9uf6GCVTvPfWv1N; SUBP=0033WrSXqPxfM725Ws9jqgMF55529P9D9Wh4v8o11NG8buTpzWiFwCTy5NHD95QcSKMNeK27e0.pWs4Dqc_hi--fi-z7iKysi--NiK.4i-i2i--ciK.Ri-8si--Xi-zRi-8Wi--fi-z7iKysi--NiK.ci-8si--fi-82iK.7eK-Ne7tt; SSOLoginState=1657693890; MLOGIN=1; M_WEIBOCN_PARAMS=oid%3D4790777764645579%26lfid%3D102803%26luicode%3D20000174; XSRF-TOKEN=fb62db'
}
# 使用session记录Cookie
session = requests.Session()
session.headers.update(headers)

config_headers = {
    # 一般 referer（请求来源页面）、origin（谁发起的请求）、host（主机名及端口号）字段也常被用于反爬虫，当我们的爬虫无法正常获取数据时，我们可以将请求头里的这些字段照搬进请求头 headers，自己试着来推断网站的反爬机制。
    'origin':'https://m.weibo.cn',
    'referer':'https://m.weibo.cn',
}
session.headers.update(config_headers)

# 获取token
config_req = session.get('https://m.weibo.cn/api/config')
config = config_req.json()
st = config['data']['st']

# 发送微博所需请求头
compose_headers = {
    'origin':'https://m.weibo.cn',
    'referer':'https://m.weibo.cn/compose/',
    'x-xsrf-token': st
}
session.headers.update(compose_headers)
# from Data 里面的三个参数，
compose_data = {
    'content': 'jby发了一条微博',
    'st': st,
    #_spr 的值看起来是屏幕大小，经测试，发现是无关紧要的参数，可以不必传入。
}
compose_req = session.post('https://m.weibo.cn/api/statuses/update',data=compose_data)
print(compose_req.json())