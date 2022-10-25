import asyncio
from fastapi import FastAPI
from uvicorn import run
from app.schemas.database import DataBase

from app.utils import prepare_dbms
from app.routers.gases import gases
from app.settings import settings


app = FastAPI(
    title="EcoIoT",
    description="Recieve data from sensors",
)
app.include_router(gases)

databases = [
    DataBase(
        name=settings.gases_database_name,
        folder="app/libs/postgresql/gases_database"
    )
]

def main() -> None:
    asyncio.run(
        prepare_dbms(databases)
    )

    run(
        app,
        host='0.0.0.0',
        port=8080,
        access_log=True
    )