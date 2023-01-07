from pydantic import BaseModel

class DataBase(BaseModel):
    name: str
    folder: str