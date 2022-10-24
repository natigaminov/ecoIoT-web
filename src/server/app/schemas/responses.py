from pydantic import BaseModel

class ForbiddenResponse(BaseModel):
    message: str = "Invalid API token"

class SuccessfulResponse(BaseModel):
    message: str = "OK"