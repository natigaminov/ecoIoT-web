import io
import sys
import psycopg2
from sqlalchemy import create_engine, MetaData
from sqlacodegen.codegen import CodeGenerator

from app.settings import settings
from app.libs.postgresql.postgresql import psql


def generate_model(db_name: str, outfile: str = None):
    """Генерирует модели для SQLAlchemy считывая данные с базы
    """
    psql_dsn = f'postgresql://{settings.dbms_admin_login}:{settings.dbms_admin_pwd}@{settings.dbms_host}/{db_name}'
    engine = create_engine(psql_dsn)
    metadata = MetaData(engine)
    metadata.reflect()
    outfile = io.open(outfile, 'w', encoding='utf-8') if outfile else sys.stdout
    generator = CodeGenerator(metadata)
    generator.render(outfile)

def migrator(db_name: str, migrations_file: str):
    """Выполняет миграции данных в БД, т.е. создает таблицы и пр. из SQL запроса
    """
    psql_dsn = f'postgresql://{settings.dbms_admin_login}:{settings.dbms_admin_pwd}@{settings.dbms_host}/{db_name}'
    with psycopg2.connect(psql_dsn) as connection:
        with open(migrations_file, "r") as f:
            try:
                connection.cursor().execute(f.read())
            except Exception as e:
                print(f"WARNING: {e}")
                connection.rollback()

async def init_database(db_name: str, db_folder: str):
    """Создает базу данных, запускает в нее миграции и после
    создает из нее модели для SQLAlchemy
    """
    await psql.create_database(db_name=db_name)
    migrator(
        db_name=settings.gases_database_name,
        migrations_file=f"{db_folder}/migrations.sql"
    )
    generate_model(
        db_name=settings.gases_database_name, 
        outfile=f"{db_folder}/models.py"
    )