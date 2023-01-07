FROM python:3.9-alpine

RUN apk add build-base

RUN python -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"
ENV PYTHONUNBUFFERED=1

WORKDIR /service
COPY . /service
RUN pip install --disable-pip-version-check --upgrade --no-cache-dir -r requirements.txt

ENTRYPOINT ["python", "-m", "app"]