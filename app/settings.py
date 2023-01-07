from pydantic import BaseSettings

class Settings(BaseSettings):
    """Хранит в себе данные из .env файла pydantic сам подхватывает их из файла
    главное, чтобы имена переменных в файле и имена полей класса были одинаковые
    """
    dbms_admin_login: str
    dbms_admin_pwd: str
    dbms_host: str

    gases_database_name: str
    
    api_access_token: str
    
    class Config:
        env_file = ".env"
        allow_mutation = False

settings = Settings()