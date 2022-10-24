from datetime import datetime
from fastapi import APIRouter, Form, status, Depends
from fastapi.responses import PlainTextResponse

from app.settings import settings
from app.schemas.responses import SuccessfulResponse, ForbiddenResponse
from app.repositories.measure import MeasureRepository


gases = APIRouter(
    prefix=f"/{settings.gases_database_name}",
    tags=[settings.gases_database_name]
)
endpoint_responses={
    status.HTTP_200_OK: {"model": SuccessfulResponse},
    status.HTTP_403_FORBIDDEN: {"model": ForbiddenResponse}
}

@gases.post(
    path="/oxides",
    response_class=PlainTextResponse,
    responses=endpoint_responses
)
async def oxides(
    api_token: str = Form(),
    time: datetime = Form(default=None),
    temperature: float = Form(),
    humidity: float = Form(),
    pressure: float = Form(),
    co: float = Form(),
    no: float = Form(),
    co2: float = Form(),
    no2: float = Form(),
    measure: MeasureRepository = Depends()
):
    if api_token == settings.api_access_token:
        kwargs = locals()
        kwargs["time"] = kwargs["time"].replace(tzinfo=None) if kwargs["time"] else None
        measures = {key:kwargs[key] for key in kwargs if key not in ["api_token", "measure"]}

        await measure.set_oxide_measures(measures)
    else:
        return PlainTextResponse(
            status_code=status.HTTP_403_FORBIDDEN,
            content=ForbiddenResponse().message
        )
    return PlainTextResponse(
        status_code=status.HTTP_200_OK,
        content=SuccessfulResponse().message
    )


@gases.post(
    path="/hydrides",
    response_class=PlainTextResponse,
    responses=endpoint_responses
)
async def hydrides(
    api_token: str = Form(),
    time: datetime = Form(default=None),
    temperature: float = Form(),
    humidity: float = Form(),
    pressure: float = Form(),
    nh3: float = Form(),
    h2s: float = Form(),
    ch4: float = Form(),
    measure: MeasureRepository = Depends()
):
    if api_token == settings.api_access_token:
        kwargs = locals()
        kwargs["time"] = kwargs["time"].replace(tzinfo=None) if kwargs["time"] else None
        measures = {key:kwargs[key] for key in kwargs if key not in ["api_token", "measure"]}
        
        await measure.set_hydride_measures(measures)
    else:
        return PlainTextResponse(
            status_code=status.HTTP_403_FORBIDDEN,
            content=ForbiddenResponse().message
        )
    return PlainTextResponse(
        status_code=status.HTTP_200_OK,
        content=SuccessfulResponse().message
    )