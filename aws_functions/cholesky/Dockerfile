FROM python:3.8

WORKDIR /app
COPY cholesky.py .

RUN pip3 install algorithms
RUN pip3 install numpy

CMD ["python3", "cholesky.py"]
