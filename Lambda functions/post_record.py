import os
import boto3
from boto3.dynamodb.conditions import Key, Attr
from boto3 import client as boto3_client
import time
import json
from datetime import datetime
from dateutil import tz

lambda_client = boto3_client('lambda')

def tempAnalysis(air, sauna, hour, status):
    '''Analysis of sauna state and custom response for the next update time
        Inputs: air temperature
                sauna temperature
                current hour
        Output: Time in minutes for the next update.
    '''
    tempDiff = sauna-air
    if int(hour.hour) < 8:
        responseTime = 15
    elif status == 'heating':
        responseTime = 2
    else:
        responseTime = 10
    return responseTime

def lambda_handler(event, context):
    dynamodb = boto3.resource('dynamodb', region_name=os.environ['REGION'])
    table = dynamodb.Table(os.environ['TABLE'])
    TZ = tz.gettz('Europe/Tallinn')
    ts = time.time()
    dt_object = datetime.fromtimestamp(ts, TZ)

    invoke_res = lambda_client.invoke(FunctionName="sauna-tempDirection",
                                    InvocationType="RequestResponse"
                                    )

    status = invoke_res['Payload'].read().decode("utf-8").strip('"')

    responseT = tempAnalysis(event['air'], event['sauna'], dt_object, status)
    #print(dt_object.strftime('%-H'))

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

    print(status)
