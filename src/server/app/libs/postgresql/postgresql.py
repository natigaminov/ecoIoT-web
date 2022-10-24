from sqlalchemy.exc import ProgrammingError
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy.ext.asyncio import create_async_engine
from sqlalchemy.engine import make_url

from app.settings import settings


class PostgreSQL:
    __instance = None
    
    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super().__new__(cls)
        return cls.__instance

    def __init__(self) -> None:
        self.dbms_admin_login = settings.dbms_admin_login
        self.dbms_admin_pwd = settings.dbms_admin_pwd
        self.dbms_host = settings.dbms_host
        self.engines = {
            "postgres": create_async_engine(
                            url=make_url(f"postgresql+asyncpg://{self.dbms_admin_login}:{self.dbms_admin_pwd}@{self.dbms_host}/postgres"),
                            pool_size=20,
                            max_overflow=70
                        )
        }
        self.sessionmakers = {
            "postgres": sessionmaker(
                            bind=self.engines["postgres"],
                            expire_on_commit=False,
                            class_= AsyncSession
                        )
        }
    
    async def get_sessionmakers(self) -> dict[str, sessionmaker]:
        return self.sessionmakers
    
    async def create_database(self, db_name: str):
        try:
            async with self.sessionmakers["postgres"]() as db:
                await db.execute("COMMIT")
                await db.execute(f"CREATE DATABASE {db_name}")
        except ProgrammingError as err:
            print(f"WARNING: Create database {db_name} error: {err}")
        finally:
            db_engine = create_async_engine(
                                url=make_url(f"postgresql+asyncpg://{self.dbms_admin_login}:{self.dbms_admin_pwd}@{self.dbms_host}/{db_name}"),
                                pool_size=20,
                                max_overflow=70
                            )
            self.engines[db_name] = db_engine
            db_engine_sessionmaker = sessionmaker(
                                bind=self.engines[db_name],
                                expire_on_commit=False,
                                class_= AsyncSession
                            )
            self.sessionmakers[db_name] = db_engine_sessionmaker

psql = PostgreSQL()