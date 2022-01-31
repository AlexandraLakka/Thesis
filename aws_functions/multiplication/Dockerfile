FROM public.ecr.aws/lambda/python:3.8

COPY multiply.py ${LAMBDA_TASK_ROOT}

RUN pip3 install algorithms
#RUN pip3 install numpy

CMD ["multiply.handler"]
