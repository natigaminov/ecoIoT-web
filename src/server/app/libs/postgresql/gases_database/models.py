# coding: utf-8
from sqlalchemy import Column, DateTime, Float, Integer, text
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()
metadata = Base.metadata


class Hydride(Base):
    __tablename__ = 'hydrides'

    id = Column(Integer, primary_key=True, server_default=text("nextval('hydrides_id_seq'::regclass)"))
    time = Column(DateTime, nullable=False, server_default=text("now()"))
    temperature = Column(Float(53))
    humidity = Column(Float(53))
    pressure = Column(Float(53))
    nh3 = Column(Float(53))
    h2s = Column(Float(53))
    ch4 = Column(Float(53))


class Oxide(Base):
    __tablename__ = 'oxides'

    id = Column(Integer, primary_key=True, server_default=text("nextval('oxides_id_seq'::regclass)"))
    time = Column(DateTime, nullable=False, server_default=text("now()"))
    temperature = Column(Float(53))
    humidity = Column(Float(53))
    pressure = Column(Float(53))
    co = Column(Float(53))
    no = Column(Float(53))
    co2 = Column(Float(53))
    no2 = Column(Float(53))
