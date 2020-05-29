import os
import boto3
from boto3.dynamodb.conditions import Key, Attr
import time
from datetime import datetime
from dateutil import tz

def lambda_handler(event, context):

    dynamodb = boto3.resource('dynamodb', region_name=os.environ['REGION'])
    table = dynamodb.Table(os.environ['TABLE'])
    TZ = tz.gettz('Europe/Tallinn')

    ts = int(time.time())
    tsLastWeek = ts - 86400 # 24h : 86400
    print(ts,tsLastWeek)

    dt_object = datetime.fromtimestamp(ts, TZ)
    year = dt_object.year

    data = table.query(
        ProjectionExpression="#ts, air, water, sauna", #uv, humidity, airPressure
        ExpressionAttributeNames={ "#ts": "timestamp" },
        KeyConditionExpression=Key('year').eq(year) & Key('timestamp').gte(tsLastWeek)
    )

    items = data['Items']

    for item in items:
        #item["uv"] = item["uv"]/100
        item["air"] = item["air"]/100
        item["water"] = item["water"]/100
        item["sauna"] = item["sauna"]/100
        item["timestamp"] = (item["timestamp"]+10800)*1000

    return items[::10]
