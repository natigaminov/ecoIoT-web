from pydantic import BaseSettings

class Settings(BaseSettings):
    dbms_admin_login: str
    dbms_admin_pwd: str
    dbms_host: str

    gases_database_name: str
    
    api_access_token: str
    
    class Config:
        env_file = ".env"
        allow_mutation = False

settings = Settings()