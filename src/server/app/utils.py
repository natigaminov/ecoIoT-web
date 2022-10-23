import io
import sys
import psycopg2
from sqlalchemy import create_engine, MetaData
from sqlacodegen.codegen import CodeGenerator

from settings import settings


def generate_model(database_name: str, outfile: str = None):
    psql_dsn = f'postgresql+psycopg2://{settings.dbms_admin_login}:{settings.dbms_admin_pwd}@{settings.dbms_host}/{database_name}'
    engine = create_engine(psql_dsn)
    metadata = MetaData(engine)
    metadata.reflect()
    outfile = io.open(outfile, 'w', encoding='utf-8') if outfile else sys.stdout
    generator = CodeGenerator(metadata)
    generator.render(outfile)

def migrator(database_name: str, migrations_file: str):
    psql_dsn = f'postgresql+psycopg2://{settings.dbms_admin_login}:{settings.dbms_admin_pwd}@{settings.dbms_host}/{database_name}'
    with psycopg2.connect(psql_dsn) as connection:
        with open(migrations_file, "r") as f:
            try:
                connection.cursor().execute(f.read())
            except Exception as e:
                print(e)
                connection.rollback()