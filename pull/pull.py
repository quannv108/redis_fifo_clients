import redis
import os
import time
from datetime import datetime

if __name__ == '__main__':
    print('pull starting...')
    redis_conn = redis.Redis(host=os.getenv('HOST'), port=6379, db=0)
    count = 0
    while True:
        _, v = redis_conn.brpop('abc')
        now = datetime.now()
        value = v.decode('utf-8')
        try:
            vv = datetime.strptime(value, '%Y-%m-%d %H:%M:%S.%f')
            print('get value {} take {} microsec'.format(vv, (now - vv).microseconds))
        except Exception as ex:
            print('get value error: {}'.format(ex))
            pass