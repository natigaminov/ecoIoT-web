from fastapi import Depends
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.asyncio import AsyncSession

from app.settings import settings
from app.libs.postgresql.postgresql import psql
from app.libs.postgresql.gases_database.models import (
    Oxide,
    Hydride
)


class MeasureRepository:
    def __init__(self, sessions: dict[str, sessionmaker] = Depends(psql.get_sessionmakers)) -> None:
        self.sessions = sessions
        self.gases_db_name = settings.gases_database_name
    
    async def set_oxide_measures(self, measures: dict):
        async with self.sessions[self.gases_db_name]() as db:
            db: AsyncSession
            oxides = Oxide(**measures)
            db.add(instance=oxides)
            await db.commit()

    async def set_hydride_measures(self, measures: dict):
        async with self.sessions[self.gases_db_name]() as db:
            db: AsyncSession
            hydride = Hydride(**measures)
            db.add(instance=hydride)
            await db.commit()