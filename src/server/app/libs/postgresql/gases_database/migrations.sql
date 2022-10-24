CREATE TABLE "oxides" (
  "id" SERIAL PRIMARY KEY,
  "time" timestamp NOT NULL DEFAULT (now()),
  "temperature" float8,
  "humidity" float8,
  "pressure" float8,
  "co" float8,
  "no" float8,
  "co2" float8,
  "no2" float8
);

CREATE TABLE "hydrides" (
  "id" SERIAL PRIMARY KEY,
  "time" timestamp NOT NULL DEFAULT (now()),
  "temperature" float8,
  "humidity" float8,
  "pressure" float8,
  "nh3" float8,
  "h2s" float8,
  "ch4" float8
);