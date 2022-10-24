import asyncio
from fastapi import FastAPI
from uvicorn import run

from app.utils import init_database
from app.routers.gases import gases
from app.settings import settings


app = FastAPI(
    title="EcoIoT",
    description="Recieve data from sensors",
)
app.include_router(gases)

async def prepare_dbms():
    await asyncio.gather(
        init_database(
            db_name=settings.gases_database_name,
            db_folder="app/libs/postgresql/gases_database"
        )
    )


def main() -> None:
    asyncio.run(prepare_dbms())

    run(
        app,
        host='0.0.0.0',
        port=8080,
        access_log=True
    )