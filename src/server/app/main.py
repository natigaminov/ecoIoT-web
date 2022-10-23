from fastapi import FastAPI
from uvicorn import run

from app.routers.gases import gases

from app.libs.postgresql.postgresql import PostgreSQL
import asyncio

app = FastAPI(
    title="EcoIoT",
    description="Recieve data from sensors",
)
app.include_router(gases)


def main() -> None:
    run(
        app,
        host='0.0.0.0',
        port=8085,
        access_log=True
    )

psql = PostgreSQL()


async def test():
    await psql.create_database("gases")
    await psql.create_database("waters")

    print(psql.engines)

asyncio.run(test())