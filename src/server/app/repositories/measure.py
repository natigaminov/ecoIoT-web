from fastapi import Depends
from pydantic import BaseModel
from sqlalchemy.sql import select, and_
from sqlalchemy.orm import sessionmaker
from sqlalchemy.engine import ChunkedIteratorResult
from sqlalchemy.ext.asyncio import AsyncSession

from app.libs.postgresql.postgresql import PostgreSQL


class MeasureRepository:
    def __init__(self, sessions: dict[str, sessionmaker] = Depends(PostgreSQL.get_sessionmakers)) -> None:
        self.sessions = sessions
    
    async def set_measure(self, db_name: str, measure: BaseModel):
        ...