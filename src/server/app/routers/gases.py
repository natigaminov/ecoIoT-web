from datetime import datetime

from fastapi import APIRouter, Form


gases = APIRouter(
    prefix="/gases",
    tags=['gases']
)

@gases.post(
    path="/oxides"
)
async def oxides(
    api_token: str = Form(),
    time: datetime = Form(),
    temperature: float = Form(),
    humidity: float = Form(),
    pressure: float = Form(),
    co: float = Form(),
    no: float = Form(),
    co2: float = Form(),
    no2: float = Form()
):
    return api_token, time, temperature, humidity, pressure, co, no, co2, no2

@gases.post(
    path="/hydrides",
)
async def hydrides(
    api_token: str = Form(),
    time: datetime = Form(),
    temperature: float = Form(),
    humidity: float = Form(),
    pressure: float = Form(),
    nh3: float = Form(),
    h2s: float = Form(),
    ch4: float = Form()
):
    return api_token, time, temperature, humidity, pressure, nh3, h2s, ch4