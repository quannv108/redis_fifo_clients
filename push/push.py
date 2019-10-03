import redis
import os
import time
from datetime import datetime

if __name__ == '__main__':
    print('push starting...')
    redis_conn = redis.Redis(host=os.getenv('HOST'), port=6379, db=0)
    count = 0
    while True:
        time.sleep(3)
        now = datetime.now()
        print('will push value {}'.format(now))
        redis_conn.lpush('abc', now.strftime('%Y-%m-%d %H:%M:%S.%f'))
        count += 1
