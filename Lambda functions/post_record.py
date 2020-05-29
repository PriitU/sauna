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
    ts = time.time()
    dt_object = datetime.fromtimestamp(ts, TZ)

    event["timestamp"] = int(ts)
    event["date"] = dt_object.strftime('%Y-%m-%d %H:%M:%S')
    event["year"] = dt_object.year
    event["water"] = int(event["water"]*100)
    event["air"] = int(event["air"]*100)
    event["sauna"] = int(event["sauna"]*100)
    event["uv"] = int(event["uv"]*100)
    event["battery"] = int(event["battery"]*100)
    event["airPressure"] = int(event["airPressure"]*100)
    event["humidity"] = int(event["humidity"]*100)
    table.put_item(Item=event)

    return {"code":200, "message":"Item added to DB"}

    #TODO: Analysis of sauna state and custom response of next update time
