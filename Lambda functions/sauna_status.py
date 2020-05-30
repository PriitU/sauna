import os
import boto3
from boto3.dynamodb.conditions import Key, Attr
import time
import numpy as np
from scipy import stats
from datetime import datetime
from dateutil import tz

def lambda_handler(event, context):

    dynamodb = boto3.resource('dynamodb', region_name=os.environ['AWS_REGION'])
    table = dynamodb.Table(os.environ['TABLE'])
    TZ = tz.gettz('Europe/Tallinn')

    ts = int(time.time())
    tsLastWeek = ts - 1800 # 24h : 86400
    #print(ts,tsLastWeek)

    dt_object = datetime.fromtimestamp(ts, TZ)
    year = dt_object.year

    data = table.query(
        ProjectionExpression="#ts, air, water, sauna", #uv, humidity, airPressure
        ExpressionAttributeNames={ "#ts": "timestamp" },
        KeyConditionExpression=Key('year').eq(year) & Key('timestamp').gte(tsLastWeek)
    )

    items = data['Items']

    y = np.array([int(item['sauna']) for item in items])
    x = np.array([int(item['timestamp']) for item in items])

    slope, intercept, r_value, p_value, std_err = stats.linregress(x, y)
    print("slope: %f    intercept: %f" % (slope, intercept))


    if slope > 0.20:
        status = 'heating'
    elif abs(slope) < 0.10:
        status = 'stable'
    elif slope < -0.10:
        status = 'cooling'
    else:
        status = 'not sure'

    return status
