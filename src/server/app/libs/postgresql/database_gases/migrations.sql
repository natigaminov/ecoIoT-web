CREATE TABLE IF NOT EXISTS "oxides" (
  "id" uuid PRIMARY KEY,
  "time" timestamp NOT NULL DEFAULT (now()),
  "temperature" float8,
  "humidity" float8,
  "pressure" float8,
  "co" float8,
  "no" float8,
  "co2" float8,
  "no2" float8
);

CREATE TABLE IF NOT EXISTS "hydrides" (
  "id" uuid PRIMARY KEY,
  "time" timestamp NOT NULL DEFAULT (now()),
  "temperature" float8,
  "humidity" float8,
  "pressure" float8,
  "nh3" float8,
  "h2s" float8,
  "ch4" float8
);